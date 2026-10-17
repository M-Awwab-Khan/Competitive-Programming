#!/usr/bin/env python3
"""Read-only health checks for catalog, source coverage, hashes, notes, and navigation."""
import argparse
import ast
import json
import re
import subprocess
import tempfile
from collections import defaultdict
from pathlib import Path
from urllib.parse import unquote, urlparse

from organization import ROOT, ROLE_ROOTS, checked_path, classification_hash, pending_files, read_catalog, sha256, source_files


def anchors(text):
    result, counts = set(), defaultdict(int)
    for heading in re.findall(r'^#{1,6}\s+(.+?)\s*#*$', text, re.M):
        base = re.sub(r'[^\w\- ]', '', heading.lower()).replace(' ', '-')
        number = counts[base]; counts[base] += 1
        result.add(base + (f'-{number}' if number else ''))
    result.update(re.findall(r'<(?:a|span)\s+(?:id|name)=["\']([^"\']+)', text))
    return result


def lint(root=ROOT):
    root = root.resolve()
    report = {'errors': [], 'warnings': [], 'information': [], 'summary': {}}
    def add(level, code, message, paths=()):
        report[level].append(dict(code=code, message=message, paths=list(paths)))
    try:
        catalog = read_catalog(root)
        problems = catalog['problems']
        categories = catalog['categories']
        registry = json.loads((root / 'catalog/patterns.json').read_text())['patterns']
        if catalog.get('schema_version') != 2:
            raise ValueError('Expected catalog schema_version 2')
        if not isinstance(problems, list) or not isinstance(categories, dict) or not isinstance(registry, list):
            raise ValueError('Catalog objects have incorrect types')
        if not all(isinstance(k, str) and isinstance(v, str) for k,v in categories.items()):
            raise ValueError('Categories must map names to descriptions')
    except (OSError, ValueError, KeyError, TypeError) as exc:
        add('errors', 'catalog-load', str(exc))
        return report
    patterns, pattern_paths = {}, set()
    for pattern in registry:
        try:
            if not re.fullmatch(r'[a-z0-9]+(?:-[a-z0-9]+)*', pattern['id']):
                raise ValueError('Invalid pattern ID')
            if pattern['id'] in patterns or pattern['path'] in pattern_paths:
                raise ValueError('Duplicate pattern ID or note path')
            path = checked_path(root, pattern['path'])
            if not path.is_relative_to(root / 'notes/patterns') or path.suffix != '.md' or not path.is_file():
                raise ValueError('Missing or misplaced pattern note')
            patterns[pattern['id']] = pattern; pattern_paths.add(pattern['path'])
        except (KeyError, ValueError, TypeError) as exc:
            add('errors', 'pattern-schema', str(exc), [str(pattern)])
    keys, paths, resolved, identities, hashes = {}, set(), set(), defaultdict(list), defaultdict(list)
    stale, unprocessed = [], []
    required = {'key','title','path','original_path','language','role','platform','problem_id','urls','collections',
                'implementation_status','original_sha256','category','tags','classification_status',
                'classification_evidence','classification_confidence','classification_sha256',
                'observed_sha256','classification_locked','review_required','patterns'}
    for p in problems:
        try:
            if not isinstance(p, dict):
                raise ValueError('Expected a problem record object')
            if required - p.keys():
                raise ValueError('Missing record fields: ' + ', '.join(sorted(required - p.keys())))
            if not all(isinstance(p[k], str) for k in ['key','path','category','original_path','title','classification_evidence']):
                raise ValueError('Expected string key/path/category/title/evidence')
            if not all(isinstance(p[k], list) and all(isinstance(t, str) for t in p[k]) for k in ['tags','patterns','urls','collections']):
                raise ValueError('Expected string lists for tags, patterns, links, and collections')
            if not all(isinstance(p[k], bool) for k in ['classification_locked','review_required']):
                raise ValueError('Expected boolean classification flags')
            if p['key'] in keys or p['path'] in paths:
                raise ValueError('Duplicate catalog key or path')
            keys[p['key']] = p; paths.add(p['path'])
            if any(p[k] is not None and not isinstance(p[k], str) for k in ['platform', 'problem_id']):
                raise ValueError('Platform and problem ID must be strings or null')
            if p['role'] not in ROLE_ROOTS or p['language'] not in {'cpp','python'}:
                raise ValueError('Unknown role or language')
            path = checked_path(root, p['path'])
            if path in resolved:
                raise ValueError('Multiple entries resolve to the same file')
            resolved.add(path)
            if not path.is_file():
                raise ValueError('Missing source')
            if path.suffix != ('.cpp' if p['language'] == 'cpp' else '.py'):
                raise ValueError('Language does not match source extension')
            if p['category'] not in categories or set(p['tags']) - categories.keys():
                raise ValueError('Unknown category or tag')
            if p['category'] != 'needs-review' and p['category'] not in p['tags']:
                raise ValueError('Primary category missing from tags')
            if set(p['patterns']) - patterns.keys():
                raise ValueError('Unknown pattern association')
            expected = (Path(ROLE_ROOTS[p['role']]) / p['category'] / path.name).as_posix()
            if p['path'] != expected:
                raise ValueError('Physical folder does not match role/category')
            if p['classification_status'] not in {'suggested','reviewed','needs-review'} or p['classification_confidence'] not in {'low','medium','high'}:
                raise ValueError('Invalid classification status or confidence')
            for name in ['original_sha256','classification_sha256','observed_sha256']:
                if not isinstance(p[name], str) or not re.fullmatch(r'[0-9a-f]{64}', p[name]):
                    raise ValueError('Invalid SHA-256: ' + name)
            digest = sha256(path)
            if digest != classification_hash(p):
                stale.append(p['path'])
            if digest != p['observed_sha256']:
                unprocessed.append(p['path'])
            if path.stat().st_size:
                hashes[digest].append(p['path'])
            if p['platform'] and p['problem_id']:
                identities[(str(p['platform']).casefold(), str(p['problem_id']).casefold())].append(p['path'])
        except (KeyError, TypeError, ValueError, OSError) as exc:
            add('errors', 'record-schema', str(exc), [str(p.get('path', p)) if isinstance(p, dict) else str(p)])
    uncataloged = sorted(source_files(root) - paths)
    if uncataloged:
        add('errors', 'uncataloged-sources', 'Managed source files are missing from the catalog; ingest them', uncataloged)
    pending = sorted(p.relative_to(root).as_posix() for p in pending_files(root))
    if pending:
        add('warnings', 'pending-inbox', 'Sources are waiting for ingestion', pending)
    if stale:
        add('warnings', 'stale-classification', 'Source bytes differ from those classified; read and review these files', stale)
    if unprocessed:
        add('warnings', 'unprocessed-changes', 'Run ingestion to acknowledge modified sources', unprocessed)
    repeated_ids = [group for group in identities.values() if len(group) > 1]
    repeated_content = [group for group in hashes.values() if len(group) > 1]
    for group in repeated_ids:
        add('information', 'shared-problem-id', 'Several implementations share a problem identity; preserved as separate attempts', group)
    for group in repeated_content:
        add('information', 'duplicate-content', 'Exact nonempty source duplicates; inspect before any consolidation', group)
    # Active documentation only. Archived planning intentionally records old paths.
    docs = sorted(p for p in root.rglob('*.md') if not any(part in {'.git','archive','build','.cph','__pycache__'} for part in p.relative_to(root).parts))
    incoming = defaultdict(set)
    for doc in docs:
        text = re.sub(r'^```.*?^```[^\n]*', '', doc.read_text(), flags=re.M | re.S)
        for raw in re.findall(r'\]\((<[^>]*>|[^\s)]+)(?:\s+"[^"\n]*")?\)', text):
            raw = raw.strip('<>')
            parsed = urlparse(raw)
            if parsed.scheme or raw.startswith('//'):
                continue
            target = (doc.parent / unquote(parsed.path)).resolve() if parsed.path else doc
            if not target.is_relative_to(root) or not target.exists():
                add('errors', 'broken-link', raw, [doc.relative_to(root).as_posix()]); continue
            if target != doc:
                incoming[target].add(doc)
            if parsed.fragment and target.is_file() and target.suffix == '.md' and unquote(parsed.fragment) not in anchors(target.read_text()):
                add('errors', 'broken-anchor', raw, [doc.relative_to(root).as_posix()])
    registered = {root / p for p in pattern_paths}
    actual = {p for p in (root / 'notes/patterns').glob('*.md') if p.name != 'INDEX.md'}
    if actual != registered:
        add('errors', 'pattern-coverage', 'Pattern notes and registry must cover each other', [str(p.relative_to(root)) for p in sorted(actual ^ registered)])
    orphans = [p.relative_to(root).as_posix() for p in (root / 'notes').rglob('*.md') if p.name != 'INDEX.md' and not incoming[p]]
    if orphans:
        add('errors', 'orphan-notes', 'Notes need an incoming navigation link', orphans)
    try:
        from build_catalog import render
        outputs = render(catalog, root)
        stale_outputs = [rel for rel,text in outputs.items() if not (root / rel).is_file() or (root / rel).read_text() != text]
        if stale_outputs:
            add('errors', 'stale-navigation', 'Regenerate with python3 scripts/build_catalog.py', stale_outputs)
    except (OSError, ValueError, KeyError, TypeError) as exc:
        add('errors', 'navigation-generation', str(exc))
    event_ids = set()
    try:
        for line in (root / 'catalog/events.jsonl').read_text().splitlines():
            event = json.loads(line)
            if not isinstance(event, dict):
                raise ValueError('Expected an event object')
            if not event.get('id') or event['id'] in event_ids or not all(k in event for k in ['time','operation','changes']):
                raise ValueError('Missing/duplicate event ID or event fields')
            event_ids.add(event['id'])
    except (OSError, ValueError, KeyError, TypeError) as exc:
        add('errors', 'event-log', str(exc))
    for script in (root / 'scripts').glob('*.py'):
        try:
            ast.parse(script.read_text(), filename=script.name)
        except SyntaxError as exc:
            add('errors', 'tool-syntax', str(exc), [script.relative_to(root).as_posix()])
    for rel in ['catalog/.organize-journal.json','catalog/.organize.lock']:
        if (root / rel).exists():
            add('errors', 'unfinished-operation', 'Another organizer is running or an operation needs recovery', [rel])
    report['summary'] = dict(catalog_entries=len(problems), pattern_notes=len(patterns), pending_sources=len(pending),
                             changed_since_classification=len(stale), shared_identity_groups=len(repeated_ids),
                             duplicate_content_groups=len(repeated_content), errors=len(report['errors']), warnings=len(report['warnings']))
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--json', action='store_true')
    parser.add_argument('--strict', action='store_true', help='Also fail on warnings')
    parser.add_argument('--staged', action='store_true', help='Check a temporary snapshot of Git staged files')
    args = parser.parse_args()
    if args.staged:
        with tempfile.TemporaryDirectory(prefix='cp-staged-lint-') as tmp:
            result = subprocess.run(['git','checkout-index','--all','--prefix',tmp + '/'],cwd=ROOT,capture_output=True,text=True)
            if result.returncode:
                parser.exit(1,result.stderr)
            report = lint(Path(tmp))
    else:
        report = lint()
    if args.json:
        print(json.dumps(report,ensure_ascii=False,indent=2))
    else:
        print(json.dumps(report['summary'],indent=2))
        for level in ['errors','warnings','information']:
            for item in report[level]:
                print(f'{level.upper()} [{item["code"]}]: {item["message"]}')
                for path in item['paths'][:12]:
                    print('  ' + path)
                if len(item['paths']) > 12:
                    print(f'  ... {len(item["paths"])-12} more (use --json for all paths)')
    raise SystemExit(1 if report['errors'] or (args.strict and report['warnings']) else 0)


if __name__ == '__main__':
    main()
