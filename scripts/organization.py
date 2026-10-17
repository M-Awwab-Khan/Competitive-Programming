"""Shared catalog operations. Source bytes are moved, never rewritten."""
import copy
import hashlib
import json
import os
import re
import tempfile
import uuid
from contextlib import contextmanager
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE_SUFFIXES = {'.cpp', '.py'}
ROLE_ROOTS = {'solution': 'solutions', 'algorithm': 'algorithms', 'reference': 'references/model-solutions'}


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_catalog(root=ROOT):
    return json.loads((root / 'catalog/problems.json').read_text())


def json_text(value):
    return json.dumps(value, ensure_ascii=False, indent=2) + '\n'


def checked_path(root, value):
    rel = Path(value)
    path = (root / rel).resolve()
    if rel.is_absolute() or '..' in rel.parts or not path.is_relative_to(root.resolve()):
        raise ValueError('Expected a repository-relative path: ' + str(value))
    return path


def classification_hash(problem):
    return problem.get('classification_sha256', problem['original_sha256'])


def locked(problem):
    return problem.get('classification_locked', False) or problem['classification_status'] == 'reviewed'


def source_files(root=ROOT):
    return {p.relative_to(root).as_posix() for folder in ["solutions", "algorithms", "references"]
            for p in (root / folder).rglob('*')
            if p.is_file() and p.suffix in SOURCE_SUFFIXES and '.cph' not in p.parts}


def pending_files(root=ROOT):
    paths = {p for p in root.iterdir() if p.is_file() and p.suffix in SOURCE_SUFFIXES}
    practice = root / 'practice'
    for p in practice.rglob('*'):
        rel = p.relative_to(practice)
        if p.is_file() and p.suffix in SOURCE_SUFFIXES and not any(part.startswith('.') or part == 'legacy' for part in rel.parts):
            paths.add(p)
    return paths


def patterns_for(category, code):
    """Associate focused notes only when implementation signals support them."""
    result = []
    if category == 'binary-search' and re.search(r'\b(?:possible|can_produce|canProduce|feasible|check)\s*(?:=|\()', code):
        result.append('binary-search-on-answer')
    if category == 'prefix-sums' and re.search(r'\b(?:map|unordered_map|dict|defaultdict|Counter)\b', code):
        result.append('prefix-sum-frequency-map')
    if re.search(r'\bdeque\b', code) and re.search(r'pop_back|pop\(', code) and re.search(r'front\(|popleft', code):
        result.append('monotonic-deque')
    if category == 'dynamic-programming/intervals' and re.search(r'\bdp\s*\[\s*(?:l|i)\s*\]\s*\[\s*(?:r|j)\s*\]', code):
        result.append('interval-dp')
    return result


def suggest(source, root, categories):
    # Historical filename overrides describe historical code; never apply them to a new attempt.
    from classify_solutions import _suggest, body
    text = source.read_text(errors='replace')
    result = _suggest(source.relative_to(root).as_posix(), text)
    if not text.strip() or re.search(r'void\s+solve\s*\(\s*\)\s*\{\s*\}', body(text, source.suffix)):
        result.update(category='needs-review', tags=[], classification_confidence='low',
                      classification_status='needs-review', classification_evidence='Empty file or empty solve function')
    if result['category'] not in categories:
        result.update(category='needs-review', tags=[], classification_confidence='low',
                      classification_status='needs-review', classification_evidence='Classifier category is not registered')
    result['tags'] = sorted({t for t in result['tags'] if t in categories} - {'needs-review'})
    if result['category'] != 'needs-review':
        result['tags'] = sorted(set(result['tags']) | {result['category']})
    result['classification_status'] = 'needs-review' if result['category'] == 'needs-review' else 'suggested'
    result['classification_locked'] = False
    result['classification_sha256'] = sha256(source)
    result['observed_sha256'] = sha256(source)
    result['review_required'] = result['category'] == 'needs-review'
    result['patterns'] = patterns_for(result['category'], body(text, source.suffix))
    return result


