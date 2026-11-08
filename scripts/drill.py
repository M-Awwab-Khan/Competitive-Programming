#!/usr/bin/env python3
"""Spaced-repetition drill over pattern notes and reviewed solutions.

Two card types:
  pattern card  front: recognition clues of a note      back: name, invariant, common mistakes
  problem card  front: title, platform, link           back: key idea, patterns, category, file

A problem card is introduced only after the card for one of its patterns, so you learn the
idea before being quizzed on its examples. Scheduling is SM-2: again / hard / good / easy.
Progress lives in drill/state.json (plain JSON, safe to commit and sync).
"""
import argparse
import json
import os
import random
import re
import sys
import tempfile
from datetime import date, timedelta
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_STATE = ROOT / 'drill' / 'state.json'
GRADES = {'1': 'again', '2': 'hard', '3': 'good', '4': 'easy'}
MIN_EASE, START_EASE = 1.3, 2.5


# ---------------------------------------------------------------- scheduling

def schedule(card, grade, today):
    """Return the updated SM-2 record for one answer. Pure function of its inputs."""
    card = dict(card or {})
    ease = card.get('ease', START_EASE)
    interval = card.get('interval', 0)
    reps = card.get('reps', 0)
    if grade == 'again':
        card['lapses'] = card.get('lapses', 0) + 1
        ease, reps, interval = max(MIN_EASE, ease - 0.2), 0, 1
    else:
        if reps == 0:
            interval = {'hard': 1, 'good': 1, 'easy': 3}[grade]
        elif reps == 1:
            interval = {'hard': 2, 'good': 3, 'easy': 5}[grade]
        else:
            factor = {'hard': 1.2, 'good': ease, 'easy': ease * 1.3}[grade]
            interval = max(interval + 1, round(interval * factor))
        ease += {'hard': -0.15, 'good': 0.0, 'easy': 0.15}[grade]
        ease = max(MIN_EASE, ease)
        reps += 1
    card.update(ease=round(ease, 3), interval=interval, reps=reps,
                due=(today + timedelta(days=interval)).isoformat(),
                last=today.isoformat(), seen=card.get('seen', 0) + 1)
    return card


# ---------------------------------------------------------------- cards

def note_sections(text):
    """Split a pattern note into {heading: body}, dropping the generated examples block."""
    text = re.sub(r'<!-- examples:start -->.*?<!-- examples:end -->', '', text, flags=re.S)
    sections, current = {}, '_intro'
    for line in text.splitlines():
        if line.startswith('# '):
            sections['_title'] = line[2:].strip()
            continue
        if line.startswith('## '):
            current = line[3:].strip().lower()
            continue
        sections.setdefault(current, []).append(line)
    return {k: (v if isinstance(v, str) else '\n'.join(v).strip()) for k, v in sections.items()}


def section(sections, *prefixes):
    for key, body in sections.items():
        if any(key.startswith(p) for p in prefixes):
            return body
    return ''


def clip(text, lines):
    rows = text.splitlines()
    return '\n'.join(rows[:lines] + (['  ...'] if len(rows) > lines else []))


def strip_links(text):
    return re.sub(r'\[([^\]]+)\]\([^)]+\)', r'\1', text)


def build_cards(root=ROOT, include_unpatterned=False):
    catalog = json.loads((root / 'catalog/problems.json').read_text())
    patterns = json.loads((root / 'catalog/patterns.json').read_text())['patterns']
    titles = {p['id']: p['title'] for p in patterns}
    counts = {}
    problems = []
    for p in catalog['problems']:
        if p.get('classification_status') != 'reviewed' or not p.get('classification_evidence'):
            continue
        pats = [x for x in p.get('patterns', []) if x in titles]
        if not pats and not include_unpatterned:
            continue
        for x in pats:
            counts[x] = counts.get(x, 0) + 1
        problems.append(dict(id='s:' + p['key'], kind='problem', title=p['title'], platform=p.get('platform') or '',
                             urls=p.get('urls') or [], path=p['path'], category=p['category'],
                             patterns=pats, evidence=p['classification_evidence']))
    cards = []
    for p in patterns:
        path = root / p['path']
        if not path.exists():
            continue
        s = note_sections(path.read_text())
        cards.append(dict(id='p:' + p['id'], kind='pattern', pattern=p['id'], title=p['title'], path=p['path'],
                          examples=counts.get(p['id'], 0),
                          clues=strip_links(section(s, 'recognition')),
                          summary=strip_links(s.get('_intro', '')),
                          invariant=strip_links(section(s, 'invariant', 'core', 'recurrence')),
                          mistakes=strip_links(section(s, 'common mistakes', 'pitfalls'))))
    return cards + problems, titles


# ---------------------------------------------------------------- state

