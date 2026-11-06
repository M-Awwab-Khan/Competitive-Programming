"""Tests for parsing GCC Make dependency files across operating systems."""
import unittest

from scripts.cpp_build import make_words


class MakeDependencyTests(unittest.TestCase):
    def test_preserves_windows_separators_and_unescapes_make_words(self):
        entries = (r'C:\Users\mawwa\file.h '
                   r'C:\Users\mawwa\folder\ with\ spaces\header.h '
                   r'C:\Users\mawwa\AppData\Local\Temp\tmpdir\file.h '
                   r'C:\\escaped\\slashes.h build/a$$b.h')
        self.assertEqual(make_words(entries), [
            r'C:\Users\mawwa\file.h',
            r'C:\Users\mawwa\folder with spaces\header.h',
            r'C:\Users\mawwa\AppData\Local\Temp\tmpdir\file.h',
            r'C:\escaped\slashes.h',
            'build/a$b.h',
        ])
        self.assertEqual(make_words('one.h ' + chr(92) + '\n second.h'),
                         ['one.h', 'second.h'])


if __name__ == '__main__':
    unittest.main()
