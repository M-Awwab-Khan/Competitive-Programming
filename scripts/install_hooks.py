#!/usr/bin/env python3
"""Enable the repository's read-only structural pre-commit hook locally."""
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    result = subprocess.run(['git','config','--local','--get','core.hooksPath'],cwd=ROOT,text=True,capture_output=True)
    current = result.stdout.strip()
    if current and current != '.githooks':
        raise SystemExit('An existing hooksPath is configured: ' + current + '. Integrate the lint command with that hook before changing configuration.')
    default_hook = subprocess.check_output(['git','rev-parse','--git-path','hooks/pre-commit'],cwd=ROOT,text=True).strip()
    path = Path(default_hook)
    if not path.is_absolute():
        path = ROOT / path
    if not current and path.exists():
        raise SystemExit('An existing pre-commit hook is present. Add python3 scripts/lint_repo.py --staged to that hook.')
    subprocess.run(['git','config','--local','core.hooksPath','.githooks'],cwd=ROOT,check=True)
    print('Enabled .githooks/pre-commit for this checkout; staged files are checked without modifying the index.')


if __name__ == '__main__':
    main()
