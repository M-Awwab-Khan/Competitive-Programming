import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import complete_names as cn  # noqa: E402

NAMES = [
    'Rectangle_Sum.cpp', 'Rectangle_Additions.cpp', 'Range_Additions.cpp',
    'Weighted_Range_Sum.cpp', 'Subarrays_with_a_Given_Sum.cpp', 'Room_Allocation.cpp',
    'Binary_Search.cpp', 'Fast_search.cpp', 'A_Line_Trip.py',
]


class FuzzyTests(unittest.TestCase):
    def test_empty_query_lists_everything_alphabetically(self):
        mode, names = cn.rank(NAMES, '')
        self.assertEqual(mode, 'prefix')
        self.assertEqual(names, sorted(NAMES))

    def test_prefix_mode_wins_when_something_starts_with_the_query(self):
        mode, names = cn.rank(NAMES, 'rect')
        self.assertEqual(mode, 'prefix')
        self.assertEqual(names, ['Rectangle_Additions.cpp', 'Rectangle_Sum.cpp'])

    def test_subsequence_matches_are_case_insensitive(self):
        mode, names = cn.rank(NAMES, 'rctsum')
        self.assertEqual((mode, names), ('fuzzy', ['Rectangle_Sum.cpp']))

    def test_non_matches_are_excluded(self):
        self.assertEqual(cn.rank(NAMES, 'zzz'), ('fuzzy', []))
        self.assertIsNone(cn.score('sumx', 'Rectangle_Sum.cpp'))
        self.assertIsNone(cn.score('mus', 'Sum.cpp'))

    def test_word_starts_and_consecutive_letters_rank_higher(self):
        # "sum" is a word at the end of all three; the shortest name wins ties.
        _, names = cn.rank(NAMES, 'sum')
        self.assertEqual(names[0], 'Rectangle_Sum.cpp')
        self.assertEqual(set(names), {'Rectangle_Sum.cpp', 'Weighted_Range_Sum.cpp',
                                      'Subarrays_with_a_Given_Sum.cpp'})
        _, names = cn.rank(NAMES, 'ra')
        # "Range_Additions" starts a word at R and A; "Room_Allocation" has R,A word starts too.
        self.assertIn(names[0], {'Range_Additions.cpp', 'Room_Allocation.cpp'})
        self.assertGreater(cn.score('wrs', 'Weighted_Range_Sum.cpp'),
                           cn.score('wrs', 'Wxxxxxxxxxxxxrxxxxxxxxxxs.cpp'))

    def test_best_alignment_is_used_not_the_leftmost(self):
        self.assertGreater(cn.score('sum', 'Subarrays_with_a_Given_Sum.cpp'),
                           cn.score('sum', 'Subarrays_with_a_Given_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxsxxuxxm.cpp'))

    def test_extension_and_separators_can_be_typed(self):
        self.assertEqual(cn.rank(NAMES, 'trip.py')[1], ['A_Line_Trip.py'])
        self.assertEqual(set(cn.rank(NAMES, 'srch')[1]), {'Binary_Search.cpp', 'Fast_search.cpp'})

    def test_candidate_discovery(self):
        import json
        import tempfile
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'practice/inbox/Foo_Bar').mkdir(parents=True)
            (root / 'practice/inbox/Foo_Bar/Foo_Bar.cpp').write_text('')
            (root / 'practice/inbox/Foo_Bar/input.txt').write_text('')
            (root / 'catalog').mkdir()
            (root / 'catalog/problems.json').write_text(json.dumps({'problems': [
                {'original_path': 'practice/inbox/Filed_One/Filed_One.py'},
                {'original_path': 'ext/other.cpp'},
            ]}))
            self.assertEqual(cn.candidate_names(root), ['Filed_One.py', 'Foo_Bar.cpp'])


if __name__ == '__main__':
    unittest.main()