def destination_for(problem, catalog, root, reserved=()):
    base = ROLE_ROOTS[problem['role']]
    target = Path(base) / problem['category'] / Path(problem['path']).name
    occupied = {p['path'] for p in catalog['problems'] if p['key'] != problem['key']} | set(reserved)
    original = problem['path']
    stem, suffix = target.stem, target.suffix
    counter = 0
    while target.as_posix() in occupied or ((root / target).exists() and target.as_posix() != original):
        counter += 1
        target = target.with_name(stem + '__' + problem['key'][:8] + (f'-{counter}' if counter > 1 else '') + suffix)
    return target.as_posix()


def new_problem(source, catalog, root=ROOT, **metadata):
    source = source.resolve()
    if not source.is_relative_to(root.resolve()) or not source.is_file() or source.suffix not in SOURCE_SUFFIXES:
        raise ValueError('Expected an existing .cpp or .py inside the repository')
    rel = source.relative_to(root).as_posix()
    if any(p['path'] == rel for p in catalog['problems']):
        raise ValueError('Already cataloged; use review_solution.py to correct a classification')
    role = metadata.get('role') or ('algorithm' if rel.startswith('algorithms/') else 'reference' if rel.startswith('references/') else 'solution')
    problem = dict(key=uuid.uuid4().hex[:16], title=metadata.get('title') or source.stem.replace('_', ' ').replace('-', ' '),
                   path=rel, original_path=rel, language='cpp' if source.suffix == '.cpp' else 'python',
                   role=role, platform=metadata.get('platform'), problem_id=metadata.get('problem_id'),
                   urls=metadata.get('urls', []), collections=[], implementation_status='not-verified',
                   original_sha256=sha256(source), **suggest(source, root, catalog['categories']))
    if not source.read_text(errors='replace').strip():
        problem['implementation_status'] = 'empty-or-template'
    if metadata.get('category'):
        set_review(problem, catalog, source, metadata['category'], metadata.get('tags', []),
                   metadata.get('evidence') or 'Category supplied when filing the solution', metadata.get('patterns', []))
    for url in problem['urls']:
        if not url.startswith(('https://', 'http://')):
            raise ValueError('Problem links must use HTTP or HTTPS')
    return problem


def set_review(problem, catalog, source, category, tags, evidence, patterns):
    if category not in catalog['categories']:
        raise ValueError('Unknown category: ' + category)
    unknown = set(tags) - catalog['categories'].keys()
    if unknown:
        raise ValueError('Unknown tags: ' + ', '.join(sorted(unknown)))
    if not evidence.strip():
        raise ValueError('Record a reason for the classification')
    problem.update(category=category, tags=sorted(set(tags) | ({category} if category != 'needs-review' else set())),
                   classification_status='reviewed' if category != 'needs-review' else 'needs-review',
                   classification_locked=True, classification_confidence='high' if category != 'needs-review' else 'low',
                   classification_evidence=evidence, classification_sha256=sha256(source), observed_sha256=sha256(source),
                   review_required=category == 'needs-review', patterns=sorted(set(patterns)))


@contextmanager
def lock(root=ROOT):
    path = root / 'catalog/.organize.lock'
    try:
        fd = os.open(path, os.O_CREAT | os.O_EXCL | os.O_WRONLY, 0o600)
    except FileExistsError:
        raise ValueError('Another organizer is running. If it crashed, inspect catalog/.organize-journal.json before removing catalog/.organize.lock.')
    try:
        with os.fdopen(fd, 'w') as handle:
            handle.write(str(os.getpid()))
        yield
    finally:
        path.unlink(missing_ok=True)


def atomic_write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, name = tempfile.mkstemp(prefix='.' + path.name + '.', suffix='.organize-tmp', dir=path.parent)
    tmp = Path(name)
    try:
        with os.fdopen(fd, 'wb') as handle:
            handle.write(data)
        tmp.replace(path)
    finally:
        tmp.unlink(missing_ok=True)



