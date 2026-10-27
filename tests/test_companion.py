"""Companion protocol and Make workflow integration in temporary repositories."""
import copy
import http.client
import json
import os
from pathlib import Path
import queue
import shutil
import subprocess
import sys
import tempfile
import threading
import unittest

REPO = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO / 'scripts'))
from companion import CHROME_ORIGIN, choose_language, import_problem, make_server, problem_name


class CompanionTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for folder in ('scripts', 'templates', 'bits'):
            shutil.copytree(REPO / folder, self.root / folder)
        shutil.copy(REPO / 'Makefile', self.root)
        (self.root / 'catalog').mkdir()
        (self.root / 'catalog/problems.json').write_text('{"problems": []}')
        self.payload = dict(name='A. Example', url='https://codeforces.com/contest/123/problem/A',
                            group='Codeforces', interactive=False,
                            tests=[dict(input='2\n', output='4\n'), dict(input='3\n', output='6\n')])

    def make(self, action, source, **env):
        variables = os.environ.copy()
        variables.update(env)
        return subprocess.run(['make', action, source.name, 'PCH=0'], cwd=self.root,
                              env=variables, capture_output=True, text=True, timeout=40)

    def test_multisample_python_pass_mismatch_and_runtime_failure(self):
        source = import_problem(self.payload, 'py', self.root)
        source.write_text('print(int(input()) * 2)\n')
        result = self.make('check', source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.count('PASS'), 2)
        self.assertEqual((source.parent / '2.output.txt').read_text(), '6\n')
        (source.parent / '1.expected.txt').write_text('wrong\n')
        result = self.make('check', source)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('2.in', result.stdout)  # Check continues after a failed sample.
        source.write_text('raise SystemExit(3)\n')
        self.assertNotEqual(self.make('run', source).returncode, 0)

    @unittest.skipUnless(shutil.which('g++'), 'g++ unavailable')
    def test_cpp_multiple_samples(self):
        source = import_problem(self.payload, 'cpp', self.root)
        source.write_text('#include "bits/stdc++.h"\nint main(){int n;std::cin>>n;std::cout<<n*2<<"\\n";}\n')
        result = self.make('check', source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.count('PASS'), 2)

    def test_single_sample_legacy_new_and_timeout(self):
        self.payload['tests'] = self.payload['tests'][:1]
        source = import_problem(self.payload, 'py', self.root)
        source.write_text('print(int(input()) * 2)\n')
        self.assertEqual(self.make('check', source).returncode, 0)
        self.assertTrue((source.parent / 'input.txt').exists())
        source.write_text('while True: pass\n')
        result = self.make('check', source, CP_RUN_TIMEOUT='0.05', RUN_TIMEOUT='0.05')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('RUN_TIMEOUT', result.stderr)
        result = self.make('new', Path('manual.py'))
        self.assertEqual(result.returncode, 0, result.stderr)
        manual = self.root / 'practice/inbox/manual/manual.py'
        manual.write_text('print(input())\n')
        (manual.parent / 'input.txt').write_text('hello\n')
        (manual.parent / 'expected.txt').write_text('hello\n')
        self.assertEqual(self.make('check', manual).returncode, 0)

    def test_preservation_validation_names_and_language_prompt(self):
        self.payload['tests'][0]['input'] = ' 2\r\n\n'
        first = import_problem(self.payload, 'cpp', self.root)
        first.write_text('// my work\n')
        second = import_problem(self.payload, 'py', self.root)
        self.assertNotEqual(first.parent, second.parent)
        self.assertEqual(first.read_text(), '// my work\n')
        self.assertEqual((first.parent / '1.in').read_bytes(), b' 2\r\n\n')
        self.assertEqual(json.loads((first.parent / 'problem.json').read_text()), self.payload)
        self.assertEqual(first.stem, 'Example')
        self.payload['url'] = 'https://vjudge.net/contest/123#problem/B'
        self.assertEqual(import_problem(self.payload, 'py', self.root).stem, 'Example-attempt-3')
        answers = iter(['', 'java', 'python'])
        self.assertEqual(choose_language(self.payload, lambda _: next(answers)), 'py')
        self.assertIsNone(choose_language(self.payload, lambda _: 's'))
        bad = copy.deepcopy(self.payload)
        bad['tests'][0]['output'] = None
        with self.assertRaises(ValueError):
            import_problem(bad, 'cpp', self.root)

    def test_readable_title_names(self):
        for title, expected in [
                ('Y. Number of Ways', 'Number_of_Ways'),
                ('k-th divisor', 'k-th_divisor'),
                ('A1. Café / two: paths?', 'Cafe_two_paths'),
                ('../../', 'problem'),
                ('A' * 200, 'A' * 100)]:
            with self.subTest(title=title):
                self.assertEqual(problem_name(dict(self.payload, name=title)), expected)

    def test_http_acknowledges_before_prompt_and_rejects_invalid_requests(self):
        pending = queue.Queue(maxsize=1)
        server = make_server(pending, 0)
        thread = threading.Thread(target=server.serve_forever, daemon=True)
        thread.start()
        self.addCleanup(thread.join)
        self.addCleanup(server.server_close)
        self.addCleanup(server.shutdown)
        def post(data, origin=CHROME_ORIGIN):
            conn = http.client.HTTPConnection('127.0.0.1', server.server_port, timeout=3)
            try:
                conn.request('POST', '/', data, {'Content-Type': 'application/json', 'Origin': origin})
                response = conn.getresponse()
                response.read()
                return response.status
            finally:
                conn.close()
        self.assertEqual(post(json.dumps(self.payload)), 200)
        self.assertEqual(post(json.dumps(self.payload)), 503)
        self.assertEqual(pending.get_nowait(), self.payload)
        self.assertEqual(post('{broken'), 400)
        self.assertEqual(post(json.dumps(self.payload), 'https://example.org'), 403)
        self.assertTrue(pending.empty())

    def test_sample_selection_listing_and_append_after_filing(self):
        source = import_problem(self.payload, 'py', self.root)
        source.write_text('print(int(input()) * 2)\n')
        (source.parent / '1.expected.txt').write_text('incorrect\n')
        result = self.make('check', source, SAMPLE='2')
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.count('PASS'), 1)
        self.assertNotEqual(self.make('check', source, SAMPLE='99').returncode, 0)
        self.assertNotEqual(self.make('run', source, SAMPLE='../2').returncode, 0)
        self.assertIn('Sample 2: 2.in', self.make('samples', source).stdout)
        original = source.relative_to(self.root).as_posix()
        target = self.root / 'solutions/math' / source.name
        target.parent.mkdir(parents=True)
        source.rename(target)
        (self.root / 'catalog/problems.json').write_text(json.dumps({'problems': [
            {'path': target.relative_to(self.root).as_posix(), 'original_path': original}]}))
        input_file, expected_file = self.root / 'custom.in', self.root / 'custom.txt'
        input_file.write_bytes(b' 9\r\n')
        expected_file.write_bytes(b'18\r\n')
        result = self.make('sample-add', target, INPUT=str(input_file), EXPECTED=str(expected_file))
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        workspace = self.root / Path(original).parent
        self.assertEqual((workspace / '3.in').read_bytes(), b' 9\r\n')
        self.assertEqual((workspace / '3.expected.txt').read_bytes(), b'18\r\n')
        self.assertFalse((target.parent / '3.in').exists())
        self.assertEqual(self.make('check', target, SAMPLE='3').returncode, 0)

    def test_adding_to_single_sample_preserves_original_and_placeholder(self):
        self.payload['tests'] = self.payload['tests'][:1]
        source = import_problem(self.payload, 'py', self.root)
        files = {p.name: p.read_bytes() for p in source.parent.iterdir() if p.is_file()}
        custom_input, custom_expected = self.root / 'custom.in', self.root / 'custom.txt'
        custom_input.write_text('10\n')
        custom_expected.write_text('20\n')
        result = self.make('sample-add', source, INPUT=str(custom_input), EXPECTED=str(custom_expected))
        self.assertEqual(result.returncode, 0, result.stderr)
        for name, content in files.items():
            self.assertEqual((source.parent / name).read_bytes(), content)
        self.assertEqual((source.parent / '1.in').read_bytes(), files['input.txt'])
        self.assertEqual((source.parent / '2.in').read_text(), '10\n')
        self.assertNotEqual(self.make('sample-add', source, INPUT='missing', EXPECTED=str(custom_expected)).returncode, 0)
        self.assertFalse((source.parent / '3.in').exists())
        self.assertEqual(self.make('new', Path('manual.py')).returncode, 0)
        result = self.make('sample-add', Path('manual.py'), INPUT=str(custom_input), EXPECTED=str(custom_expected))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue((self.root / 'practice/inbox/manual/1.in').is_file())
        self.assertFalse((self.root / 'practice/inbox/manual/2.in').exists())

    @unittest.skipUnless(shutil.which('g++'), 'g++ unavailable')
    def test_debug_colored_helpers_and_separate_release_cache(self):
        source = import_problem(self.payload, 'cpp', self.root)
        text = source.read_text().replace('// Write your solution here.',
            'int n; cin >> n; vector<vector<int>> rows = {{n}}; '
            'debug(n, rows); int a[] = {n, n+1}; debugArr(a, 2); cout << n*2 << "\\n";')
        source.write_text(text)
        release = self.make('check', source)
        self.assertEqual(release.returncode, 0, release.stdout + release.stderr)
        self.assertNotIn('\x1b[', release.stderr)
        debug = self.make('debug', source, SAMPLE='2')
        self.assertEqual(debug.returncode, 0, debug.stdout + debug.stderr)
        self.assertIn('\x1b[', debug.stderr)
        self.assertIn('rows', debug.stderr)
        self.assertNotIn('\x1b[', (source.parent / '2.output.txt').read_text())
        self.assertEqual(debug.stdout.count('PASS'), 1)
        release = self.make('check', source)
        self.assertEqual(release.returncode, 0, release.stdout + release.stderr)
        self.assertNotIn('Compiling', release.stdout)
        self.assertNotIn('\x1b[', release.stderr)
        source.write_text('#include "bits/stdc++.h"\nint main(){volatile int x=INT_MAX;std::cout<<x+1;}\n')
        debug = self.make('debug', source, SAMPLE='1')
        self.assertNotEqual(debug.returncode, 0)
        self.assertIn('signed integer overflow', debug.stderr)

    def test_filed_source_retains_numbered_samples(self):
        source = import_problem(self.payload, 'py', self.root)
        source.write_text('print(int(input()) * 2)\n')
        original = source.relative_to(self.root).as_posix()
        target = self.root / 'solutions/math' / source.name
        target.parent.mkdir(parents=True)
        source.rename(target)
        (self.root / 'catalog/problems.json').write_text(json.dumps({'problems': [
            {'path': target.relative_to(self.root).as_posix(), 'original_path': original}]}))
        result = self.make('check', target)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.count('PASS'), 2)


if __name__ == '__main__':
    unittest.main()
