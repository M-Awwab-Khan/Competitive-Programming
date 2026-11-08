# Simulation with cycle detection

When a process with a finite (or small) state space is run for a huge number of steps, simulate until a state repeats, then jump: only the pre-period and `k mod period` steps need to be simulated.

## Recognition clues

- `k` or `n` up to `10^9`–`10^18` steps, but each step is a deterministic function of a small state.
- A recurrence taken modulo a small number (last digit of Fibonacci, `f_i = f_{i-1} - f_{i-2}`).
- A fixed shuffle or pair of reversals applied repeatedly; "after how many shuffles is the deck back".
- A pointer chase `i -> a[i]` (functional graph): "does it loop, leave, or finish".
- "Answer -1 if the game never ends".

## Invariant and variants

A deterministic map on a finite state set is eventually periodic: states `s_0, s_1, ...` satisfy `s_{i+p} = s_i` for all `i >= mu` (tail length `mu`, period `p`). Record the first time each state is seen; at the first repeat, `mu = first[s]` and `p = t - first[s]`. Then

```text
answer(k) = k < mu ? simulate(k) : state at mu + (k - mu) mod p
```

| Variant | State / period | Repo illustration |
| --- | --- | --- |
| Known arithmetic period | Pisano period 60 for mod 10; period 6 for `f_i = f_{i-1} - f_{i-2}`; period 15 for `i mod 3 == i mod 5` | `C_Fib_Last_Digit.cpp`, `cf-B_Jzzhu_and_Sequences.cpp`, `B_Subtractonacci.cpp`, `cf-fizzbuzzremixed.cpp` |
| Restarting program | time between two consecutive returns to `0` | `B_Robot_Program.cpp` (`1 + (k - first) / period`) |
| Apply permutation until identity | order of the composite permutation | `Problem_3_Swapity_Swap.cpp`, `kattis-shuffling.cpp` |
| Fixed point | iterate until the value stops changing | `kattis-digits.cpp` |
| Pointer chase with visited set | cycle, exits, or terminates | `kattis-basicprogramming1.cpp` (case 7) |
| Infinite game | repeated state means `-1` | `C_Soldier_and_Cards.py` (uses a step cap instead) |

### Functional-graph and permutation cycles

For a permutation `p`, each index lies on exactly one cycle; mark visited while walking so every cycle is traversed once, `O(n)` total. The order of `p` is the `lcm` of cycle lengths, and `p^k` maps `i` to the element `k mod len` steps ahead on its cycle. `A_Two_Friends.cpp` needs the shortest cycle in `i -> p_i` (length 2 means answer 2, else 3). `C_Disappearing_Permutation.cpp` repairs positions by walking `t -> p[t]` along a cycle. For a general functional graph, every component is a cycle with in-trees; jumps of `k` steps on a non-permutation use binary lifting.

Complexity: `O(mu + p)` steps times the cost of one step, plus memory for seen states (a map or array).

## Common mistakes

- Simulating until the *whole* permutation returns to identity: its order is `lcm` of cycle lengths and can be astronomically large; decompose into cycles instead. (Small inputs like `Problem_3_Swapity_Swap.cpp` survive.)
- Restarting a walk from every start without a global visited array: `A_Two_Friends.cpp` is `O(n^2)` in the worst case.
- Assuming the cycle starts at step 0: with a tail, use `(k - mu) mod p`, not `k mod p`.
- A heuristic step cap (`C_Soldier_and_Cards.py` stops after 1000 fights) instead of hashing visited states; it can be wrong if the true pre-period is longer.
- `list.insert(0, x)` / `pop(0)` as a queue in Python is `O(n)` per move; use `collections.deque`.
- Off-by-one between "number of steps" and "number of states" (for `n mod 60`, the base cases `n <= 1` must be returned directly).

## Related patterns

Periodic sequences under a modulus connect to [modular arithmetic](modular-arithmetic.md) and [closed-form arithmetic](closed-form-arithmetic.md). Cycles of `i -> a[i]` are a special case of [graph BFS/DFS](graph-bfs-dfs.md), and repeated jumps generalise to binary lifting as in [tree DFS](tree-dfs.md). Invariant-based shortcuts are in [parity and invariants](parity-and-invariants.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Two Friends (cpp)](../../solutions/graphs/traversal/A_Two_Friends.cpp) | graphs/traversal | reviewed |
| [B Robot Program (cpp)](../../solutions/simulation/B_Robot_Program.cpp) | simulation | reviewed |
| [B Subtractonacci (cpp)](../../solutions/math/arithmetic/B_Subtractonacci.cpp) | math/arithmetic | reviewed |
| [C Fib Last Digit (cpp)](../../solutions/math/arithmetic/C_Fib_Last_Digit.cpp) | math/arithmetic | reviewed |
| [C Soldier and Cards (python)](../../solutions/simulation/C_Soldier_and_Cards.py) | simulation | reviewed |
| [C Yet another XOR problem (cpp)](../../solutions/prefix-sums/C_Yet_another_XOR_problem.cpp) | prefix-sums | reviewed |
| [C. Disappearing Permutation (cpp)](../../solutions/simulation/C_Disappearing_Permutation.cpp) | simulation | reviewed |
| [cf B Jzzhu and Sequences (cpp)](../../solutions/math/combinatorics/cf-B_Jzzhu_and_Sequences.cpp) | math/combinatorics | reviewed |
| [cf fizzbuzzremixed (cpp)](../../solutions/math/arithmetic/cf-fizzbuzzremixed.cpp) | math/arithmetic | reviewed |
| [kattis basicprogramming1 (cpp)](../../solutions/simulation/kattis-basicprogramming1.cpp) | simulation | reviewed |
| [kattis digits (cpp)](../../solutions/simulation/kattis-digits.cpp) | simulation | reviewed |
| [kattis shuffling (cpp)](../../solutions/simulation/kattis-shuffling.cpp) | simulation | reviewed |
| [Problem 3. Swapity Swap (cpp)](../../solutions/simulation/Problem_3_Swapity_Swap.cpp) | simulation | reviewed |

<!-- examples:end -->