def load_state(path):
    if path.exists():
        data = json.loads(path.read_text())
        data.setdefault('cards', {})
        data.setdefault('log', {})
        return data
    return {'version': 1, 'cards': {}, 'log': {}}


def save_state(path, state):
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=path.parent, prefix='.state-')
    with os.fdopen(fd, 'w') as handle:
        json.dump(state, handle, indent=1, sort_keys=True)
        handle.write('\n')
    os.replace(tmp, path)


def pick_session(cards, state, today, new_limit, review_limit, pattern=None, seed=None):
    """Due reviews first (most overdue first, then shuffled), then new cards in teaching order."""
    rng = random.Random(seed if seed is not None else today.isoformat())
    known = state['cards']
    if pattern:
        cards = [c for c in cards if c.get('pattern') == pattern or pattern in c.get('patterns', [])]
    due = [c for c in cards if c['id'] in known and known[c['id']]['due'] <= today.isoformat()]
    due.sort(key=lambda c: known[c['id']]['due'])
    due = due[:review_limit]
    rng.shuffle(due)  # interleave patterns instead of reviewing one topic in a block

    introduced_patterns = {c[2:] for c in known if c.startswith('p:')}
    fresh_patterns = sorted((c for c in cards if c['kind'] == 'pattern' and c['id'] not in known),
                            key=lambda c: (-c['examples'], c['pattern']))
    fresh_problems = [c for c in cards if c['kind'] == 'problem' and c['id'] not in known]
    rng.shuffle(fresh_problems)
    new = []
    # Alternate: one new pattern, then up to two of its or earlier patterns' examples.
    while len(new) < new_limit and (fresh_patterns or fresh_problems):
        if fresh_patterns:
            card = fresh_patterns.pop(0)
            new.append(card)
            introduced_patterns.add(card['pattern'])
        ready = [c for c in fresh_problems if introduced_patterns & set(c['patterns']) or not c['patterns']]
        for c in ready[:2]:
            if len(new) >= new_limit:
                break
            new.append(c)
            fresh_problems.remove(c)
        if not fresh_patterns and not ready:
            break
    return due, new


# ---------------------------------------------------------------- rendering

def guess_link(card):
    """Kattis slugs are predictable; elsewhere, give a search phrase rather than a guessed URL."""
    stem = Path(card['path']).stem
    if card['platform'] == 'kattis' and stem.startswith('kattis-'):
        return 'https://open.kattis.com/problems/' + stem[len('kattis-'):]
    title = re.sub(r'^(cf|cses|kattis|at|atcoder|uva|usaco|USACO)\s+', '', card['title'])
    return f"(no link) search: {card['platform'] or 'problem'} \"{title}\""


def front(card):
    if card['kind'] == 'pattern':
        clues = card['clues'] or card['summary']
        return ('PATTERN  -  which technique fits these clues? State its invariant and one pitfall.\n\n'
                + clip(clues, 18))
    links = '\n'.join('  ' + u for u in card['urls'][:2]) or '  ' + guess_link(card)
    where = f" [{card['platform']}]" if card['platform'] else ''
    return (f"PROBLEM  -  {card['title']}{where}\n{links}\n\n"
            'What is the key idea, and which pattern does it use?')


def back(card, titles):
    if card['kind'] == 'pattern':
        parts = [f"== {card['title']}  ({card['pattern']}, {card['examples']} examples)", card['summary']]
        if card['invariant']:
            parts += ['', '-- Invariant', clip(card['invariant'], 16)]
        if card['mistakes']:
            parts += ['', '-- Common mistakes', clip(card['mistakes'], 8)]
        parts += ['', 'Note: ' + card['path']]
        return '\n'.join(parts)
    pats = ', '.join(f"{titles.get(p, p)} ({p})" for p in card['patterns']) or '(no pattern linked)'
    return '\n'.join([f"== Key idea: {card['evidence']}", f"Patterns: {pats}",
                      f"Category: {card['category']}", f"Code: {card['path']}"]
                     + [f"Note: notes/patterns/{p}.md" for p in card['patterns'][:2]])


def ask(prompt, read):
    print(prompt, end='', flush=True)
    line = read()
    if line == '':
        raise EOFError
    return line.strip().lower()


