#!/usr/bin/env python3
"""Search the solution catalog using only Python's standard library."""
import argparse
import json
import re
import unicodedata
from pathlib import Path

from organization import classification_hash, sha256

ROOT = Path(__file__).resolve().parents[1]
ALIASES = {'dp': 'dynamic-programming', 'two-pointers': 'two-pointers-and-sliding-window',
           'sliding-window': 'two-pointers-and-sliding-window', 'dsu': 'data-structures/disjoint-set',
           'segment-tree': 'data-structures/range-queries', 'fenwick': 'data-structures/range-queries',
           'number-theory': 'math/number-theory', 'combinatorics': 'math/combinatorics',
           'bfs': 'graphs', 'dfs': 'graphs', 'cf': 'codeforces', 'py': 'python', 'c++': 'cpp'}

def normalize(value):
    value = unicodedata.normalize('NFKD', str(value)).casefold()
    return re.sub(r'[^\w]+', ' ', value.replace('_', ' ')).strip()

def expand(value):
    key = value.casefold().replace(' ', '-').replace('_', '-')
    return ALIASES.get(key, value)

def load_catalog():
    return json.loads((ROOT / 'catalog/problems.json').read_text())

def field_matches(wanted, actual):
    wanted = normalize(expand(wanted))
    actual = normalize(actual or '')
    return actual == wanted or actual.startswith(wanted + ' ')

def matches(problem, queries, category=None, tag=None, platform=None, language=None, role=None, needs_review=False):
    if category and not field_matches(category, problem['category']):
        return False
    if tag and not any(field_matches(tag, t) for t in problem['tags']):
        return False
    if platform and not field_matches(platform, problem.get('platform')):
        return False
    if language and not field_matches(language, problem['language']):
        return False
    if role and problem['role'] != role:
        return False
    if needs_review and not (problem['classification_status'] == 'needs-review' or problem.get('review_required') or sha256(ROOT / problem['path']) != classification_hash(problem)):
        return False
    haystack = normalize(' '.join(str(problem.get(k) or '') for k in
                         ['title', 'path', 'original_path', 'platform', 'problem_id', 'tags', 'patterns', 'collections', 'urls']))
    terms = [term for query in queries for term in normalize(expand(query)).split()]
    return all(term in haystack for term in terms)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('query', nargs='*', help='Title, filename, old path, ID, or keyword (all terms must match)')
    parser.add_argument('--category', help='Primary category; parent names and aliases such as dp work')
    parser.add_argument('--tag', help='Primary or secondary pattern tag')
    parser.add_argument('--pattern', help='Focused pattern ID, such as monotonic-deque')
    parser.add_argument('--changed', action='store_true', help='Source changed since its classification')
    parser.add_argument('--notes', action='store_true', help='Search pattern note explanations instead of solutions')
    parser.add_argument('--list-patterns', action='store_true')
    parser.add_argument('--platform')
    parser.add_argument('--language', choices=['cpp', 'python', 'py', 'c++'])
    parser.add_argument('--role', choices=['solution', 'algorithm', 'reference'])
    parser.add_argument('--needs-review', action='store_true', help='Entries without enough classification evidence')
    parser.add_argument('--suggested', action='store_true', help='Show classifications awaiting manual confirmation')
    parser.add_argument('--list-categories', action='store_true')
    parser.add_argument('--limit', type=int, help='Maximum results; default shows every match')
    parser.add_argument('--json', action='store_true', help='Machine-readable results')
    parser.add_argument('--paths', action='store_true', help='Only print repository-relative paths')
    args = parser.parse_args()
    if args.limit is not None and args.limit < 1:
        parser.error('--limit must be positive')
    catalog = load_catalog()
    registry = json.loads((ROOT / 'catalog/patterns.json').read_text())['patterns']
    if args.list_patterns:
        for pattern in registry:
            print(pattern['id'] + '  ' + pattern['title'] + '  ' + pattern['path'])
        return
    if args.notes:
        terms = [term for query in args.query for term in normalize(expand(query)).split()]
        results = [p for p in registry if (not args.pattern or field_matches(args.pattern, p['id'])) and
                   all(term in normalize(p['title'] + ' ' + p['id'] + ' ' + (ROOT / p['path']).read_text()) for term in terms)]
        if args.limit is not None:
            results = results[:args.limit]
        if args.json:
            print(json.dumps(results, ensure_ascii=False, indent=2))
        else:
            for p in results:
                print(p['path'] if args.paths else p['title'] + '\n  ' + p['path'])
        return
    if args.list_categories:
        for category, description in sorted(catalog['categories'].items()):
            count = sum(p['category'] == category for p in catalog['problems'])
            if count:
                print(f'{category:46} {count:4}  {description}')
        return
    results = [p for p in catalog['problems'] if matches(p, args.query, args.category, args.tag, args.platform,
               args.language, args.role, args.needs_review) and (not args.suggested or p['classification_status'] == 'suggested')
               and (not args.pattern or any(field_matches(args.pattern, tag) for tag in p.get('patterns', [])))
               and (not args.changed or sha256(ROOT / p['path']) != classification_hash(p))]
    results.sort(key=lambda p: (p['category'], p['title'].casefold(), p['path']))
    shown = results if args.limit is None else results[:args.limit]
    if args.json:
        print(json.dumps(shown, ensure_ascii=False, indent=2))
    elif args.paths:
        for p in shown:
            print(p['path'])
    else:
        for p in shown:
            identity = ' / '.join(str(x) for x in [p.get('platform'), p.get('problem_id')] if x)
            print(p['title'] + (f' [{identity}]' if identity else ''))
            print('  ' + p['path'])
            print('  tags: ' + ', '.join(p['tags']) + ' | ' + p['classification_status'])
        print(f'{len(results)} match(es)' + (f'; showing {len(shown)}' if len(shown) != len(results) else ''))

if __name__ == '__main__':
    main()
