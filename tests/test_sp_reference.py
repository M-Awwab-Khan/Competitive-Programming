"""Check that copy-ready guide snippets stay synchronized and work on small oracles."""
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


class SpeedProgrammingReferenceTests(unittest.TestCase):
    def test_header_matches_guide(self):
        result = subprocess.run([sys.executable, 'scripts/build_sp_reference.py', '--check'],
                                cwd=ROOT, text=True, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    @unittest.skipUnless(shutil.which('g++'), 'GNU C++ compiler unavailable')
    def test_cpp17_snippets_against_boundaries_and_small_oracles(self):
        with tempfile.TemporaryDirectory(prefix='sp-reference-check-') as tmp:
            binary = Path(tmp) / 'checks'
            result = subprocess.run(['g++', '-std=c++17', '-O2', '-Wall', '-Wextra',
                                     '-I', str(ROOT / 'templates/cpp'),
                                     str(ROOT / 'tests/sp_reference_checks.cpp'), '-o', str(binary)],
                                    text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], text=True, capture_output=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn('All cheat-sheet snippet checks passed.', result.stdout)


if __name__ == '__main__':
    unittest.main()
