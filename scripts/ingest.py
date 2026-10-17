#!/usr/bin/env python3
"""Preview or apply incremental organization; existing reviewed labels are protected."""
import argparse
import copy
import json
from pathlib import Path

from organization import (ROOT, apply, change_record, classification_hash, destination_for, json_text,
                          lock, locked, new_problem, pending_files, read_catalog, sha256, source_files, suggest)


def plan(catalog, root=ROOT, selected=None):
    catalog = copy.deepcopy(catalog)
    changes = []
    indexed = {p['path'] for p in catalog['problems']}
    incoming = pending_files(root) | {root / p for p in source_files(root) - indexed}
    if selected:
        incoming |= {Path(p).resolve() for p in selected}
        invalid = [p for p in incoming if p in {Path(s).resolve() for s in selected} and
                   (not p.is_file() or not p.is_relative_to(root) or p.suffix not in {'.cpp', '.py'})]
        if invalid:
            raise ValueError('Invalid source path: ' + str(invalid[0]))
        incoming = {Path(p).resolve() for p in selected if Path(p).resolve().relative_to(root).as_posix() not in indexed}
    unchanged = 0
    for problem in catalog['problems']:
        source = root / problem['path']
        if selected and source.resolve() not in {Path(p).resolve() for p in selected}:
            continue
        if not source.is_file():
            raise ValueError('Missing catalog source: ' + problem['path'])
        digest = sha256(source)
        observed = problem.get('observed_sha256', classification_hash(problem))
        if digest == observed:
            unchanged += 1
            continue
        before = copy.deepcopy(problem)
        if locked(problem):
            problem.update(observed_sha256=digest, review_required=digest != classification_hash(problem))
            reason = 'Source changed; preserved locked classification pending review'
        else:
            problem.update(suggest(source, root, catalog['categories']))
            problem['path'] = destination_for(problem, catalog, root)
            reason = 'Reclassified changed source using current implementation signals'
        changes.append(change_record(before, problem, source, reason))
    for source in sorted(incoming):
        if source.relative_to(root).as_posix() in indexed:
            continue
        problem = new_problem(source, catalog, root)
        before = copy.deepcopy(problem)
        problem['path'] = destination_for(problem, catalog, root)
        catalog['problems'].append(problem)
        changes.append(change_record(before, problem, source, 'Filed new source; classification remains a suggestion'))
    return catalog, changes, unchanged


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('sources', nargs='*', help='Optional specific files; otherwise scan inbox and managed sources')
    parser.add_argument('--apply', action='store_true', help='Apply moves, update metadata, regenerate indexes, and log the operation')
    parser.add_argument('--json', action='store_true')
    args = parser.parse_args()
    try:
        with lock():
            catalog, changes, unchanged = plan(read_catalog(), selected=args.sources or None)
            if not args.json:
                for c in changes:
                    print(c['before']['path'] + ' -> ' + c['after']['path'])
                    print('  ' + c['reason'] + ' [' + c['after']['classification_status'] + ']')
                print(f'{len(changes)} change(s); {unchanged} unchanged source(s) skipped.')
                if changes and not args.apply:
                    print('Preview only. Apply with --apply after reviewing the proposed moves.')
            if args.apply and changes:
                apply(catalog, changes, 'INGEST')
                if not args.json:
                    print('Applied. Source bytes preserved; indexes and log updated.')
            if args.json:
                print(json_text(dict(changes=changes, unchanged=unchanged, applied=bool(args.apply and changes))), end='')
    except (ValueError, OSError, KeyError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    main()
