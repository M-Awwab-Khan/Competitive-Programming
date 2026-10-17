#!/usr/bin/env python3
"""Regenerate navigation and example links; preserve authored pattern explanations."""
import json
import re
from collections import Counter, defaultdict
from pathlib import Path
from urllib.parse import quote

from organization import ROOT, ROLE_ROOTS, atomic_write, checked_path, classification_hash, lock, read_catalog, sha256, source_files


def link(path):
    return quote(str(path), safe='/.-_')


def cell(text):
    return str(text).replace('|', '\\|').replace('\n', ' ').replace('[', '\\[').replace(']', '\\]')


def stale(problem, root):
    return sha256(checked_path(root, problem['path'])) != classification_hash(problem)


def render(catalog, root=ROOT):
    """Return deterministic generated artifacts without writing anything."""
    problems, paths, keys = catalog['problems'], set(), set()
    outputs = {}
    registry = json.loads((root / 'catalog/patterns.json').read_text())['patterns']
    patterns = {p['id']: p for p in registry}
    for p in problems:
        if p['path'] in paths or p['key'] in keys:
            raise ValueError('Duplicate catalog path or key: ' + p['path'])
        paths.add(p['path']); keys.add(p['key'])
        target = checked_path(root, p['path'])
        if not target.is_file():
            raise ValueError('Missing source: ' + p['path'])
        if p['category'] not in catalog['categories'] or set(p['tags']) - catalog['categories'].keys():
            raise ValueError('Unknown category or tag: ' + p['path'])
        if p['category'] != 'needs-review' and p['category'] not in p['tags']:
            raise ValueError('Primary category missing from tags: ' + p['path'])
        expected = Path(ROLE_ROOTS[p['role']]) / p['category'] / target.name
        if expected.as_posix() != p['path']:
            raise ValueError('Source is outside its category: ' + p['path'])
        if set(p.get('patterns', [])) - patterns.keys():
            raise ValueError('Unknown pattern association: ' + p['path'])
    if source_files(root) != paths:
        raise ValueError('Catalog/source mismatch: ' + repr(sorted(source_files(root) ^ paths)))
    grouped, tagged = defaultdict(list), defaultdict(list)
    ordered = sorted(problems, key=lambda p: (p['title'].casefold(), p['path']))
    changed = {p['key'] for p in problems if stale(p, root)}
    for p in ordered:
        grouped[p['category']].append(p)
        for tag in p['tags']:
            tagged[tag].append(p)
    lines = ['# Problem index', '', f'{len(problems)} source files across {len(grouped)} primary categories.', '',
             'Categories describe local implementations. Suggested labels are inferred; reviewed labels are explicit decisions. Neither implies judge acceptance.', '',
             '[Tag index](TAGS.md) · [Review queue](REVIEW.md) · [Pattern notes](../notes/patterns/INDEX.md) · [Guide](../README.md)', '',
             '| Category | Files | Description |', '| --- | ---: | --- |']
    for cat, entries in sorted(grouped.items()):
        lines.append(f'| [{cat}](#{cat.replace("/", "")}) | {len(entries)} | {catalog["categories"][cat]} |')
    for cat, entries in sorted(grouped.items()):
        lines += ['', '## ' + cat, '', '| Problem / file | Language | Platform / ID | Tags | Classification | Patterns |', '| --- | --- | --- | --- | --- | --- |']
        for p in entries:
            identity = ' / '.join(str(x) for x in [p.get('platform'), p.get('problem_id')] if x) or 'unknown'
            label = cell(p['title']) + ' — ' + cell(Path(p['original_path']).name)
            pattern_links = ', '.join(f'[{cell(patterns[t]["title"])}](../{link(patterns[t]["path"])})' for t in p.get('patterns', []))
            status = p['classification_status'] + ('; source changed' if p['key'] in changed else '')
            lines.append(f'| [{label}](../{link(p["path"])}) | {p["language"]} | {cell(identity)} | {", ".join(p["tags"])} | {status} | {pattern_links} |')
    outputs['catalog/INDEX.md'] = '\n'.join(lines) + '\n'
    lines = ['# Pattern and tag index', '', 'A source may appear under several tags. Its primary category determines its folder.', '',
             '[Problem index](INDEX.md) · [Pattern explanations](../notes/patterns/INDEX.md)', '']
    for tag, entries in sorted(tagged.items()):
        lines += ['## ' + tag, '', f'{len(entries)} files', '']
        lines += [f'- [{cell(p["title"])} ({p["language"]})](../{link(p["path"])})' for p in entries]
        lines.append('')
    outputs['catalog/TAGS.md'] = '\n'.join(lines)
    lines = ['# Classification review queue', '',
             'Empty or uncertain implementations and sources changed since classification appear here. Reviewed labels remain locked until explicitly corrected.', '',
             'Automatic suggestions can be inspected with `python3 scripts/search.py --suggested`.', '',
             '| File | Reason |', '| --- | --- |']
    for p in ordered:
        if p['classification_status'] == 'needs-review' or p.get('review_required') or p['key'] in changed:
            reason = 'Source changed since classification; read the current implementation' if p['key'] in changed else p['classification_evidence']
            lines.append(f'| [{cell(p["original_path"])}](../{link(p["path"])}) | {cell(reason)} |')
    lines += ['', 'Record a decision with `python3 scripts/review_solution.py FILE --category CATEGORY --evidence "Why this pattern applies"`.', '']
    outputs['catalog/REVIEW.md'] = '\n'.join(lines)
    lines = ['# Solutions by pattern', '', '[Problem index](../catalog/INDEX.md) · [Pattern notes](../notes/patterns/INDEX.md) · [Guide](../README.md)', '',
             '| Category | Solutions |', '| --- | ---: |']
    for cat, entries in sorted(grouped.items()):
        count = sum(p['role'] == 'solution' for p in entries)
        if count:
            lines.append(f'| [{cat}]({link(cat)}/) | {count} |')
    outputs['solutions/README.md'] = '\n'.join(lines) + '\n'
    stats = dict(total_entries=len(problems), roles=dict(Counter(p['role'] for p in problems)),
                 categories=dict(Counter(p['category'] for p in problems)),
                 classifications=dict(Counter(p['classification_status'] for p in problems)),
                 implementations=dict(Counter(p['implementation_status'] for p in problems)), sources_changed_since_classification=len(changed))
    outputs['catalog/stats.json'] = json.dumps(stats, indent=2) + '\n'
    lines = ['# Pattern notes', '', 'Recognition clues, invariants, pitfalls, and examples from this repository.', '',
             '[All notes](../INDEX.md) · [Problem index](../../catalog/INDEX.md)', '', '| Pattern | Examples |', '| --- | ---: |']
    for pattern in registry:
        examples = [p for p in ordered if pattern['id'] in p.get('patterns', [])]
        path = checked_path(root, pattern['path'])
        text = path.read_text()
        block = ['<!-- examples:start -->', '', '## Examples from this repository', '',
                 'Links are generated from catalog associations; classifications do not establish correctness.', '',
                 '| Implementation | Category | Classification |', '| --- | --- | --- |']
        for p in examples:
            block.append(f'| [{cell(p["title"])} ({p["language"]})](../../{link(p["path"])}) | {p["category"]} | {p["classification_status"]} |')
        block += ['', '<!-- examples:end -->']
        if text.count('<!-- examples:start -->') != 1 or text.count('<!-- examples:end -->') != 1:
            raise ValueError('Expected one generated examples block in ' + pattern['path'])
        outputs[pattern['path']] = re.sub(r'<!-- examples:start -->.*?<!-- examples:end -->', lambda _: '\n'.join(block), text, flags=re.S)
        lines.append(f'| [{cell(pattern["title"])}]({link(path.name)}) | {len(examples)} |')
    outputs['notes/patterns/INDEX.md'] = '\n'.join(lines) + '\n'
    lines = ['# Notes', '', '[Problem catalog](../catalog/INDEX.md) · [Pattern hub](patterns/INDEX.md)', '']
    for path in sorted((root / 'notes').rglob('*.md')):
        if path.name == 'INDEX.md':
            continue
        title = next((line.lstrip('# ').strip() for line in path.read_text().splitlines() if line.startswith('#')), path.stem)
        lines.append(f'- [{cell(title)}]({link(path.relative_to(root / "notes"))})')
    outputs['notes/INDEX.md'] = '\n'.join(lines) + '\n'
    lines = ['# Organization log', '', 'Repository organization events, newest first. Source code is never copied into the log.', '', '[Guide](README.md)', '']
    events = (root / 'catalog/events.jsonl').read_text().splitlines() if (root / 'catalog/events.jsonl').exists() else []
    for raw in reversed(events):
        event = json.loads(raw)
        lines += ['## ' + event['time'] + ' — ' + event['operation'], '']
        if event.get('summary'):
            lines.append(event['summary']); lines.append('')
        for change in event.get('changes', []):
            before, after = change['before'], change['after']
            lines.append(f'- {before["path"]} → {after["path"]}: {change["reason"]}. Category: {after.get("category")}; status: {after.get("classification_status")}.')
        lines.append('')
    outputs['ORGANIZATION_LOG.md'] = '\n'.join(lines)
    return outputs


def build(root=ROOT):
    with lock(root):
        outputs = render(read_catalog(root), root)
        for rel, text in outputs.items():
            atomic_write(root / rel, text.encode())
    print(f'Rebuilt {len(outputs)} navigation artifacts and example lists.')


if __name__ == '__main__':
    build()
