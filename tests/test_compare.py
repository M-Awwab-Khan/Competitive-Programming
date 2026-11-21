import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import compare  # noqa: E402


class CompareTests(unittest.TestCase):
    def test_whitespace_is_ignored(self):
        self.assertTrue(compare.matches(b'1 2\n3\n', b'1\n2 3', None))
        self.assertTrue(compare.layout_differs(b'1 2\n3\n', b'1\n2 3'))
        self.assertFalse(compare.layout_differs(b'1 2\n3\n\n', b'1 2\n3'))

    def test_tolerance_is_opt_in(self):
        self.assertFalse(compare.matches(b'1.0', b'1.0000001'))
        self.assertTrue(compare.matches(b'1.0', b'1.0000001', 1e-6))
        self.assertFalse(compare.matches(b'1.0', b'1.01', 1e-6))
        self.assertFalse(compare.matches(b'abc', b'abd', 1e-6))
        self.assertFalse(compare.matches(b'nan', b'nan1', 1e-6))
        with self.assertRaises(ValueError):
            compare.parse_eps('0')
        self.assertIsNone(compare.parse_eps(''))

    def test_diagnosis(self):
        self.assertIn('empty', compare.diagnose(b'1', b'')[0])
        self.assertIn('ends early', compare.diagnose(b'1 2 3', b'1 2')[0])
        self.assertIn('extra output', compare.diagnose(b'1', b'1 2')[0])
        notes = compare.diagnose(b'3\n1 2 3\n', b'3\n1 2 4\n')
        self.assertIn('expected line 2, token 3: expected 3, got 4', notes[0])
        self.assertIn('off by one', notes)
        self.assertTrue(any('letter case' in n for n in compare.diagnose(b'YES', b'Yes')))
        self.assertTrue(any('order' in n for n in compare.diagnose(b'1 2', b'2 1')))
        self.assertTrue(any('EPS=' in n for n in compare.diagnose(b'1.0', b'1.0001')))

    def test_report_pass_and_fail(self):
        ok, text = compare.report(b'1\n', b'1\n', 'e', 'o')
        self.assertTrue(ok)
        self.assertEqual(text.count('PASS'), 1)
        ok, text = compare.report(b'1\n2\n', b'1\n3\n', 'e', 'o')
        self.assertFalse(ok)
        self.assertNotIn('PASS', text)
        self.assertIn('[2]', text)
        self.assertIn('[3]', text)
        self.assertNotIn('\x1b[', text)

    def test_color_only_when_requested(self):
        self.assertIn('\x1b[', compare.report(b'1', b'2', 'e', 'o', color=True)[1])

    def test_table_limits_and_missing_lines(self):
        wanted = b''.join(b'%d\n' % i for i in range(30))
        actual = b''.join(b'%d\n' % (i + 1) for i in range(30))
        text = compare.report(wanted, actual, 'e', 'o')[1]
        self.assertIn('and 25 more differing lines', text)
        verbose = compare.report(wanted, actual, 'e', 'o', verbose=True)[1]
        self.assertNotIn('more differing', verbose)
        short = compare.report(b'1\n2\n', b'1\n', 'e', 'o')[1]
        self.assertIn('(no line)', short)

    def test_long_lines_keep_the_difference_visible(self):
        wanted = b' '.join(b'%d' % i for i in range(200)) + b'\n'
        actual = wanted.replace(b' 150 ', b' 999 ')
        text = compare.report(wanted, actual, 'e', 'o')[1]
        self.assertIn('[150]', text)
        self.assertIn('[999]', text)

    def test_unified_style(self):
        text = compare.report(b'1\n', b'2\n', 'e', 'o', style='unified')[1]
        self.assertIn('--- e', text)
        self.assertIn('+2', text)


if __name__ == '__main__':
    unittest.main()
