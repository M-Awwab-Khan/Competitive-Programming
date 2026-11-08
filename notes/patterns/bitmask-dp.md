# Bitmask DP

When `n <= 20`, a DP state can be the set of items already used, stored as a bitmask, often with one extra coordinate such as the last item. Transitions add one unused item, so every state is processed after all its submasks if masks are iterated in increasing order.

## Recognition clues

- `n <= 20` (sometimes `<= 16` with an extra `n` factor) and the order or grouping of items matters.
- Visit every node once with pairwise costs (travelling salesman, Hamiltonian path).
- Pack all items into the fewest bins/rides with a capacity.
- Assignment of `n` tasks to `n` people, or counting arrangements subject to adjacency rules.

## Invariant and variants

`mask | (1 << j)` is numerically larger than `mask`, so a forward loop over `mask` finalises each state before it is extended.

| Variant | State and transition | Repo idea |
| --- | --- | --- |
| Hamiltonian path / TSP | `dp[mask][last] = min dp[mask ^ (1<<last)][prev] + cost[prev][last]` | `Sprinkler_Piping.cpp`: base `dp[1<<i][i] = start[i]` |
| Bin packing | `dp[mask] = lexicographic min (rides, lastLoad)`; add `i` to the current ride if it fits, else open a ride | `G_Elevator_Rides.cpp` |
| Assignment | `dp[mask]` with the next person `popcount(mask)` | (no repo example yet) |

```cpp
vector<vector<int>> dp(1 << n, vector<int>(n, INF));
for (int i = 0; i < n; ++i) dp[1 << i][i] = start[i];
for (int mask = 1; mask < (1 << n); ++mask)
    for (int i = 0; i < n; ++i) if (dp[mask][i] < INF)
        for (int j = 0; j < n; ++j) if (!(mask >> j & 1))
            dp[mask | 1 << j][j] = min(dp[mask | 1 << j][j], dp[mask][i] + cost[i][j]);
```

Hamiltonian DP is `O(2^n * n^2)` time and `O(2^n * n)` memory; the rides DP is `O(2^n * n)`. Iterating all submasks of all masks is `O(3^n)`.

## Common mistakes

- `INT_MAX + cost` overflow; skip unreachable states (as `Sprinkler_Piping.cpp` does) or use a smaller `INF`.
- Memory: `2^20 * 20` ints is about 80 MB; prefer `int` over `long long` or drop the extra dimension.
- In the rides variant the pair must be compared lexicographically (fewer rides first, then lighter last ride); `std::pair` comparison does that.
- Base case `dp[0] = {1, 0}` treats the first ride as already open; do not add one again at the end.
- Using `vector<vector<...>>` for `2^20` rows has heavy allocation overhead; a flat array is faster.

## Related patterns

Enumerating masks without overlapping subproblems is [subset enumeration](subset-enumeration.md); bit tricks are in [per-bit reasoning](per-bit-reasoning.md). Bitmask DP is a [knapsack](knapsack-dp.md)-style DP whose capacity is a set, and a DP over a DAG whose order is mask inclusion ([topological sort](topological-sort.md)). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [G - Elevator Rides (cpp)](../../solutions/dynamic-programming/bitmask/G_Elevator_Rides.cpp) | dynamic-programming/bitmask | reviewed |
| [Sprinkler Piping (cpp)](../../solutions/dynamic-programming/bitmask/Sprinkler_Piping.cpp) | dynamic-programming/bitmask | reviewed |

<!-- examples:end -->
