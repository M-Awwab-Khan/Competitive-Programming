"""Checks for the spaced-repetition drill: scheduling, teaching order, and saved sessions."""
import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from datetime import date
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO / 'scripts'))
import drill

TODAY = date(2026, 1, 10)


class ScheduleTests(unittest.TestCase):
    def test_good_answers_grow_intervals(self):
        card, intervals = None, []
        for _ in range(5):
            card = drill.schedule(card, 'good', TODAY)
            intervals.append(card['interval'])
        self.assertEqual(intervals[:2], [1, 3])
        self.assertTrue(all(b > a for a, b in zip(intervals, intervals[1:])))

    def test_again_resets_and_lowers_ease(self):
        card = drill.schedule(drill.schedule(None, 'good', TODAY), 'good', TODAY)
        lapsed = drill.schedule(card, 'again', TODAY)
        self.assertEqual((lapsed['interval'], lapsed['reps'], lapsed['lapses']), (1, 0, 1))
        self.assertLess(lapsed['ease'], card['ease'])
        self.assertEqual(lapsed['due'], '2026-01-11')

    def test_ease_has_a_floor(self):
        card = None
        for _ in range(20):
            card = drill.schedule(card, 'again', TODAY)
        self.assertEqual(card['ease'], drill.MIN_EASE)


class CardTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.cards, cls.titles = drill.build_cards(REPO)

    def test_every_registered_pattern_has_a_card_with_clues(self):
        registry = json.loads((REPO / 'catalog/patterns.json').read_text())['patterns']
        pattern_cards = {c['pattern']: c for c in self.cards if c['kind'] == 'pattern'}
        self.assertEqual(set(pattern_cards), {p['id'] for p in registry})
        for card in pattern_cards.values():
            self.assertTrue(card['clues'] or card['summary'], card['pattern'])
            self.assertNotIn('examples:start', card['clues'] + card['invariant'] + card['mistakes'])

    def test_problem_cards_are_reviewed_with_registered_patterns(self):
        problems = [c for c in self.cards if c['kind'] == 'problem']
        self.assertTrue(problems)
        for card in problems:
            self.assertTrue(card['evidence'])
            self.assertTrue(set(card['patterns']) <= set(self.titles))

    def test_new_problem_follows_its_pattern(self):
        due, new = drill.pick_session(self.cards, {'cards': {}, 'log': {}}, TODAY, 30, 50, seed=1)
        self.assertEqual(due, [])
        introduced = set()
        for card in new:
            if card['kind'] == 'pattern':
                introduced.add(card['pattern'])
            else:
                self.assertTrue(introduced & set(card['patterns']), card['title'])

    def test_pattern_filter(self):
        _, new = drill.pick_session(self.cards, {'cards': {}, 'log': {}}, TODAY, 5, 50, pattern='dsu-variants')
        self.assertEqual(new[0]['id'], 'p:dsu-variants')
        self.assertTrue(all('dsu-variants' in (c.get('patterns') or [c.get('pattern')]) for c in new))


class SessionTests(unittest.TestCase):
    def test_session_saves_answers_and_requeues_lapses(self):
        cards, titles = drill.build_cards(REPO)
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'state.json'
            state = drill.load_state(path)
            answers = iter(['\n', '3\n', '\n', '1\n', '\n', '3\n', '\n', '3\n', ''])
            args = type('Args', (), dict(new=2, max=50, pattern=None))
            with redirect_stdout(io.StringIO()):
                drill.run_session(cards, titles, state, path, TODAY, args, read=lambda: next(answers))
            saved = json.loads(path.read_text())
            self.assertEqual(len(saved['cards']), 2)
            self.assertEqual(saved['log']['2026-01-10'], {'again': 1, 'hard': 0, 'good': 2, 'easy': 0})
            self.assertEqual(sorted(c['lapses'] for c in saved['cards'].values() if 'lapses' in c), [1])


if __name__ == '__main__':
    unittest.main()
