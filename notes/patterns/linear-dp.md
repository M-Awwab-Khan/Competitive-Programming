# Linear DP over positions

Index states by position (or amount) `i`, possibly with a small extra dimension, and compute `dp[i]` from a constant or bounded number of earlier states. The work is choosing a state that makes the transition depend only on earlier indices.

## Recognition clues

- "Minimum cost / number of ways / maximum value to reach position `n`" with steps of bounded length (stairs, frog jumps, dice, digits).
- Take-or-skip choices along a line with a spacing rule (no two adjacent, at least `k` apart).
- A small set of modes per position: activity of the day, assembly line, row of a 2-row grid, phase of a pattern `a*b*a*`.
- Constraints around `n <= 10^5`–`10^6` with `O(1)`–`O(k)` transitions.

## Invariant and variants

`dp[i]` is final once all states it depends on are final; iterate in that order.

| Shape | Recurrence | Repo idea |
| --- | --- | --- |
| Bounded jumps, min cost | `dp[i] = min_j dp[i-j] + |h[i]-h[i-j]|` | `Frog_1.cpp`, `E_Frog_1.cpp`, `Frog_2.cpp`, `Pegs_DP.cpp` |
| Count ordered ways | `dp[i] = sum_{j in steps} dp[i-j]` | `cses-dicecombinations.cpp`, `Number_of_Ways.cpp`, `C_Typical_Stairs.cpp`, `Coin_Change_2.cpp` |
| Take or skip | `dp[i] = max(dp[i-1], dp[i-k-1] + a[i])` | `J_Bernard.cpp`, `boredom.cpp` (over values, with `cnt[v] * v`) |
| Mode per position | `dp[i][m] = cost + best dp[i-1][m']` with a rule on `m'` | `C_Vacation.cpp`, `car_wash.cpp`, `softwarehouse.py`, `abdul_ahad_heights.py` |
| Phase automaton | `dp[i+1][p]` = extend phase `p` or move from `p-1` | `Nikita_and_string.cpp` (`a`, `b`, `a` phases) |
| Digit-driven steps | `dp[i] = 1 + min_{d in digits(i)} dp[i-d]` | `cses-removingdigits.cpp` |
| Probability | `dp[i][j] = dp[i-1][j] * (1-p) + dp[i-1][j-1] * p` | `Coins.cpp` |
| Run length | `dp[i] = a[i] >= a[i-1] ? dp[i-1] + 1 : 1` | `A_Kefa_and_First_Steps.cpp` |
| Lookback of length 2 | `dp[i+1] = max(dp[i] + f(i), dp[i-1] + g(i-1, i))` | `C_MAX_MEX_Cut.cpp` |
| Backward game DP | `dp[i] = (holder best, other best)` from `i+1` | `Pie_Rules.cpp` |

Time `O(n * transitions)`; rolling variables reduce memory to `O(window)`. A sliding-window minimum over `dp[i-k..i-1]` turns `O(nk)` into `O(n)` with a [monotonic deque](monotonic-deque.md); a window sum uses a running prefix.

## Common mistakes

- Missing the modulus inside the loop: `E_Tribonacci_numbers.cpp` reduces only at the end, so values overflow. Reduce every step (addition mod is safe).
- Wrong array size or read bound: `C_Typical_Stairs.cpp` allocates `k` entries but reads `n`.
- Base cases: `dp[0] = 1` for counting, `dp[0] = 0` for costs, and `INF` sentinels that overflow when added to.
- Iterating `dp[i-j]` with `i - j < 0` or reading uninitialised states.
- A redundant self-transition (`dp[i]` from `dp[i]`) is harmless for `min` but can double-count in counting DP.

## Related patterns

