# Prefix sums and difference arrays

Precompute cumulative aggregates so any range query is a constant number of lookups, and record range updates as two boundary marks that one prefix pass turns into final values.

## Recognition clues

- Many static queries "sum / count / xor of `a[l..r]`" with no updates between them.
- Many range updates ("add 1 to every cell in `[l, r]`") followed by reading every cell once.
- "Remove one element" or "split at position `i`" and the answer combines everything left of `i` with everything right of it.
- A 2D grid with rectangle-sum queries.
- A DP transition that sums a contiguous window of the previous row.

## Invariant and variants

With half-open prefixes `P[0] = 0`, `P[i] = P[i-1] + a[i-1]`, the sum of `a[l..r]` (0-indexed, inclusive) is `P[r+1] - P[l]`. Any invertible operation works (`+`, `xor`); counts of a predicate are prefix sums of an indicator.

Difference array for "add `v` to `[l, r]`": `D[l] += v; D[r+1] -= v`, then `a = prefix(D)`. Size `D` as `n + 2` so `r + 1` is always valid.

| Variant | Formula | Repo illustration |
| --- | --- | --- |
| 1D range sum / count | `P[r] - P[l-1]` (1-indexed) | `static_range_sum_queries.cpp`, `breed_counting.cpp`, `Winning_Record.cpp` |
| Prefix xor | `X[r] ^ X[l-1]` | `H_Range_Xor_Queries.cpp`, `AJ_Data_Structures_Fan.cpp` |
| Per-letter / per-bit prefix counts | one array per symbol or bit | `K_Counting_Test.cpp`, `AH_And_It_s_Non_Zero.cpp` |
| Difference array, then prefix of a predicate | coverage `>= k`, then counts of that | `Karen_and_Coffee.cpp`, `cf-wrath.cpp`, `haybale_stacking.cpp` |
| 2D prefix sums | `S[y2][x2] - S[y1-1][x2] - S[y2][x1-1] + S[y1-1][x1-1]` | `cses-forestqueries.cpp`, `J_Counting_Rectangles.cpp` |
| Sorted prefix + binary search | first prefix `>= x` by `lower_bound` | `E_Eating_Queries.cpp`, `B_Worms.cpp` |
| Window-sum DP transition | `dp[i][j] = sum dp[i-1][j-a_i .. j]` | `M_Candies.cpp`, `N_Slimes.cpp` |
| Periodic string | `(x / n) * freq[c] + pref[c][x % n]` | `K_Counting_Test.cpp` |

### Prefix/suffix "exclude one"

For a non-invertible associative operation (gcd, min, max), store `pre[i]` = op of `a[0..i-1]` and `suf[i]` = op of `a[i..n-1]`; the value with `a[i]` removed is `op(pre[i], suf[i+1])`. `C_Another_GCD.cpp` maximises this gcd; `G_Pivot.cpp` and `C_Prefix_Min_and_Suffix_Max.cpp` compare `a[i]` with prefix max and suffix min; `icpcworldfinals.cpp` scans every split point.

### Two-pass sweep

When each value is capped by its neighbour on both sides (`b[i] <= b[i±1] + 1`), relax left-to-right then right-to-left; after both passes every constraint holds. `D_Pawn_Line.cpp` uses this and pays `sum(a[i] - b[i])`.

Complexity: `O(n)` build and `O(1)` per query (`O(nm)` build in 2D); memory equal to the array.

## Common mistakes

- Writing `D[r+1]` into an array of size `n + 1`: `haybale_stacking.cpp` goes out of bounds when `r == n`.
- Mixing 0-indexed inclusive arrays with 1-indexed queries; `static-range-sum-queries.py` needs a special case for `l == 1` that a leading zero would remove.
- Overflow: `K_Counting_Test.cpp` accumulates `(x / n) * freq` into an `int`.
- Fixed-size arrays (`200005`) must cover the largest coordinate, not `n`.
- Using prefix differences for min/max/gcd, which are not invertible; use prefix/suffix arrays or [range-query structures](range-query-structures.md).

## Related patterns