def apply(catalog, changes, operation, root=ROOT):
    """Caller holds lock. Roll back moves and metadata if any step fails."""
    if not changes:
        return False
    from build_catalog import render
    registered_patterns = {p['id'] for p in json.loads((root / 'catalog/patterns.json').read_text())['patterns']}
    for problem in catalog['problems']:
        unknown = set(problem.get('patterns', [])) - registered_patterns
        if unknown:
            raise ValueError('Unknown patterns: ' + ', '.join(sorted(unknown)))
    moves = [(c['before']['path'], c['after']['path']) for c in changes if c['before']['path'] != c['after']['path']]
    # Preflight before moving any files.
    for change in changes:
        source = checked_path(root, change['before']['path'])
        if not source.is_file() or sha256(source) != change['source_sha256']:
            raise ValueError('Source changed while preparing operation: ' + str(source))
    for old, new in moves:
        if checked_path(root, new).exists():
            raise ValueError('Refusing to overwrite ' + new)
    events_path = root / 'catalog/events.jsonl'
    events = events_path.read_text() if events_path.exists() else ''
    event = dict(id=uuid.uuid4().hex, time=datetime.now(timezone.utc).isoformat(timespec='seconds'),
                 operation=operation, changes=changes)
    events += json.dumps(event, ensure_ascii=False) + '\n'
    snapshot = {}
    completed = []
    journal = root / 'catalog/.organize-journal.json'
    if journal.exists():
        raise ValueError('An unfinished journal exists; inspect it before another write')
    journal.write_text(json_text(dict(operation=operation, moves=moves, event=event)))
    def write(rel, data):
        path = root / rel
        if path not in snapshot:
            snapshot[path] = path.read_bytes() if path.exists() else None
        atomic_write(path, data)
    cleanup_journal = False
    try:
        for old, new in moves:
            target = checked_path(root, new)
            target.parent.mkdir(parents=True, exist_ok=True)
            checked_path(root, old).rename(target)
            completed.append((old, new))
        # CPH remains optional; update any existing active association when its source moves.
        for old, new in moves:
            for record in sorted((root / old).parent.glob('.cph/*.prob')):
                obj = json.loads(record.read_text())
                if obj.get('srcPath') != str(root / old):
                    continue
                obj['srcPath'] = str(root / new)
                if obj.get('url') == str(root / old):
                    obj['url'] = str(root / new)
                name = '.' + Path(new).name + '_' + hashlib.md5(str(root / new).encode()).hexdigest() + '.prob'
                target = Path(new).parent / '.cph' / name
                if (root / target).exists():
                    raise ValueError('CPH target already exists: ' + str(target))
                write(target, json_text(obj).encode())
                if record not in snapshot:
                    snapshot[record] = record.read_bytes()
                record.unlink()
        write('catalog/problems.json', json_text(catalog).encode())
        write('catalog/events.jsonl', events.encode())
        for rel, text in render(catalog, root).items():
            write(rel, text.encode())
        for change in changes:
            if sha256(root / change['after']['path']) != change['source_sha256']:
                raise ValueError('Source preservation check failed')
        cleanup_journal = True
    except BaseException:
        for path, data in reversed(list(snapshot.items())):
            if data is None:
                path.unlink(missing_ok=True)
            else:
                atomic_write(path, data)
        for old, new in reversed(completed):
            source = root / old
            source.parent.mkdir(parents=True, exist_ok=True)
            (root / new).rename(source)
        cleanup_journal = True
        raise
    finally:
        if cleanup_journal:
            journal.unlink(missing_ok=True)
    return True


def change_record(before, after, source, reason):
    # Log semantic changes, not entire source files or duplicated catalog records.
    fields = ['path', 'category', 'tags', 'classification_status', 'classification_locked', 'classification_sha256', 'observed_sha256', 'patterns', 'review_required']
    return dict(key=after['key'], before={k:copy.deepcopy(before.get(k)) for k in fields},
                after={k:copy.deepcopy(after.get(k)) for k in fields}, source_sha256=sha256(source), reason=reason)
