# LIS and subsequence DP

Subsequence problems keep, for each prefix, the best subsequence ending in (or matching up to) some state. For the longest increasing subsequence, the "tails" array gives `O(n log n)`; for two sequences, a 2D table over prefixes gives LCS.

## Recognition clues

- "Longest (strictly) increasing / non-decreasing subsequence", "minimum deletions to make sorted", "fewest decreasing chains to cover" (Dilworth).
- Longest common subsequence of two strings, or reconstructing it.
- Subsequence that must follow a cyclic pattern (colour A then B then C) or a regular pattern.
- `n` up to `2 * 10^5` for LIS (needs `O(n log n)`), `n, m <= 3000` for LCS.

## Invariant and variants

Patience sorting: `tails[k]` is the smallest possible last value of an increasing subsequence of length `k + 1`. `tails` stays strictly increasing, so binary search finds where `x` goes:

```cpp
for (int x : a) {
    auto it = lower_bound(tails.begin(), tails.end(), x);   // strict LIS
    if (it == tails.end()) tails.push_back(x); else *it = x;
}
// length = tails.size(); use upper_bound for non-decreasing
```

LCS: `dp[i][j] = dp[i-1][j-1] + 1` if `s[i-1] == t[j-1]`, else `max(dp[i-1][j], dp[i][j-1])`; reconstruct by walking back from `dp[n][m]`.

| Variant | Repo idea |
| --- | --- |
| LIS length via tails | `cses-lis.cpp`, `C_Morco.cpp`, `E_Increasing_Subsequence.cpp` |
| LCS with reconstruction | `LCS.cpp` |
| Cyclic-state subsequence | `E_Traffic_Light.cpp`: best length ending in each of three colours, extend from the predecessor colour |

`O(n log n)` for LIS; `O(nm)` time and memory for LCS (one row suffices for the length only).

## Common mistakes

- `lower_bound` versus `upper_bound`: strict increase needs `lower_bound`, non-decreasing needs `upper_bound`.
- Printing `tails` as if it were a subsequence; it is not (`E_Increasing_Subsequence.cpp`). To recover one, store for each element its length and a parent index (or the index stored at each tail).
- Off-by-one between string indices and 1-based DP indices in LCS.
- Using the `O(n^2)` LIS DP when `n` is large.
- In state-machine subsequences, forgetting to carry unchanged states forward from `i` to `i + 1`.

## Related patterns

Position-indexed DP is [linear DP](linear-dp.md); the binary search step is [sorted lookup](sorted-lookup.md). DP over substrings rather than subsequences is [interval DP](interval-dp.md), and string comparisons may need [string matching](string-matching.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [C. Morco (cpp)](../../solutions/dynamic-programming/sequences/C_Morco.cpp) | dynamic-programming/sequences | reviewed |
| [cses lis (cpp)](../../solutions/dynamic-programming/sequences/cses-lis.cpp) | dynamic-programming/sequences | reviewed |
| [E - Increasing Subsequence (cpp)](../../solutions/dynamic-programming/sequences/E_Increasing_Subsequence.cpp) | dynamic-programming/sequences | reviewed |
| [E Traffic Light (cpp)](../../solutions/dynamic-programming/sequences/E_Traffic_Light.cpp) | dynamic-programming/sequences | reviewed |
| [LCS (cpp)](../../solutions/dynamic-programming/sequences/LCS.cpp) | dynamic-programming/sequences | reviewed |

<!-- examples:end -->