Item-by-item capacity DP is [knapsack DP](knapsack-dp.md); two-coordinate positions are [grid path DP](grid-path-dp.md); subsequence states are [LIS and sequence DP](lis-and-sequence-dp.md). Maximum subarray is [Kadane](kadane-max-subarray.md). DP along a DAG order is [topological sort](topological-sort.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A. Kefa and First Steps (cpp)](../../solutions/dynamic-programming/general/A_Kefa_and_First_Steps.cpp) | dynamic-programming/general | reviewed |
| [abdul ahad heights (python)](../../solutions/dynamic-programming/general/abdul_ahad_heights.py) | dynamic-programming/general | reviewed |
| [B - Flight Planner (cpp)](../../solutions/dynamic-programming/general/B_Flight_Planner.cpp) | dynamic-programming/general | reviewed |
| [boredom (cpp)](../../solutions/dynamic-programming/sequences/boredom.cpp) | dynamic-programming/sequences | reviewed |
| [C - Typical Stairs (cpp)](../../solutions/dynamic-programming/general/C_Typical_Stairs.cpp) | dynamic-programming/general | reviewed |
| [C - Vacation (cpp)](../../solutions/dynamic-programming/general/C_Vacation.cpp) | dynamic-programming/general | reviewed |
| [C. MAX-MEX Cut (cpp)](../../solutions/dynamic-programming/general/C_MAX_MEX_Cut.cpp) | dynamic-programming/general | reviewed |
| [car wash (cpp)](../../solutions/dynamic-programming/general/car_wash.cpp) | dynamic-programming/general | reviewed |
| [car wash (python)](../../solutions/dynamic-programming/general/car_wash.py) | dynamic-programming/general | reviewed |
| [Coin Change 2 (cpp)](../../solutions/dynamic-programming/sequences/Coin_Change_2.cpp) | dynamic-programming/sequences | reviewed |
| [Coins (cpp)](../../solutions/dynamic-programming/general/Coins.cpp) | dynamic-programming/general | reviewed |
| [cses dicecombinations (cpp)](../../solutions/dynamic-programming/general/cses-dicecombinations.cpp) | dynamic-programming/general | reviewed |
| [cses removingdigits (cpp)](../../solutions/dynamic-programming/general/cses-removingdigits.cpp) | dynamic-programming/general | reviewed |
| [E - Frog 1 (cpp)](../../solutions/dynamic-programming/general/E_Frog_1.cpp) | dynamic-programming/general | reviewed |
| [E Minimum Score (cpp)](../../solutions/dynamic-programming/general/E_Minimum_Score.cpp) | dynamic-programming/general | reviewed |
| [E. Tribonacci numbers (cpp)](../../solutions/dynamic-programming/general/E_Tribonacci_numbers.cpp) | dynamic-programming/general | reviewed |
| [Frog 1 (cpp)](../../solutions/dynamic-programming/general/Frog_1.cpp) | dynamic-programming/general | reviewed |
| [Frog 2 (cpp)](../../solutions/dynamic-programming/general/Frog_2.cpp) | dynamic-programming/general | reviewed |
| [J Bernard (cpp)](../../solutions/dynamic-programming/general/J_Bernard.cpp) | dynamic-programming/general | reviewed |
| [M Truckloads (cpp)](../../solutions/dynamic-programming/general/M_Truckloads.cpp) | dynamic-programming/general | reviewed |
| [Nikita and string (cpp)](../../solutions/dynamic-programming/sequences/Nikita_and_string.cpp) | dynamic-programming/sequences | reviewed |
| [Number of Ways (cpp)](../../solutions/dynamic-programming/general/Number_of_Ways.cpp) | dynamic-programming/general | reviewed |
| [Pegs DP (cpp)](../../solutions/dynamic-programming/sequences/Pegs_DP.cpp) | dynamic-programming/sequences | reviewed |
| [Pie Rules (cpp)](../../solutions/dynamic-programming/general/Pie_Rules.cpp) | dynamic-programming/general | reviewed |
| [softwarehouse (python)](../../solutions/dynamic-programming/general/softwarehouse.py) | dynamic-programming/general | reviewed |

<!-- examples:end -->
