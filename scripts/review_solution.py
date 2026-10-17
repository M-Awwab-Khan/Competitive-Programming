#!/usr/bin/env python3
"""Record and lock a classification correction, preserving source bytes and old names."""
import argparse
import copy
from pathlib import Path

from organization import ROOT, apply, change_record, destination_for, lock, read_catalog, set_review


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', help='Current path, unique original path, or unique filename')
    parser.add_argument('--category', required=True)
    parser.add_argument('--tags', default='', help='Comma-separated additional category tags; replaces old tags')
    parser.add_argument('--pattern', action='append', default=None, help='Link a focused pattern note by ID (repeatable)')
    parser.add_argument('--clear-patterns', action='store_true')
    parser.add_argument('--evidence', required=True, help='Reason supported by reading the current implementation')
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    try:
        with lock():
            catalog = read_catalog()
            matches = [p for p in catalog['problems'] if args.source in {p['path'], p['original_path'], Path(p['path']).name}]
            if len(matches) != 1:
                raise ValueError('Expected exactly one match; use the current catalog path')
            problem = matches[0]
            before = copy.deepcopy(problem)
            patterns = args.pattern if args.pattern is not None else ([] if args.clear_patterns else problem.get('patterns', []))
            set_review(problem, catalog, ROOT / before['path'], args.category,
                       [t.strip() for t in args.tags.split(',') if t.strip()], args.evidence, patterns)
            problem['path'] = destination_for(problem, catalog, ROOT)
            print(before['path'] + ' -> ' + problem['path'])
            print('Classification will be locked: ' + args.evidence)
            if args.apply:
                if before == problem:
                    print('Already recorded; nothing changed.')
                else:
                    apply(catalog, [change_record(before, problem, ROOT / before['path'], args.evidence)], 'REVIEW')
                    print('Review recorded; source preserved and navigation updated.')
            else:
                print('Preview only. Use --apply to record this review.')
    except (ValueError, OSError, KeyError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    main()
