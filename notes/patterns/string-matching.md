# String matching: naive scans, library find, and KMP

Find occurrences of a pattern `p` in a text `s`. Small inputs allow trying every offset; large ones need a linear-time matcher such as KMP or the Z-function.

## Recognition clues

- "Count/list all positions where `p` occurs", possibly overlapping.
- "Minimum number of changes so that `b` appears in `a`": per-offset Hamming distance.
- Queries "delete every name containing substring `q`".
- Wildcards like `?` matching any single character.
- `|s| * |p|` large (both near `1e5` or more): naive is too slow.

## Invariant and variants

KMP prefix function: `pi[i]` is the length of the longest proper border of `p[0..i]`. During the scan, `j` is the length of the longest prefix of `p` that is a suffix of the processed text.

```cpp
vector<int> pi(m);
for (int i = 1, j = 0; i < m; ++i) {
    while (j && p[i] != p[j]) j = pi[j - 1];
    if (p[i] == p[j]) ++j; pi[i] = j;
}
for (int i = 0, j = 0; i < n; ++i) {
    while (j && s[i] != p[j]) j = pi[j - 1];
    if (s[i] == p[j]) ++j;
    if (j == m) { occ.push_back(i - m + 1); j = pi[j - 1]; }
}
```

| Variant | Cost / note |
| --- | --- |
| Every offset, count mismatches | `O((n - m + 1) m)`; fine for small `n` |
| `string::find` per stored string | `O(total length)` per query in practice; delete after iterating, not during |
| KMP / Z on `p + '#' + s` | `O(n + m)` |
| `?` wildcard, small input | regex with `?` -> `.` or a direct per-offset check |

## Common mistakes

- Regex `finditer` returns non-overlapping matches, so overlapping occurrences are lost; also escape other metacharacters.
- KMP does not support wildcards: `?` breaks the border property, so a "wildcard-aware" prefix function is wrong in general.
- Erasing from a `set` while range-iterating over it.
- Loop bound `n - m + 1` when `m > n` (negative bound or unsigned wraparound).
- After a full match, forgetting `j = pi[j - 1]` and missing overlaps.

## Related patterns

[Palindromes](palindromes.md) is the other string family in the repo. Hashing-based alternatives use [modular arithmetic](modular-arithmetic.md); a precomputed index of occurrences is [sorted lookup](sorted-lookup.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [ashar (cpp)](../../solutions/strings/ashar.cpp) | strings | reviewed |
| [hate between strings (cpp)](../../solutions/strings/hate-between-strings.cpp) | strings | reviewed |
| [kmp (python)](../../solutions/strings/kmp.py) | strings | reviewed |

<!-- examples:end -->
