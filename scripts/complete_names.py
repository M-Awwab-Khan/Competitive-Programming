#!/usr/bin/env python3
"""Problem-filename candidates for shell completion, with fuzzy ranking.

Usage: complete_names.py REPO_ROOT [QUERY]
Prints the mode ("prefix" or "fuzzy") on the first line, then one name per line.

Candidates are the NAME.cpp / NAME.py files `make` can resolve: sources still in
practice/inbox/NAME/ and filed sources whose catalog original_path is there.

Matching: if any name starts with QUERY (case-insensitive) the plain prefix
matches are returned alphabetically, so the shell can still extend a prefix.
Otherwise names containing QUERY's letters in order (case-insensitive) are
returned best first, scored like an editor's quick-open: consecutive letters
and letters at word starts score higher, gaps and long names lower.
"""
import json
import sys
from pathlib import Path

SEPARATORS = '_-. '
NEG = float('-inf')


def candidate_names(root):
    root = Path(root)
    names = set()
    inbox = root / 'practice/inbox'
    if inbox.is_dir():
        for folder in inbox.iterdir():
            if folder.is_dir():
                names.update(f.name for f in folder.glob(folder.name + '.*') if f.suffix in ('.cpp', '.py'))
    try:
        catalog = json.loads((root / 'catalog/problems.json').read_text(encoding='utf-8'))
        for problem in catalog['problems']:
            parts = Path(problem['original_path']).parts
            if len(parts) == 4 and parts[:2] == ('practice', 'inbox') and parts[3].rsplit('.', 1)[-1] in ('cpp', 'py'):
                names.add(parts[3])
    except (OSError, ValueError, KeyError):
        pass
    return sorted(names)


def _word_start(name, j):
    if j == 0 or name[j - 1] in SEPARATORS:
        return True
    return name[j - 1].islower() and name[j].isupper()


def score(query, name):
    """Best alignment score of query as a case-insensitive subsequence of name, or None."""
    q, n = query.lower(), name.lower()
    if not q:
        return 0.0
    previous = None
    for i, ch in enumerate(q):
        current = [NEG] * len(n)
        for j, nc in enumerate(n):
            if nc != ch:
                continue
            gain = 1.0 + (1.0 if name[j] == query[i] else 0.0)
            if _word_start(name, j):
                gain += 8.0 + (4.0 if j == 0 else 0.0)
            if previous is None:
                current[j] = gain
                continue
            best = NEG
            for k in range(j):
                if previous[k] == NEG:
                    continue
                link = 6.0 if k == j - 1 else -1.0 * min(j - k - 1, 5)
                best = max(best, previous[k] + link)
            if best != NEG:
                current[j] = best + gain
        if all(value == NEG for value in current):
            return None
        previous = current
    return max(previous)


def rank(names, query):
    """Return (mode, ordered names)."""
    if not query:
        return 'prefix', sorted(names)
    lowered = query.lower()
    prefixed = sorted(n for n in names if n.lower().startswith(lowered))
    if prefixed:
        return 'prefix', prefixed
    scored = []
    for name in names:
        value = score(query, name)
        if value is not None:
            scored.append((-value, len(name), name))
    scored.sort()
    return 'fuzzy', [name for _, _, name in scored]


def main(argv):
    root = argv[1] if len(argv) > 1 else '.'
    query = argv[2] if len(argv) > 2 else ''
    mode, names = rank(candidate_names(root), query)
    print(mode)
    print('\n'.join(names))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
