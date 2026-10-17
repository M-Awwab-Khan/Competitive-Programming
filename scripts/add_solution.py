#!/usr/bin/env python3
"""File a source with an explicit category, lock that decision, and update navigation."""
import argparse
import copy
from pathlib import Path

from organization import ROOT, apply, change_record, destination_for, lock, new_problem, read_catalog


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('--category', required=True)
    parser.add_argument('--tags', default='')
    parser.add_argument('--pattern', action='append', default=[])
    parser.add_argument('--title')
    parser.add_argument('--platform')
    parser.add_argument('--id', dest='problem_id')
    parser.add_argument('--url', action='append', default=[])
    parser.add_argument('--role', choices=['solution', 'algorithm', 'reference'], default='solution')
    args = parser.parse_args()
    try:
        with lock():
            catalog = read_catalog()
            problem = new_problem(args.source, catalog, category=args.category,
                                  tags=[t.strip() for t in args.tags.split(',') if t.strip()], patterns=args.pattern,
                                  title=args.title, platform=args.platform, problem_id=args.problem_id,
                                  urls=args.url, role=args.role)
            before = copy.deepcopy(problem)
            problem['path'] = destination_for(problem, catalog, ROOT)
            catalog['problems'].append(problem)
            apply(catalog, [change_record(before, problem, ROOT / before['path'], 'Filed with an explicitly chosen category')], 'INGEST')
            print(problem['path'])
    except (ValueError, OSError, KeyError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    main()
