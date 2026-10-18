#!/usr/bin/env python3
"""Create and run standalone practice problems without CPH."""
import argparse
import difflib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

from cpp_build import build, prepare_pch

ROOT = Path(__file__).resolve().parents[1]
LANGUAGES = {'cpp': 'cpp', 'c++': 'cpp', 'cc': 'cpp', 'py': 'py', 'python': 'py', 'python3': 'py'}
HELP = """Problem workflow (run from the repository root):
  make new NAME=A_Line_Trip LANG=cpp   Create source, input.txt, output.txt, expected.txt
  make new NAME=B LANG=python         Python starter (cpp is the default)
  make run NAME=A_Line_Trip           Read input.txt; write and show output.txt
  make check NAME=A_Line_Trip         Run and compare with expected.txt (ignores whitespace)
  make build NAME=A_Line_Trip         Compile C++; Python needs no build
  make pch                           Precompile bits/stdc++.h for GCC
  make ingest                        Preview filing all new/changed solutions
  make ingest-apply                  Apply filing; keep samples in their workspace
  make lint                          Check catalog, links, generated files

Workspaces: practice/inbox/NAME/NAME.cpp (or .py).
Select a language with LANG if a workspace contains both implementations.
Use SOURCE=path/to/file.cpp to run/build an existing source with the same file I/O.
CXX=g++ CXXFLAGS='-std=c++23 -O2 -pipe' CPPFLAGS='' PCH=1 are configurable.
Use PCH=0 for ordinary compilation, including with Clang. First PCH build costs extra.
No files are overwritten by new. There is no implicit ingestion or commit.
"""


def name_from_env():
    name = os.environ.get('CP_NAME', '')
    if not re.fullmatch(r'[A-Za-z0-9][A-Za-z0-9_-]*', name):
        raise ValueError('Set NAME to a name using letters, digits, underscores or hyphens.')
    return name


def language():
    value = os.environ.get('CP_LANG', 'cpp').lower()
    if value not in LANGUAGES:
        raise ValueError('Supported languages: cpp/c++ and py/python.')
    return LANGUAGES[value]


def create():
    name, lang = name_from_env(), language()
    workspace = ROOT / 'practice/inbox' / name
    template = ROOT / 'templates' / ('cpp/problem.cpp' if lang == 'cpp' else 'python/problem.py')
    content = template.read_bytes()
    workspace.parent.mkdir(parents=True, exist_ok=True)
    # mkdir refuses existing folders, preserving all previous work and samples.
    workspace.mkdir()
    try:
        source = workspace / (name + '.' + lang)
        source.write_bytes(content)
        for filename in ('input.txt', 'output.txt', 'expected.txt'):
            (workspace / filename).write_bytes(b'')
    except BaseException:
        shutil.rmtree(workspace)
        raise
    print('Created ' + str(source.relative_to(ROOT)))
    print('Edit input.txt and expected.txt in ' + str(workspace.relative_to(ROOT)))


def select():
    explicit = os.environ.get('CP_SOURCE', '')
    if explicit:
        from run import resolve_source
        source = resolve_source(explicit)
        return source, source.parent
    name, lang = name_from_env(), language()
    workspace = ROOT / 'practice/inbox' / name
    relative = str((workspace / (name + '.' + lang)).relative_to(ROOT))
    source = ROOT / relative
    if not source.is_file():
        # Filing moves only source code. Original paths preserve access to its samples.
        catalog = json.loads((ROOT / 'catalog/problems.json').read_text())
        matches = [ROOT / p['path'] for p in catalog['problems'] if p['original_path'] == relative]
        if len(matches) != 1:
            raise ValueError('Problem not found; use make new NAME=... LANG=... or SOURCE=...')
        source = matches[0]
    if not workspace.is_dir():
        raise ValueError('Sample workspace is missing: ' + str(workspace))
    return source, workspace


def run(action):
    source, workspace = select()
    if source.suffix == '.cpp':
        command = [str(build(source, use_pch=os.environ.get('CP_PCH', '1') != '0'))]
    elif source.suffix == '.py':
        command = [sys.executable, str(source)]
    else:
        raise ValueError('Expected a .cpp or .py source.')
    if action == 'build':
        print('Ready: ' + str(source.relative_to(ROOT)))
        return 0
    expected = workspace / 'expected.txt'
    if action == 'check' and not expected.is_file():
        raise ValueError('Create expected.txt in ' + str(workspace))
    # Open input first, so a missing input never truncates previous output.
    with (workspace / 'input.txt').open('rb') as stdin:
        with (workspace / 'output.txt').open('wb') as stdout:
            result = subprocess.run(command, stdin=stdin, stdout=stdout, cwd=workspace)
    actual = (workspace / 'output.txt').read_bytes()
    sys.stdout.flush()
    sys.stdout.buffer.write(actual)
    sys.stdout.buffer.flush()
    if result.returncode:
        print('\nProgram exited with code ' + str(result.returncode), file=sys.stderr)
        return result.returncode if result.returncode > 0 else 1
    if action == 'check':
        wanted = expected.read_bytes()
        if actual.split() != wanted.split():
            print('\nOutput differs from expected.txt:', file=sys.stderr)
            print(''.join(difflib.unified_diff(wanted.decode(errors='replace').splitlines(True),
                                             actual.decode(errors='replace').splitlines(True),
                                             fromfile='expected.txt', tofile='output.txt')), file=sys.stderr)
            return 1
        print('\nPASS (whitespace-separated tokens match; no floating-point tolerance)')
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=['help', 'new', 'build', 'run', 'check', 'pch'])
    args = parser.parse_args()
    try:
        if args.action == 'help':
            print(HELP)
        elif args.action == 'new':
            create()
        elif args.action == 'pch':
            print('Ready: ' + str(prepare_pch().relative_to(ROOT)))
        else:
            return run(args.action)
    except (ValueError, OSError, subprocess.CalledProcessError) as exc:
        print('Error: ' + str(exc), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
