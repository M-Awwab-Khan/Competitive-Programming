#!/usr/bin/env python3
"""Extract marked, original C++ snippets from the speed-programming guide."""
import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GUIDE = ROOT / 'notes/contest-prep/div3-speed-programming.md'
HEADER = ROOT / 'templates/cpp/sp-reference.hpp'


def render(root=ROOT):
    snippets = re.findall(r'<!-- snippet:([a-z0-9-]+) -->\s*```cpp\n(.*?)\n```', (root / 'notes/contest-prep/div3-speed-programming.md').read_text(), re.S)
    names = [name for name, _ in snippets]
    if not snippets or len(set(names)) != len(names):
        raise ValueError('Expected nonempty, uniquely named C++ snippets')
    lines = ['// Generated from notes/contest-prep/div3-speed-programming.md.',
             '// Regenerate: python3 scripts/build_sp_reference.py',
             '// GNU C++17. Read the guide for preconditions; no global using-directive.',
             '#pragma once', '#include <bits/stdc++.h>', '', 'namespace sp {',
             'using namespace std;', 'using ll = long long;', 'using i128 = __int128_t;', '']
    for name, code in snippets:
        lines.extend(['// ' + name, code, ''])
    lines.append('} // namespace sp')
    return '\n'.join(lines) + '\n', names


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true', help='Read-only check that the header matches the guide')
    args = parser.parse_args()
    text, names = render()
    if args.check:
        if not HEADER.is_file() or HEADER.read_text() != text:
            parser.exit(1, 'Reference header is stale. Run python3 scripts/build_sp_reference.py\n')
        print(f'Header matches all {len(names)} marked snippets.')
    else:
        HEADER.write_text(text)
        print(f'Generated {HEADER.relative_to(ROOT)} from {len(names)} snippets.')


if __name__ == '__main__':
    main()