def run_session(cards, titles, state, state_path, today, args, read=sys.stdin.readline):
    due, new = pick_session(cards, state, today, args.new, args.max, args.pattern)
    queue = [(c, False) for c in due] + [(c, True) for c in new]
    if not queue:
        print('Nothing due. Come back tomorrow, or raise --new to learn more cards.')
        return 0
    print(f"{len(due)} review(s), {len(new)} new card(s). Keys: Enter reveal | 1 again 2 hard 3 good 4 easy | s skip | q quit\n")
    done = 0
    log = state['log'].setdefault(today.isoformat(), {'again': 0, 'hard': 0, 'good': 0, 'easy': 0})
    try:
        while queue:
            card, is_new = queue.pop(0)
            print('=' * 72)
            print(('NEW ' if is_new else '') + f'[{done + 1}/{done + len(queue) + 1}]')
            print(front(card))
            if ask('\n(Enter to reveal) ', read) == 'q':
                break
            print()
            print(back(card, titles))
            while True:
                answer = ask('\nGrade 1-4, s skip, q quit: ', read)
                if answer in GRADES or answer in {'s', 'q'}:
                    break
            if answer == 'q':
                break
            if answer == 's':
                continue
            grade = GRADES[answer]
            state['cards'][card['id']] = schedule(state['cards'].get(card['id']), grade, today)
            log[grade] += 1
            done += 1
            if grade == 'again':
                queue.append((card, False))  # see it again before the session ends
            save_state(state_path, state)
    except (EOFError, KeyboardInterrupt):
        print()
    save_state(state_path, state)
    print(f'\nSession saved: {done} answer(s). Remaining due today: '
          f"{sum(1 for c in cards if c['id'] in state['cards'] and state['cards'][c['id']]['due'] <= today.isoformat())}")
    return 0


def stats(cards, titles, state, today):
    known = state['cards']
    by_kind = {}
    for c in cards:
        k = by_kind.setdefault(c['kind'], [0, 0, 0])
        k[0] += 1
        if c['id'] in known:
            k[1] += 1
            k[2] += known[c['id']]['due'] <= today.isoformat()
    for kind, (total, seen, due) in sorted(by_kind.items()):
        print(f'{kind:8} cards: {total:4}   learned: {seen:4}   due today: {due:4}')
    upcoming = {}
    for c in cards:
        if c['id'] in known:
            d = known[c['id']]['due']
            if today.isoformat() < d <= (today + timedelta(days=7)).isoformat():
                upcoming[d] = upcoming.get(d, 0) + 1
    if upcoming:
        print('Next 7 days: ' + ', '.join(f'{d[5:]}: {n}' for d, n in sorted(upcoming.items())))
    recent = sorted(state['log'].items())[-7:]
    if recent:
        print('Recent answers: ' + ', '.join(
            f"{d[5:]} {sum(v.values())} ({v['again']} again)" for d, v in recent))


def weak(cards, titles, state, limit=12):
    """Patterns ranked by forgetting: lapses and low ease across the pattern and its examples."""
    known = state['cards']
    score = {}
    for c in cards:
        rec = known.get(c['id'])
        if not rec:
            continue
        for p in ([c['pattern']] if c['kind'] == 'pattern' else c['patterns']):
            s = score.setdefault(p, {'lapses': 0, 'ease': [], 'cards': 0})
            s['lapses'] += rec.get('lapses', 0)
            s['ease'].append(rec.get('ease', START_EASE))
            s['cards'] += 1
    rows = sorted(((v['lapses'], sum(v['ease']) / len(v['ease']), v['cards'], p) for p, v in score.items()),
                  key=lambda r: (-r[0], r[1]))
    rows = [r for r in rows if r[0] or r[1] < START_EASE][:limit]
    if not rows:
        print('No weak patterns yet: nothing has been forgotten so far.')
        return
    print(f"{'pattern':40} lapses  ease  cards")
    for lapses, ease, n, p in rows:
        print(f'{titles.get(p, p)[:40]:40} {lapses:6} {ease:5.2f} {n:6}')


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--new', type=int, default=10, help='new cards to introduce this session (default 10)')
    parser.add_argument('--max', type=int, default=50, help='maximum reviews this session (default 50)')
    parser.add_argument('--pattern', help='only cards for this pattern ID')
    parser.add_argument('--all-problems', action='store_true', help='also drill reviewed solutions with no pattern')
    parser.add_argument('--stats', action='store_true', help='show progress and upcoming load')
    parser.add_argument('--weak', action='store_true', help='rank patterns you forget most')
    parser.add_argument('--state', type=Path, default=DEFAULT_STATE)
    parser.add_argument('--today', type=date.fromisoformat, default=None, help=argparse.SUPPRESS)
    args = parser.parse_args(argv)
    today = args.today or date.fromisoformat(os.environ.get('CP_DRILL_TODAY') or date.today().isoformat())
    cards, titles = build_cards(include_unpatterned=args.all_problems)
    if args.pattern and args.pattern not in titles:
        parser.error('Unknown pattern ID: ' + args.pattern + ' (see catalog/patterns.json)')
    state = load_state(args.state)
    if args.stats:
        stats(cards, titles, state, today)
        return 0
    if args.weak:
        weak(cards, titles, state)
        return 0
    return run_session(cards, titles, state, args.state, today, args)


if __name__ == '__main__':
    sys.exit(main())
