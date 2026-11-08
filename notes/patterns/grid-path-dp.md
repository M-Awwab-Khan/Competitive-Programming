# Grid path DP

When moves on a grid only go in monotone directions (right/down, or one row forward), cells form a DAG in row-major order, so `dp[i][j]` can be computed from already-finished neighbours.

## Recognition clues

- "Move only right or down" (or only forward one row and to an adjacent lane).
- Count paths modulo a prime, avoiding blocked cells or traps.
- Minimise or maximise a sum collected along the path, or a quantity derived from a product (trailing zeros).
- Each cell gives a jump length right or down; count ways to reach the corner.
- Grid up to about `1000 x 1000`; with general four-direction moves this pattern does not apply.

## Invariant and variants

```text
dp[0][0] = (start is free)
dp[i][j] = 0                              if blocked
dp[i][j] = dp[i-1][j] + dp[i][j-1]        (count)
dp[i][j] = cost[i][j] + min(dp[i-1][j], dp[i][j-1])   (optimise)
```

Iterate rows then columns (bottom-up) or memoise `f(i, j)` returning paths to the target; both are `O(nm)` time.

| Variant | Repo idea |
| --- | --- |
| Count with walls | `Grid_1.cpp`, `cses-gridpaths.cpp` (memoised from the target side, 0 on traps or out of bounds) |
| Blocked cells, `long long` count, start checked | `A_Walking_on_the_Safe_Side.cpp` |
| Lane DP, best neighbour below | `G_Subway_Surfers.cpp`: obstacles keep a negative sentinel |
| Jump length per cell | `L_JUMP.cpp` (big integers as strings), `L_JUMP.py` (native big ints) |
| Path minimising a factor count | `matrix-path.cpp`: memoised, stores the path string |

Memory can be one row (`dp[j] += dp[j-1]` row by row) for counting. Reconstruct a path by walking back from the target, choosing the predecessor that produced the value, instead of storing strings per cell.

## Common mistakes

- Seeding `dp[0][0] = 1` when the start itself is blocked.
- For minimum trailing zeros, the answer is `min(min twos, min fives)` computed by two separate DPs; tracking only fives (as `matrix-path.cpp` does) is incomplete, and a zero cell gives a candidate answer of 1 by routing through it.
- Sentinels for obstacles (`-1`, `INT_MIN`) leaking into `max`/`+` and becoming valid-looking values.
- Path counts grow exponentially; without a modulus you need big integers (`L_JUMP`).
- Storing a string per cell in memoisation multiplies memory by the path length.
- Recursion depth `n + m` is fine, but `n * m` deep recursion on a large grid can overflow the stack.

## Related patterns

One-dimensional version: [linear DP](linear-dp.md). Free movement in four directions needs [grid traversal](grid-traversal.md) or [shortest paths](shortest-paths.md). Half-paths from both corners joined at the anti-diagonal are [meet in the middle](meet-in-the-middle.md). Closed-form counts without obstacles are [binomial counting](binomial-counting.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Walking on the Safe Side (cpp)](../../solutions/dynamic-programming/general/A_Walking_on_the_Safe_Side.cpp) | dynamic-programming/general | reviewed |
| [cses gridpaths (cpp)](../../solutions/dynamic-programming/general/cses-gridpaths.cpp) | dynamic-programming/general | reviewed |
| [G Subway Surfers (cpp)](../../solutions/dynamic-programming/general/G_Subway_Surfers.cpp) | dynamic-programming/general | reviewed |
| [Grid 1 (cpp)](../../solutions/dynamic-programming/general/Grid_1.cpp) | dynamic-programming/general | reviewed |
| [L JUMP (cpp)](../../solutions/dynamic-programming/general/L_JUMP.cpp) | dynamic-programming/general | reviewed |
| [L JUMP (python)](../../solutions/dynamic-programming/general/L_JUMP.py) | dynamic-programming/general | reviewed |
| [matrix path (cpp)](../../solutions/dynamic-programming/general/matrix-path.cpp) | dynamic-programming/general | reviewed |

<!-- examples:end -->
