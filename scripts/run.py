#!/usr/bin/env python3
"""Compile/run a catalog source or a scratch file, keeping generated output in build/."""
import argparse
import hashlib
import json
import os
import shlex
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def resolve_source(value):
    direct = Path(value).expanduser()
    if direct.is_file():
        return direct.resolve()
    if not direct.is_absolute() and (ROOT / direct).is_file():
        return (ROOT / direct).resolve()
    catalog = json.loads((ROOT / 'catalog/problems.json').read_text())
    matches = [ROOT / p['path'] for p in catalog['problems']
               if p['original_path'] == value or Path(p['path']).name == value]
    if len(matches) == 1:
        return matches[0]
    if len(matches) > 1:
        raise ValueError('Ambiguous filename; use a full path:\n' + '\n'.join(str(p) for p in matches))
    raise ValueError('Source not found: ' + value)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', help='Current path, original path, or unique filename')
    parser.add_argument('--cwd', type=Path, default=ROOT / 'practice', help='Runtime directory (default: practice/)')
    parser.add_argument('args', nargs='*', help='Program arguments after --')
    args = parser.parse_args()
    try:
        source = resolve_source(args.source)
    except ValueError as exc:
        parser.error(str(exc))
    cwd = args.cwd.resolve()
    if not cwd.is_dir():
        parser.error('Runtime directory does not exist: ' + str(cwd))
    if source.suffix == '.cpp':
        build = ROOT / 'build'
        build.mkdir(exist_ok=True)
        suffix = '.exe' if os.name == 'nt' else ''
        key = hashlib.sha256(str(source).encode()).hexdigest()[:10]
        binary = build / (source.stem + '-' + key + suffix)
        command = shlex.split(os.environ.get('CXX', 'g++'))
        command += ['-std=c++23', '-O2', '-I', str(ROOT), str(source), '-o', str(binary)]
        result = subprocess.run(command, cwd=ROOT)
        if result.returncode:
            raise SystemExit(result.returncode)
        command = [str(binary)]
    elif source.suffix == '.py':
        import sys
        command = [sys.executable, str(source)]
    else:
        parser.error('Expected a .cpp or .py source')
    program_args = args.args[1:] if args.args[:1] == ['--'] else args.args
    raise SystemExit(subprocess.run(command + program_args, cwd=cwd).returncode)

if __name__ == '__main__':
    main()
