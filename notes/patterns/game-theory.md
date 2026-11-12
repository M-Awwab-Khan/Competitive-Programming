# Game theory: winning and losing states

For two-player, perfect-information games with optimal play, a state is winning iff some move leads to a losing state, and losing iff every move leads to a winning state. Compute this by DP for small state spaces, or find the pattern (often parity or a residue) for large ones.

## Recognition clues

- "Both players play optimally; who wins?" with a small state space (stones up to `1e5`, arrays up to `3000`).
- Taking elements from either end of an array and maximising your own score.
- Constraints too large for DP (`n` up to `1e9`, many test cases): compute small values by DP, look for a period, then prove it.
- The outcome seems to depend only on a distance, count, or residue (`A_Two_Frogs.cpp`: parity of `|a - b|`; `A_Game_of_chocolates.py`: `n mod 3`).
- A first move that "locks in" a win: the first player wins iff some single choice cannot be answered (`gameOfDivision.py`: a residue class of size one).

## Invariant and variants

```text
win[0..terminal] = false
for state in increasing order:
    win[state] = exists move m with not win[state - m]
```

| Variant | Recurrence | Repo illustration |
| --- | --- | --- |
| Subtraction game | `dp[i] = OR over x in A of !dp[i - x]` | `K_Stones.cpp` |
| Win/lose with a move to print | store states, print any move to a losing state | `dynamic-programming/general/test.py` |
| Score difference, take from either end | `d[l][r] = max(a[l] - d[l+1][r], a[r] - d[l][r-1])`; first player's score `(total + d[0][n-1]) / 2` | `cses-removalgame.cpp`, `L_Deque.cpp` |
| Two-value backward DP with a token | `dp[i] = (holder's best, other's best)` over a suffix | `Pie_Rules.cpp` |
| Parity or residue shortcut | answer from `|a - b| % 2`, `n % 3`, or odd letter count | `A_Two_Frogs.cpp`, `A_Game_of_chocolates.py`, `B_Little_Girl_and_Game.cpp` |

The score-difference form works because the game is zero-sum: the player to move maximises (my gain) minus (opponent's best difference on the rest). For sums of independent games, Sprague-Grundy numbers generalise win/lose: a position's Grundy value is the mex of its successors, and the XOR of component values is zero iff the position is losing.

Win/lose DP is `O(states * moves)`; interval score DP is `O(n^2)` time and memory.

## Common mistakes

- Simulating "a reasonable move" instead of proving optimality. `B_Little_Girl_and_Game.cpp` simulates removals with string copies (roughly cubic); the result is decided by the parity of the number of letters with odd count.
- Mixing up whose turn a DP value describes; define `dp` from the perspective of the player to move.
- Storing score differences in `int` when sums reach `n * 1e9`.
- Forgetting the terminal state: in a subtraction game, a position with no legal move is losing.
- Guessing a pattern from a few values without checking it against brute force for small `n`.

## Related patterns

Take-from-either-end games are [interval DP](interval-dp.md); one-dimensional state games are [linear DP](linear-dp.md). Shortcuts usually come from [parity and invariants](parity-and-invariants.md) or [modular arithmetic](modular-arithmetic.md), and Grundy XOR uses [XOR properties](xor-properties.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Game of chocolates (python)](../../solutions/games/A_Game_of_chocolates.py) | games | reviewed |
| [A Two Frogs (cpp)](../../solutions/games/A_Two_Frogs.cpp) | games | reviewed |
| [Avalanche (cpp)](../../solutions/games/Avalanche.cpp) | games | reviewed |
| [B Little Girl and Game (cpp)](../../solutions/games/B_Little_Girl_and_Game.cpp) | games | reviewed |
| [cses removalgame (cpp)](../../solutions/dynamic-programming/intervals/cses-removalgame.cpp) | dynamic-programming/intervals | reviewed |
| [K - Stones (cpp)](../../solutions/games/K_Stones.cpp) | games | reviewed |
| [L - Deque (cpp)](../../solutions/dynamic-programming/intervals/L_Deque.cpp) | dynamic-programming/intervals | reviewed |
| [Pie Rules (cpp)](../../solutions/dynamic-programming/general/Pie_Rules.cpp) | dynamic-programming/general | reviewed |
| [test (python)](../../solutions/dynamic-programming/general/test.py) | dynamic-programming/general | reviewed |

<!-- examples:end -->
