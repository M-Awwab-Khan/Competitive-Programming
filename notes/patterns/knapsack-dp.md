# Knapsack and coin-change DP

Process items one at a time over a capacity (sum, budget, residue) dimension. The loop direction decides whether an item may be reused, and the loop nesting decides whether ordered sequences or unordered combinations are counted.

## Recognition clues

- Items with weight and value, a budget, a target sum, or a set of coin denominations.
- "Is sum `s` reachable / how many ways / minimum number of items / maximum value within capacity `W`".
- Capacity (or total value) small enough to index an array, typically `<= 10^5`–`10^6`.
- Splitting a set into two parts with equal or closest sums.

## Invariant and variants

After processing items `0..i`, `dp[c]` describes the best (or count of) selections from those items with capacity `c`.

```cpp
for (item : items)                         // 0/1: descending
    for (int c = C; c >= w; --c) dp[c] = best(dp[c], dp[c - w] + v);
for (item : items)                         // unbounded: ascending
    for (int c = w; c <= C; ++c) dp[c] = best(dp[c], dp[c - w] + v);
```

| Variant | Key detail | Repo idea |
| --- | --- | --- |
| 0/1 max value | descending capacity | `Knapsack_1.cpp`, `cses-bookshop.cpp` |
| Huge `W`, small values | swap: `dp[v]` = min weight for value `v`; answer is max `v` with `dp[v] <= W` | `Knapsack_2.cpp` |
| Subset-sum reachability | boolean, descending | `cses-moneysums.cpp`, `A_Subset_sum_dp.cpp` |
| Count equal partitions | count subsets with sum `S/2`, divide by 2 via inverse of 2 | `cses-twosets.cpp` |
| Combinations (unordered) | coin outer, sum inner | `cses-coincombinations.cpp`, `Coin_Change_1.cpp`, `fours-and-fives.cpp` |
| Ordered sequences | sum outer, coin inner | `cses-coincombinations1.cpp` |
| Min coins / max pieces | unbounded, `-1` or `INF` for unreachable | `cses-minimizingcoins.cpp`, `A_Cut_Ribbon.cpp` |
| Overshoot allowed | clamp `dp[min(C, c + a)]`, or treat `a >= c` as finishing | `E_Crested_Ibis_vs_Monster.cpp` |
| Residues | `dp` over `sum mod m`, copy then add; pigeonhole says `n > m` is always YES | `B_Modulo_Sum.cpp` |
| Bounded count per item | `dp[i][j] = sum_{t=0..a_i} dp[i-1][j-t]` with a prefix sum | `M_Candies.cpp` |
| Reconstruction | DP over budget then greedy digit choice | `G_Match_Matching.cpp` |
| Two resources | 2D capacity, unbounded | `D_Clock_Strikes_Twelve.cpp` |

Time `O(n * C)`, memory `O(C)` for the 1D forms. Bitset shifts (`bs |= bs << w`) speed up boolean subset sum by about 64.

## Common mistakes

- Ascending loop for a 0/1 problem silently allows reuse; `L_The_Knapsack_problem.cpp` iterates ascending and so computes the unbounded version.
- Swapping loop nesting changes combinations into ordered sequences (and vice versa).
- Using `dp[c - w] + v` when `dp[c - w]` is the unreachable sentinel (`LLONG_MAX` overflows, `-1` looks valid); guard it.
- Modular subtraction in prefix-sum transitions needs `+ MOD` before `%`.
- In residue DP, updating `dp` in place lets one item be used twice; copy first.
- `int` products such as `n * (n + 1) / 2` can overflow before being stored in `long long`.

## Related patterns

Position-indexed recurrences are [linear DP](linear-dp.md); `n` up to 40 with huge sums needs [meet in the middle](meet-in-the-middle.md), and tiny `n` allows [subset enumeration](subset-enumeration.md). Pigeonhole on prefix residues is in [prefix sums with a frequency map](prefix-sum-frequency-map.md); counting modulo a prime uses [modular arithmetic](modular-arithmetic.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Cut Ribbon (cpp)](../../solutions/dynamic-programming/knapsack/A_Cut_Ribbon.cpp) | dynamic-programming/knapsack | reviewed |
| [A Subset sum dp (cpp)](../../solutions/dynamic-programming/knapsack/A_Subset_sum_dp.cpp) | dynamic-programming/knapsack | reviewed |
| [B Modulo Sum (cpp)](../../solutions/dynamic-programming/knapsack/B_Modulo_Sum.cpp) | dynamic-programming/knapsack | reviewed |
| [Coin Change 1 (cpp)](../../solutions/dynamic-programming/knapsack/Coin_Change_1.cpp) | dynamic-programming/knapsack | reviewed |
| [cses bookshop (cpp)](../../solutions/dynamic-programming/knapsack/cses-bookshop.cpp) | dynamic-programming/knapsack | reviewed |
| [cses coincombinations (cpp)](../../solutions/dynamic-programming/knapsack/cses-coincombinations.cpp) | dynamic-programming/knapsack | reviewed |
| [cses coincombinations1 (cpp)](../../solutions/dynamic-programming/knapsack/cses-coincombinations1.cpp) | dynamic-programming/knapsack | reviewed |
| [cses minimizingcoins (cpp)](../../solutions/dynamic-programming/knapsack/cses-minimizingcoins.cpp) | dynamic-programming/knapsack | reviewed |
| [cses moneysums (cpp)](../../solutions/dynamic-programming/knapsack/cses-moneysums.cpp) | dynamic-programming/knapsack | reviewed |
| [cses twosets (cpp)](../../solutions/dynamic-programming/knapsack/cses-twosets.cpp) | dynamic-programming/knapsack | reviewed |
| [D Clock Strikes Twelve (cpp)](../../solutions/dynamic-programming/knapsack/D_Clock_Strikes_Twelve.cpp) | dynamic-programming/knapsack | reviewed |
| [E - Crested Ibis vs Monster (cpp)](../../solutions/dynamic-programming/knapsack/E_Crested_Ibis_vs_Monster.cpp) | dynamic-programming/knapsack | reviewed |
| [fours and fives (cpp)](../../solutions/dynamic-programming/knapsack/fours-and-fives.cpp) | dynamic-programming/knapsack | reviewed |
| [G Match Matching (cpp)](../../solutions/dynamic-programming/knapsack/G_Match_Matching.cpp) | dynamic-programming/knapsack | reviewed |
| [H - Crested Ibis vs Monster (cpp)](../../solutions/dynamic-programming/knapsack/H_Crested_Ibis_vs_Monster.cpp) | dynamic-programming/knapsack | reviewed |
| [Knapsack 1 (cpp)](../../solutions/dynamic-programming/knapsack/Knapsack_1.cpp) | dynamic-programming/knapsack | reviewed |
| [Knapsack 2 (cpp)](../../solutions/dynamic-programming/knapsack/Knapsack_2.cpp) | dynamic-programming/knapsack | reviewed |
| [L. The Knapsack problem (cpp)](../../solutions/dynamic-programming/knapsack/L_The_Knapsack_problem.cpp) | dynamic-programming/knapsack | reviewed |
| [M - Candies (cpp)](../../solutions/dynamic-programming/knapsack/M_Candies.cpp) | dynamic-programming/knapsack | reviewed |

<!-- examples:end -->
