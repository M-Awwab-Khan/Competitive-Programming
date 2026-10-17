#!/usr/bin/env python3
"""Apply the recorded, local category migration once. Default: print a summary."""
import argparse
import hashlib
import json
import re
import shutil
from collections import Counter
from pathlib import Path

from classify_solutions import CATEGORIES, classify

ROOT = Path(__file__).resolve().parents[1]

def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    manifest_path = ROOT / 'catalog/migration.json'
    if manifest_path.exists():
        parser.exit(0, 'Migration already recorded in catalog/migration.json; use the catalog tools for future additions.\n')
    inventory = json.loads((ROOT / 'catalog/inventory.json').read_text())
    moves, problems, source_destinations = [], [], {}
    for old in inventory['files']:
        source, kind = old['source'], old['category']
        path = ROOT / source
        destination = source
        if kind in {'solution', 'reference'}:
            text = path.read_text(errors='replace')
            classification = classify(source, text)
            implementation_status = 'not-verified'
            if not text.strip() or re.search(r'void\s+solve\s*\(\s*\)\s*\{\s*\}', text):
                implementation_status = 'empty-or-template'
                classification.update(category='needs-review', classification_confidence='low',
                                      classification_status='needs-review',
                                      classification_evidence='Empty file or empty solve function')
            role = 'reference' if kind == 'reference' else 'solution'
            if source.startswith('sp/'):
                role = 'algorithm' if Path(source).name != 'A.cpp' else 'scratch'
            category = classification['category']
            base = {'solution': 'solutions', 'algorithm': 'algorithms', 'reference': 'references/model-solutions', 'scratch': 'practice/legacy'}[role]
            destination = base + '/' + (category + '/' if role != 'scratch' else 'sp/') + path.name
            metadata = old['metadata']
            title = next((m['name'] for m in metadata if m.get('name') and not m['name'].startswith('Local:')), path.stem.replace('_', ' ').replace('-', ' '))
            urls = sorted({m['url'] for m in metadata if m.get('url', '').startswith(('http://', 'https://'))})
            # VJudge Gym identifiers belong to Codeforces Gym.
            platform, problem_id = old.get('platform'), old.get('problem_id')
            if platform == 'gym':
                platform, problem_id = 'codeforces', 'gym-' + problem_id
            if role != 'scratch':
                problems.append(dict(key=hashlib.sha256(source.encode()).hexdigest()[:16],
                                     title=title, path=destination, original_path=source,
                                     language='cpp' if path.suffix == '.cpp' else 'python',
                                     role=role, platform=platform, problem_id=problem_id,
                                     urls=urls, collections=sorted({m['group'] for m in metadata if m.get('group') and m['group'] != 'local'}),
                                     implementation_status=implementation_status,
                                     original_sha256=old['sha256'], **classification))
        elif kind == 'template':
            destination = 'templates/' + ('cpp/' if path.suffix == '.cpp' else 'python/') + path.name
        elif kind == 'practice-candidate':
            destination = 'practice/legacy/' + source
            if path.suffix == '.txt':
                destination = 'practice/' + path.name
        elif kind == 'notes':
            destination = 'notes/math/diophantine-equations.md'
        elif kind == 'build-artifact':
            destination = 'build/legacy/' + source
        elif kind == 'tooling':
            destination = ('scripts/' if path.suffix == '.py' else 'archive/tooling/') + path.name
        elif kind == 'cph-metadata':
            destination = 'archive/cph-original/' + source
        source_destinations[source] = destination
        moves.append(dict(source=source, destination=destination, sha256=old['sha256'],
                          size_bytes=old['size_bytes'], originally_tracked=old['tracked'], kind=kind))
    destinations = [m['destination'] for m in moves]
    if len(set(destinations)) != len(destinations):
        raise SystemExit('Destination collision: inspect the plan before applying.')
    print(json.dumps(dict(files=len(moves), catalog_entries=len(problems),
                          categories=dict(Counter(p['category'] for p in problems)),
                          moves=sum(m['source'] != m['destination'] for m in moves)), indent=2))
    if not args.apply:
        return
    # Check the entire snapshot before the first move; preserve all uncommitted bytes.
    for move in moves:
        source, target = ROOT / move['source'], ROOT / move['destination']
        if not source.is_file() or digest(source) != move['sha256']:
            raise SystemExit('Snapshot changed; refresh inventory before applying: ' + move['source'])
        if target != source and target.exists():
            raise SystemExit('Refusing to overwrite: ' + move['destination'])
    completed = []
    try:
        for move in moves:
            if move['source'] == move['destination']:
                continue
            source, target = ROOT / move['source'], ROOT / move['destination']
            target.parent.mkdir(parents=True, exist_ok=True)
            source.rename(target)
            completed.append(move)
    except BaseException:
        for move in reversed(completed):
            source, target = ROOT / move['source'], ROOT / move['destination']
            source.parent.mkdir(parents=True, exist_ok=True)
            target.rename(source)
        raise
    # Keep original ignored records byte-for-byte, and create new active CPH associations.
    cph_updates = []
    for move in moves:
        if move['kind'] != 'cph-metadata':
            continue
        saved = ROOT / move['destination']
        obj = json.loads(saved.read_text())
        original = obj.get('srcPath', '')
        old_path = Path(original)
        try:
            old_key = old_path.relative_to(ROOT).as_posix() if old_path.is_absolute() else old_path.as_posix()
        except ValueError:
            old_key = None
        if old_key not in source_destinations:
            candidates = [s for s in source_destinations if Path(s).name == old_path.name]
            old_key = candidates[0] if len(candidates) == 1 else None
        if old_key is None:
            # Orphan records remain locally available in their previous location as well.
            target = ROOT / move['source']
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(saved, target)
            continue
        new_source = ROOT / source_destinations[old_key]
        new_absolute = str(new_source)
        obj['srcPath'] = new_absolute
        if obj.get('url') == original:
            obj['url'] = new_absolute
        name = '.' + new_source.name + '_' + hashlib.md5(new_absolute.encode()).hexdigest() + '.prob'
        target = new_source.parent / '.cph' / name
        if target.exists():
            current = json.loads(target.read_text())
            samples = current.setdefault('tests', [])
            seen = {(t.get('input'), t.get('output')) for t in samples}
            for sample in obj.get('tests', []):
                signature = (sample.get('input'), sample.get('output'))
                if signature not in seen:
                    sample = dict(sample)
                    ids = {t.get('id') for t in samples}
                    if sample.get('id') in ids:
                        sample['id'] = max((i for i in ids if isinstance(i, int)), default=0) + 1
                    samples.append(sample)
                    seen.add(signature)
            obj = current
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(json.dumps(obj, ensure_ascii=False, indent=2) + '\n')
        cph_updates.append(dict(original_record=move['source'], new_record=target.relative_to(ROOT).as_posix(), source=source_destinations[old_key]))
    # Integrity check is about file preservation; historical solutions are not executed.
    mismatches = [m['destination'] for m in moves if digest(ROOT / m['destination']) != m['sha256']]
    if mismatches:
        raise SystemExit('Integrity mismatch: ' + repr(mismatches))
    payload = dict(schema_version=1, layout='category-first', original_file_count=len(moves),
                   preservation_check='All original file hashes matched after moving', files=moves,
                   cph_updates=cph_updates)
    manifest_path.write_text(json.dumps(payload, ensure_ascii=False, indent=2) + '\n')
    (ROOT / 'catalog/problems.json').write_text(json.dumps(dict(schema_version=1, categories=CATEGORIES, problems=problems), ensure_ascii=False, indent=2) + '\n')
    archive = ROOT / 'archive/planning'
    archive.mkdir(parents=True, exist_ok=True)
    for name in ['inventory.json', 'migration.csv', 'MIGRATION_PREVIEW.md', 'classification-draft.json']:
        (ROOT / 'catalog' / name).rename(archive / name)
    (ROOT / 'scripts/preview_organization.py').rename(archive / 'preview_platform_organization.py')
    (archive / 'README.md').write_text('# Historical planning snapshot\n\nThese files capture the initial platform-based proposal before the category-first implementation. Paths describe the original layout. The preview script is preserved as historical source, not an active command. Current paths and classifications are in ../../catalog/problems.json; original-to-current paths and hashes are in ../../catalog/migration.json.\n')
    print('Migration applied. All ' + str(len(moves)) + ' original file hashes matched. CPH associations updated: ' + str(len(cph_updates)))

if __name__ == '__main__':
    main()
