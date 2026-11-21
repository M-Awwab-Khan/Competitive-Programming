"""Readable comparison of a program's output with the expected answer.

Verdict rule (unchanged): whitespace-separated tokens must match exactly, or
numerically within EPS when an error margin is requested. Everything else here
only explains a failure: a one-line diagnosis, then a side-by-side table that
marks the differing lines and the differing tokens inside them.
"""
import difflib
import math
import re
import shutil
import sys

MAX_ROWS = 5
NUMBER = re.compile(r'[+-]?(\d+\.?\d*|\.\d+)([eE][+-]?\d+)?')


def parse_eps(value):
    """Return the EPS setting as a float, or None when unset."""
    if not value:
        return None
    eps = float(value)
    if not math.isfinite(eps) or eps <= 0:
        raise ValueError('EPS must be a finite positive number.')
    return eps


def _number(token):
    return float(token) if NUMBER.fullmatch(token) else None


def tokens_equal(expected, actual, eps=None):
    if expected == actual:
        return True
    if eps is None:
        return False
    x, y = _number(expected), _number(actual)
    return x is not None and y is not None and abs(x - y) <= eps * max(1.0, abs(x))


def _tokens(data):
    return data.decode(errors='replace').split()


def _rows(data):
    rows = [line.split() for line in data.decode(errors='replace').splitlines()]
    while rows and not rows[-1]:
        rows.pop()
    return rows


def matches(wanted, actual, eps=None):
    w, a = _tokens(wanted), _tokens(actual)
    return len(w) == len(a) and all(tokens_equal(x, y, eps) for x, y in zip(w, a))


def layout_differs(wanted, actual):
    """True when tokens match but the line breaks do not (informational)."""
    keep = lambda data: [row for row in _rows(data) if row]
    return keep(wanted) != keep(actual)


def _paint(code, text, color):
    return '\x1b[%sm%s\x1b[0m' % (code, text) if color else text


def _locate(rows, index):
    """1-based (line, token) of the index-th token across rows."""
    for number, row in enumerate(rows, 1):
        if index < len(row):
            return number, index + 1
        index -= len(row)
    return len(rows), 1


def _preview(tokens, limit=5):
    shown = ' '.join(tokens[:limit])
    return shown + (' ...' if len(tokens) > limit else '')


def diagnose(wanted, actual, eps=None):
    """Plain-language explanations, most useful first."""
    w, a = _tokens(wanted), _tokens(actual)
    if not a:
        return ['your output is empty (crash, timeout, or nothing printed?)']
    notes = []
    common = min(len(w), len(a))
    first = next((i for i in range(common) if not tokens_equal(w[i], a[i], eps)), None)
    if first is None:
        if len(a) < len(w):
            notes.append('output ends early: %d tokens, expected %d (missing: %s)'
                         % (len(a), len(w), _preview(w[len(a):])))
        else:
            notes.append('extra output: %d tokens, expected %d (extra: %s)'
                         % (len(a), len(w), _preview(a[len(w):])))
        return notes
    wl, wc = _locate(_rows(wanted), first)
    al, ac = _locate(_rows(actual), first)
    where = 'expected line %d, token %d' % (wl, wc)
    if (al, ac) != (wl, wc):
        where += ' (your line %d, token %d)' % (al, ac)
    notes.append('first difference at %s: expected %s, got %s' % (where, w[first], a[first]))
    if len(a) != len(w):
        notes.append('token counts differ: expected %d, got %d' % (len(w), len(a)))
    x, y = _number(w[first]), _number(a[first])
    if x is not None and y is not None:
        if x == int(x) and y == int(y) and abs(x - y) == 1:
            notes.append('off by one')
        elif eps is None and abs(x - y) <= 1e-3 * max(1.0, abs(x)):
            notes.append('the numbers differ by only %.3g; if the problem allows an error margin, '
                         'rerun with EPS=1e-6' % abs(x - y))
    if len(w) == len(a) and [t.lower() for t in w] == [t.lower() for t in a]:
        notes.append('same text, different letter case (e.g. YES vs Yes)')
    elif len(w) == len(a) and sorted(w) == sorted(a):
        notes.append('same tokens, different order')
    return notes


def _row_diff(mine, other, eps, expected_side):
    """Indexes of tokens in `mine` that disagree with `other` (None = missing line)."""
    if mine is None:
        return set()
    other = other or []
    bad = set()
    for i, token in enumerate(mine):
        if i >= len(other):
            bad.add(i)
        else:
            pair = (token, other[i]) if expected_side else (other[i], token)
            if not tokens_equal(pair[0], pair[1], eps):
                bad.add(i)
    return bad