Counting subarrays by matching prefix values belongs to [prefix sums with a frequency map](prefix-sum-frequency-map.md). Point updates between queries need [range-query structures](range-query-structures.md). Monotone prefix sums support [sorted lookup](sorted-lookup.md) and [binary search on the answer](binary-search-on-answer.md); interval sums also feed [interval DP](interval-dp.md) and sweep-based [interval scheduling](interval-scheduling-and-sweep.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Appleman and Toastman (cpp)](../../solutions/greedy/A_Appleman_and_Toastman.cpp) | greedy | reviewed |
| [A-B Knapsack (cpp)](../../solutions/greedy/A-B_Knapsack.cpp) | greedy | reviewed |
| [AH - And It's Non-Zero (cpp)](../../solutions/bit-manipulation/AH_And_It_s_Non_Zero.cpp) | bit-manipulation | reviewed |
| [AJ - Data Structures Fan (cpp)](../../solutions/prefix-sums/AJ_Data_Structures_Fan.cpp) | prefix-sums | reviewed |
| [Avalanche (cpp)](../../solutions/games/Avalanche.cpp) | games | reviewed |
| [B Fence (cpp)](../../solutions/prefix-sums/B_Fence.cpp) | prefix-sums | reviewed |
| [B Flip The Bits (cpp)](../../solutions/prefix-sums/B_Flip_The_Bits.cpp) | prefix-sums | reviewed |
| [B Kuriyama Mirai s Stones (cpp)](../../solutions/prefix-sums/B_Kuriyama_Mirai_s_Stones.cpp) | prefix-sums | reviewed |
| [B Short and Hard (cpp)](../../solutions/prefix-sums/B_Short_and_Hard.cpp) | prefix-sums | reviewed |
| [B. Collecting Game (cpp)](../../solutions/greedy/B_Collecting_Game.cpp) | greedy | reviewed |
| [B. Ilya and Queries (cpp)](../../solutions/prefix-sums/B_Ilya_and_Queries.cpp) | prefix-sums | reviewed |
| [B. Move to the End (cpp)](../../solutions/prefix-sums/B_Move_to_the_End.cpp) | prefix-sums | reviewed |
| [B. Store Statistics (cpp)](../../solutions/prefix-sums/B_Store_Statistics.cpp) | prefix-sums | reviewed |
| [B. Two Squares (cpp)](../../solutions/prefix-sums/B_Two_Squares.cpp) | prefix-sums | reviewed |
| [B. Worms (cpp)](../../solutions/prefix-sums/B_Worms.cpp) | prefix-sums | reviewed |
| [breed counting (cpp)](../../solutions/prefix-sums/breed_counting.cpp) | prefix-sums | reviewed |
| [C - Odd Queries (cpp)](../../solutions/prefix-sums/C_Odd_Queries.cpp) | prefix-sums | reviewed |
| [C Frosted Highway (cpp)](../../solutions/prefix-sums/C_Frosted_Highway.cpp) | prefix-sums | reviewed |
| [C. Another GCD (cpp)](../../solutions/math/number-theory/C_Another_GCD.cpp) | math/number-theory | reviewed |
| [C. Fady: Ya baraaaa el mat3am feeeen (cpp)](../../solutions/sorting-and-searching/C_Fady_Ya_baraaaa_el_mat_3_am_feeeen.cpp) | sorting-and-searching | reviewed |
| [C. Jury Marks (cpp)](../../solutions/prefix-sums/C_Jury_Marks.cpp) | prefix-sums | reviewed |
| [C. Prefix Min and Suffix Max (cpp)](../../solutions/prefix-sums/C_Prefix_Min_and_Suffix_Max.cpp) | prefix-sums | reviewed |
| [cf eugeny playlist (cpp)](../../solutions/binary-search/cf-eugeny-playlist.cpp) | binary-search | reviewed |
| [cf vladsumofdigits (cpp)](../../solutions/prefix-sums/cf-vladsumofdigits.cpp) | prefix-sums | reviewed |
| [cf wrath (cpp)](../../solutions/prefix-sums/cf-wrath.cpp) | prefix-sums | reviewed |
| [Closest Cities (cpp)](../../solutions/prefix-sums/Closest_Cities.cpp) | prefix-sums | reviewed |
| [counting sort (cpp)](../../solutions/sorting-and-searching/counting-sort.cpp) | sorting-and-searching | reviewed |
| [cses forestqueries (cpp)](../../solutions/prefix-sums/cses-forestqueries.cpp) | prefix-sums | reviewed |
| [D - Pawn Line (cpp)](../../solutions/greedy/D_Pawn_Line.cpp) | greedy | reviewed |
| [D - Swap and Range Sum (cpp)](../../solutions/prefix-sums/D_Swap_and_Range_Sum.cpp) | prefix-sums | reviewed |
| [D Home Garden (cpp)](../../solutions/data-structures/stacks-and-queues/D_Home_Garden.cpp) | data-structures/stacks-and-queues | reviewed |
| [D Snowball (cpp)](../../solutions/prefix-sums/D_Snowball.cpp) | prefix-sums | reviewed |
| [D. Find the Different Ones! (cpp)](../../solutions/prefix-sums/D_Find_the_Different_Ones.cpp) | prefix-sums | reviewed |
| [D. Soldier and Number Game (cpp)](../../solutions/math/number-theory/D_Soldier_and_Number_Game.cpp) | math/number-theory | reviewed |
| [E. Eating Queries (cpp)](../../solutions/prefix-sums/E_Eating_Queries.cpp) | prefix-sums | reviewed |
| [E. Scuza (cpp)](../../solutions/prefix-sums/E_Scuza.cpp) | prefix-sums | reviewed |
| [F. Money Trees (cpp)](../../solutions/two-pointers-and-sliding-window/F_Money_Trees.cpp) | two-pointers-and-sliding-window | reviewed |
| [G - DMOPC '14 Contest 2 P4 - Deforestation (cpp)](../../solutions/prefix-sums/G_DMOPC_14_Contest_2_P_4_Deforestation.cpp) | prefix-sums | reviewed |
| [G Pivot (cpp)](../../solutions/prefix-sums/G_Pivot.cpp) | prefix-sums | reviewed |
| [H - Hits Different (cpp)](../../solutions/dynamic-programming/general/H_Hits_Different.cpp) | dynamic-programming/general | reviewed |
| [H - Range Xor Queries (cpp)](../../solutions/prefix-sums/H_Range_Xor_Queries.cpp) | prefix-sums | reviewed |
| [H. Zaglol vs. the British Occupation (cpp)](../../solutions/binary-search/H_Zaglol_vs_the_British_Occupation.cpp) | binary-search | reviewed |
| [haybale stacking (cpp)](../../solutions/prefix-sums/haybale_stacking.cpp) | prefix-sums | reviewed |
| [hoof paper scissors (cpp)](../../solutions/prefix-sums/hoof_paper_scissors.cpp) | prefix-sums | reviewed |
| [I. Swap(Mohamed, !Mohamed) (cpp)](../../solutions/prefix-sums/I_Swap_Mohamed_Mohamed.cpp) | prefix-sums | reviewed |
| [icpcworldfinals (cpp)](../../solutions/prefix-sums/icpcworldfinals.cpp) | prefix-sums | reviewed |
| [J - Counting Rectangles (cpp)](../../solutions/prefix-sums/J_Counting_Rectangles.cpp) | prefix-sums | reviewed |
| [J. Zaghloul and the spies (cpp)](../../solutions/prefix-sums/J_Zaghloul_and_the_spies.cpp) | prefix-sums | reviewed |
| [K - Counting Test (cpp)](../../solutions/prefix-sums/K_Counting_Test.cpp) | prefix-sums | reviewed |
| [Karen and Coffee (cpp)](../../solutions/prefix-sums/Karen_and_Coffee.cpp) | prefix-sums | reviewed |
| [M - Candies (cpp)](../../solutions/dynamic-programming/knapsack/M_Candies.cpp) | dynamic-programming/knapsack | reviewed |
| [Maximum Average Segment (cpp)](../../solutions/binary-search/Maximum_Average_Segment.cpp) | binary-search | reviewed |
| [maximum sum (python)](../../solutions/prefix-sums/maximum_sum.py) | prefix-sums | reviewed |
| [N - Slimes (cpp)](../../solutions/dynamic-programming/intervals/N_Slimes.cpp) | dynamic-programming/intervals | reviewed |
| [Prefix Sum Addicts (cpp)](../../solutions/prefix-sums/Prefix_Sum_Addicts.cpp) | prefix-sums | reviewed |
| [static range sum queries (python)](../../solutions/prefix-sums/static-range-sum-queries.py) | prefix-sums | reviewed |
| [static range sum queries (cpp)](../../solutions/prefix-sums/static_range_sum_queries.cpp) | prefix-sums | reviewed |
| [trace of matrix (python)](../../solutions/prefix-sums/trace_of_matrix.py) | prefix-sums | reviewed |
| [TripTastic (cpp)](../../solutions/binary-search/TripTastic.cpp) | binary-search | reviewed |
| [USACO Air Cownditioning (cpp)](../../solutions/greedy/USACO_Air_Cownditioning.cpp) | greedy | reviewed |
| [USACO Air Cownditioning II (cpp)](../../solutions/brute-force-and-backtracking/USACO_Air_Cownditioning_II.cpp) | brute-force-and-backtracking | reviewed |
| [Winning Record (cpp)](../../solutions/prefix-sums/Winning_Record.cpp) | prefix-sums | reviewed |

<!-- examples:end -->
