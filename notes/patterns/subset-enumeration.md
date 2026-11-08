# Subset and permutation enumeration

When `n` is about 20 or less, try every subset as a bitmask (`2^n`) or, when `n` is about 10 or less, every ordering with `next_permutation` (`n!`). Evaluate each candidate directly and keep the best or count the valid ones.

## Recognition clues

- `n <= 20` (subsets), `n <= 10` (orderings), or a tiny fixed size such as 3 logos, 5 people or 8 cows.
- "Choose some items / split into two groups / assign a sign to each item / colour each vertex with two colours".
- Inclusion–exclusion over a handful of sets (`n <= 20` divisors or conditions).
- Ordering constraints on a few named objects ("X must be beside Y"), or "lexicographically smallest valid order".

## Invariant and variants

Bit `i` of `mask` means item `i` is chosen (or on side 1, or has sign `+`):

```cpp
for (int mask = 0; mask < (1 << n); ++mask) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) if (mask >> i & 1) sum += a[i];
    // evaluate mask
}
for (int s = mask; s; s = (s - 1) & mask) { /* every nonempty submask of mask */ }
sort(p.begin(), p.end());
do { /* evaluate order p */ } while (next_permutation(p.begin(), p.end()));
```

| Variant | Repo idea |
| --- | --- |
| Two groups / partition | `apple_division.cpp`: mask = group 1, minimise `|sum1 - sum2|` |
| Sign assignment | `H_Petr_and_a_Combination_Lock.cpp`: bit = `+`/`-`, test sum divisible by 360 |
| Filtered subsets | `G_Preparing_Olympiad.cpp`: popcount `>= 2`, sum in `[l, r]`, `max - min >= x` |
| Inclusion–exclusion by parity | `E_Again_Divisors.cpp`: add or subtract multiples of `lcm(subset)` by popcount parity, stop once `lcm > r` |
| Subset then simulate | `USACO_Air_Cownditioning_II.cpp`: apply chosen ranges with a difference array, check, keep cheapest |
| Rotation masks | `D_Three_Logos.cpp`: 3-bit mask chooses each logo's orientation |
| Small candidate set | `Problem_1_Field_Reduction.cpp`: only the extreme 3 per side matter, enumerate subsets of those |
| Permutations | `B_Shower_Line.cpp`, `USACO_Livestock_Lineup.cpp`, `A_Three_Cards.cpp` |

Cost is `O(2^n * n)` (or `O(2^n)` with incremental sums via `dp[mask] = dp[mask ^ lowbit] + a[bit]`) and `O(n! * n)` for permutations. Over-limit sizes call for [meet in the middle](meet-in-the-middle.md) or [bitmask DP](bitmask-dp.md).

## Common mistakes

- `next_permutation` only visits all orders if the range starts sorted; sort first.
- Including the empty mask when the problem needs a nonempty subset (start at `mask = 1`).
- Overflow of a subset LCM or product; cap early or use `__int128` as `E_Again_Divisors.cpp` does.
- Comparing concatenated numeric strings lexicographically is only valid when lengths are equal (`A_Three_Cards.cpp`).
- Fixing an arbitrary order among symmetric choices: `D_Three_Logos.cpp` tries rotations but always places logos in the order A, B, C.
- `1 << n` with `n >= 31` overflows `int`.

## Related patterns

When each choice must be checked against partial state with pruning, use [backtracking](backtracking-recursion.md). Splitting `n` around 40 into two halves is [meet in the middle](meet-in-the-middle.md). Submask counting by popcount is [per-bit reasoning](per-bit-reasoning.md); parity-signed sums are [pair counting and inclusion–exclusion](pair-counting-inclusion-exclusion.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Three Cards (cpp)](../../solutions/sorting-and-searching/A_Three_Cards.cpp) | sorting-and-searching | reviewed |
| [apple division (cpp)](../../solutions/brute-force-and-backtracking/apple_division.cpp) | brute-force-and-backtracking | reviewed |
| [B - B (cpp)](../../solutions/brute-force-and-backtracking/B_B.cpp) | brute-force-and-backtracking | reviewed |
| [B Shower Line (cpp)](../../solutions/brute-force-and-backtracking/B_Shower_Line.cpp) | brute-force-and-backtracking | reviewed |
| [C - Bipartize (cpp)](../../solutions/brute-force-and-backtracking/C_Bipartize.cpp) | brute-force-and-backtracking | reviewed |
| [C Olympic Haircut (cpp)](../../solutions/brute-force-and-backtracking/C_Olympic_Haircut.cpp) | brute-force-and-backtracking | reviewed |
| [D. Three Logos (cpp)](../../solutions/brute-force-and-backtracking/D_Three_Logos.cpp) | brute-force-and-backtracking | reviewed |
| [E Again Divisors (cpp)](../../solutions/math/number-theory/E_Again_Divisors.cpp) | math/number-theory | reviewed |
| [G - Preparing Olympiad (cpp)](../../solutions/brute-force-and-backtracking/G_Preparing_Olympiad.cpp) | brute-force-and-backtracking | reviewed |
| [Grid Sums Backtracking (cpp)](../../solutions/brute-force-and-backtracking/Grid_Sums_Backtracking.cpp) | brute-force-and-backtracking | reviewed |
| [H - Maximum Subsequence (cpp)](../../solutions/meet-in-the-middle/H_Maximum_Subsequence.cpp) | meet-in-the-middle | reviewed |
| [H - Petr and a Combination Lock (cpp)](../../solutions/brute-force-and-backtracking/H_Petr_and_a_Combination_Lock.cpp) | brute-force-and-backtracking | reviewed |
| [K - Subset Sums (cpp)](../../solutions/meet-in-the-middle/K_Subset_Sums.cpp) | meet-in-the-middle | reviewed |
| [Problem 1. Field Reduction (cpp)](../../solutions/brute-force-and-backtracking/Problem_1_Field_Reduction.cpp) | brute-force-and-backtracking | reviewed |
| [USACO Air Cownditioning II (cpp)](../../solutions/brute-force-and-backtracking/USACO_Air_Cownditioning_II.cpp) | brute-force-and-backtracking | reviewed |
| [USACO Livestock Lineup (cpp)](../../solutions/brute-force-and-backtracking/USACO_Livestock_Lineup.cpp) | brute-force-and-backtracking | reviewed |

<!-- examples:end -->