def _cell(tokens, bad, width, color, code):
    """One table cell: (text with colors, visible length)."""
    if tokens is None:
        return _paint('2', '(no line)', color), len('(no line)')
    if not tokens:
        return _paint('2', '(blank line)', color), len('(blank line)')
    start = max(0, min(bad) - 1) if bad and len(' '.join(tokens)) > width else 0
    parts, used = [], 0

    def add(label, painted):
        nonlocal used
        used += len(label) + (1 if parts else 0)
        parts.append(painted)

    if start:
        add('...', _paint('2', '...', color))
    for i in range(start, len(tokens)):
        label = tokens[i] if color or i not in bad else '[' + tokens[i] + ']'
        reserve = 4 if i < len(tokens) - 1 else 0
        limit = max(3, width - used - (1 if parts else 0) - reserve)
        if len(label) > limit and len(parts) > (1 if start else 0):
            add('...', _paint('2', '...', color))
            break
        if len(label) > limit:
            label = label[:limit - 1] + '~'
        add(label, _paint(code if i in bad else '2', label, color))
    return ' '.join(parts), used


def table(wanted, actual, eps=None, color=False, width=100, verbose=False, ascii_only=False):
    w_rows, a_rows = _rows(wanted), _rows(actual)
    total = max(len(w_rows), len(a_rows))
    pick = lambda rows, i: rows[i] if i < len(rows) else None
    differing = [i for i in range(total)
                 if _row_diff(pick(w_rows, i), pick(a_rows, i), eps, True)
                 or _row_diff(pick(a_rows, i), pick(w_rows, i), eps, False)]
    if not differing:
        return []
    shown_diffs = differing if verbose else differing[:MAX_ROWS]
    wanted_rows = set(range(total)) if verbose else set(shown_diffs)
    if not verbose:
        for i in shown_diffs:
            wanted_rows.update(j for j in (i - 1, i + 1) if 0 <= j < total)
    natural = max([len(' '.join(rows[i])) + 2 for rows in (w_rows, a_rows)
                   for i in wanted_rows if i < len(rows)] + [10])
    column = min(natural, max(10, (width - 10) // 2))
    mark = '!' if ascii_only else '✗'
    gap = '   ...' if ascii_only else '   ⋮'
    lines = ['%s %s  %s' % (' ' * 5, _paint('1', 'expected'.ljust(column), color), _paint('1', 'yours', color))]
    previous = None
    for i in sorted(wanted_rows):
        if previous is not None and i != previous + 1:
            lines.append(_paint('2', gap, color))
        previous = i
        wr, ar = pick(w_rows, i), pick(a_rows, i)
        bad = i in differing
        left, left_len = _cell(wr, _row_diff(wr, ar, eps, True) if bad else set(), column, color, '1;32')
        right, _ = _cell(ar, _row_diff(ar, wr, eps, False) if bad else set(), column, color, '1;31')
        flag = _paint('1;31', mark, color) if bad else ' '
        lines.append('%s %s  %s%s  %s' % (flag, ('%d' % (i + 1)).rjust(3), left,
                                         ' ' * max(0, column - left_len), right))
    if len(differing) > len(shown_diffs):
        lines.append(_paint('2', '   ... and %d more differing lines (VERBOSE=1 shows all)'
                            % (len(differing) - len(shown_diffs)), color))
    return lines


def unified(wanted, actual, expected_name, actual_name):
    return ''.join(difflib.unified_diff(
        wanted.decode(errors='replace').splitlines(True),
        actual.decode(errors='replace').splitlines(True),
        fromfile=expected_name, tofile=actual_name))


def report(wanted, actual, expected_name, actual_name, eps=None, color=False,
           verbose=False, style='side-by-side'):
    """Verdict text for one sample: (ok, text)."""
    encoding = (getattr(sys.stdout, 'encoding', None) or '').lower()
    if matches(wanted, actual, eps):
        rule = ('tokens match within EPS=%g' % eps if eps is not None
                else 'whitespace-separated tokens match; no floating-point tolerance')
        text = _paint('1;32', 'PASS', color) + ' (' + rule + ')'
        if layout_differs(wanted, actual):
            text += '\n' + _paint('2', 'note: the tokens match but the line breaks differ', color)
        return True, text
    w_lines, a_lines = len(_rows(wanted)), len(_rows(actual))
    out = [_paint('1;31', 'FAIL', color) + '  expected %d line%s, got %d (%s vs %s)'
           % (w_lines, '' if w_lines == 1 else 's', a_lines, expected_name, actual_name)]
    out += ['  ' + note for note in diagnose(wanted, actual, eps)]
    out.append('')
    if style == 'unified':
        out.append(unified(wanted, actual, expected_name, actual_name).rstrip('\n'))
    else:
        width = shutil.get_terminal_size((100, 24)).columns
        out += table(wanted, actual, eps, color, width, verbose, not encoding.startswith('utf'))
    return False, '\n'.join(out)
