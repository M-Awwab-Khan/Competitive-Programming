# Parity and operation invariants

When a problem allows an operation any number of times, find a quantity the operation cannot change (a sum, a parity, a residue, a gcd). Reachability then reduces to comparing that quantity, and the remaining question is usually whether everything else is reachable.

## Recognition clues

- "You may perform the operation any number of times; can you reach ...?" or "what is the minimum/maximum after any number of operations?"
- Operations that flip two signs, move one unit between elements, swap elements at distance 2, or remove a fixed-size block.
- Yes/no answers with large inputs and a tiny output: the check is probably one parity or residue comparison.
- Grids and boards: a chessboard colouring (`(i + j) % 2`) often decides adjacency or reachability.
- Two-player games whose outcome depends only on a distance or count, often through parity.

## Invariant and variants

Prove two directions: the invariant is necessary (no operation changes it), and it is sufficient (a construction reaches every state with the right invariant value).

| Operation in the repo | Invariant | Consequence |
| --- | --- | --- |
| Flip signs of an adjacent pair (`E_Negatives_and_Positives.cpp`) | parity of the negative count | sum of `|a|`, minus `2 * min|a|` if the count is odd |
| Move value between elements (`B_Increase_and_Decrease.cpp`, `A_Final_Verdict.cpp`) | total sum | all equal iff `sum % n == 0` (or `sum == n * x`) |
| Transfer between `i-1` and `i+1` (`A_Transfusion.cpp`) | sum on each index-parity class | each class must average to the same value |
| Remove "33" or subtract 33 (`A_Kevin_and_Combination_Lock.cpp`) | `n mod 33` | reachable iff `n % 33 == 0` |
| Pairwise "two decrease, one increases" (`B_Laura_and_Operations.cpp`) | parity of pairwise differences | type survives iff the other two counts have equal parity |
| Swap only same-parity values (`parity_sort.py`) | parity at each position | compare with the sorted array position by position |
| Add or subtract `k` (`C_Make_it_Equal.cpp`, `cf-B_Polo_the_Penguin_and_Matrix.cpp`) | residue class mod `k` | normalise `x mod k` (or `min(r, k - r)`) before comparing |
| Subtract earlier elements (`G_Difference_Operations.cpp`) | gcd | reachable iff `gcd(all) == a[0]` |

Typical parity facts: a sum is odd iff the number of odd terms is odd; `n(n+1)/2` must be even to split `1..n` into equal halves (`two-sets.cpp`); a bishop never changes square colour (`kattis-chess.cpp`); a polynomial's sign at `x` flips with the parity of roots above `x` (`The_Wave.cpp`).

After the invariant check, the construction is usually greedy and `O(n)`.

## Common mistakes

- Checking only necessity. Make sure a construction exists for every state with the matching invariant, or the answer is too permissive.
- Testing several candidate targets on an array that the first test already modified (`A_Transfusion.cpp` mutates `a` inside its check); work on a copy.
- Using `x % 2 == 1` for negative `x` in C++ (`-3 % 2 == -1`); test `x % 2 != 0` or `x & 1`.
- Forgetting the degenerate case that has no room for an operation (`n = 1`, weight 2 in `watermelon.py`).

## Related patterns

Residue invariants are [modular arithmetic](modular-arithmetic.md); gcd invariants are in [gcd and lcm](gcd-lcm.md). Bit-level invariants are [per-bit reasoning](per-bit-reasoning.md) and [XOR properties](xor-properties.md). Parity often decides [game theory](game-theory.md) outcomes and suggests [constructive small cases](constructive-small-cases.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A - Transfusion (cpp)](../../solutions/simulation/A_Transfusion.cpp) | simulation | reviewed |
| [A Domino (cpp)](../../solutions/math/arithmetic/A_Domino.cpp) | math/arithmetic | reviewed |
| [A DZY Loves Chessboard (cpp)](../../solutions/constructive/A_DZY_Loves_Chessboard.cpp) | constructive | reviewed |
| [A Kitahara Haruki s Gift (cpp)](../../solutions/greedy/A_Kitahara_Haruki_s_Gift.cpp) | greedy | reviewed |
| [A Sakurako s Exam (cpp)](../../solutions/math/arithmetic/A_Sakurako_s_Exam.cpp) | math/arithmetic | reviewed |
| [A The Play Never Ends (cpp)](../../solutions/math/arithmetic/A_The_Play_Never_Ends.cpp) | math/arithmetic | reviewed |
| [A To Zero (cpp)](../../solutions/math/arithmetic/A_To_Zero.cpp) | math/arithmetic | reviewed |
| [A Two Frogs (cpp)](../../solutions/games/A_Two_Frogs.cpp) | games | reviewed |
| [A. Kevin and Combination Lock (cpp)](../../solutions/math/number-theory/A_Kevin_and_Combination_Lock.cpp) | math/number-theory | reviewed |
| [A. Square sorted (python)](../../solutions/arrays-and-counting/A_Square_sorted.py) | arrays-and-counting | reviewed |
| [A. Sublime Sequence (cpp)](../../solutions/math/arithmetic/A_Sublime_Sequence.cpp) | math/arithmetic | reviewed |
| [A. zerorush (cpp)](../../solutions/arrays-and-counting/A_zerorush.cpp) | arrays-and-counting | reviewed |
| [AA - Robin Hood and the Major Oak (cpp)](../../solutions/math/arithmetic/AA_Robin_Hood_and_the_Major_Oak.cpp) | math/arithmetic | reviewed |
| [B Core Programmer 39 s Job (cpp)](../../solutions/math/arithmetic/B_Core_Programmer_39_s_Job.cpp) | math/arithmetic | reviewed |
| [B Equidistant String (cpp)](../../solutions/constructive/B_Equidistant_String.cpp) | constructive | reviewed |
| [B Generate Permutation (cpp)](../../solutions/constructive/B_Generate_Permutation.cpp) | constructive | reviewed |
| [B Increase and Decrease (cpp)](../../solutions/math/arithmetic/B_Increase_and_Decrease.cpp) | math/arithmetic | reviewed |
| [B Laura and Operations (cpp)](../../solutions/math/arithmetic/B_Laura_and_Operations.cpp) | math/arithmetic | reviewed |
| [B Root Sorted (cpp)](../../solutions/arrays-and-counting/B_Root_Sorted.cpp) | arrays-and-counting | reviewed |
| [B. An Operational Problem (cpp)](../../solutions/math/number-theory/B_An_Operational_Problem.cpp) | math/number-theory | reviewed |
| [B. Merge it! (cpp)](../../solutions/greedy/B_Merge_it.cpp) | greedy | reviewed |
| [C - Odd Queries (cpp)](../../solutions/prefix-sums/C_Odd_Queries.cpp) | prefix-sums | reviewed |
| [C Raspberries (cpp)](../../solutions/math/number-theory/C_Raspberries.cpp) | math/number-theory | reviewed |
| [C. Combination Lock (cpp)](../../solutions/constructive/C_Combination_Lock.cpp) | constructive | reviewed |
| [C. Make it Equal (cpp)](../../solutions/math/number-theory/C_Make_it_Equal.cpp) | math/number-theory | reviewed |
| [C. Pacer (cpp)](../../solutions/math/arithmetic/C_Pacer.cpp) | math/arithmetic | reviewed |
| [C. Penchick and BBQ Buns (cpp)](../../solutions/constructive/C_Penchick_and_BBQ_Buns.cpp) | constructive | reviewed |
| [C. Uninteresting Number (cpp)](../../solutions/math/arithmetic/C_Uninteresting_Number.cpp) | math/arithmetic | reviewed |
| [cf B Polo the Penguin and Matrix (cpp)](../../solutions/math/arithmetic/cf-B_Polo_the_Penguin_and_Matrix.cpp) | math/arithmetic | reviewed |
| [cf evenarray (cpp)](../../solutions/arrays-and-counting/cf-evenarray.cpp) | arrays-and-counting | reviewed |
| [coin piles (cpp)](../../solutions/math/arithmetic/coin_piles.cpp) | math/arithmetic | reviewed |
| [D String Game (cpp)](../../solutions/data-structures/stacks-and-queues/D_String_Game.cpp) | data-structures/stacks-and-queues | reviewed |
| [D Taxes (cpp)](../../solutions/math/number-theory/D_Taxes.cpp) | math/number-theory | reviewed |
| [D. Destruction of the Dandelion Fields (cpp)](../../solutions/greedy/D_Destruction_of_the_Dandelion_Fields.cpp) | greedy | reviewed |
| [E. Negatives and Positives (cpp)](../../solutions/greedy/E_Negatives_and_Positives.cpp) | greedy | reviewed |
| [Ehab The Exorcist (python)](../../solutions/bit-manipulation/Ehab_The_Exorcist.py) | bit-manipulation | reviewed |
| [erase tab submissions (cpp)](../../solutions/simulation/erase_tab_submissions.cpp) | simulation | reviewed |
| [firework festival (cpp)](../../solutions/math/arithmetic/firework-festival.cpp) | math/arithmetic | reviewed |
| [G Difference Operations (cpp)](../../solutions/math/number-theory/G_Difference_Operations.cpp) | math/number-theory | reviewed |
| [K - Superultra's Favorite Permutation (cpp)](../../solutions/constructive/K_Superultra_s_Favorite_Permutation.cpp) | constructive | reviewed |
| [kattis chess (cpp)](../../solutions/simulation/kattis-chess.cpp) | simulation | reviewed |
| [number spiral (cpp)](../../solutions/math/arithmetic/number_spiral.cpp) | math/arithmetic | reviewed |
| [oddities (python)](../../solutions/math/arithmetic/oddities.py) | math/arithmetic | reviewed |
| [parity sort (python)](../../solutions/sorting-and-searching/parity_sort.py) | sorting-and-searching | reviewed |
| [roots (python)](../../solutions/binary-search/roots.py) | binary-search | reviewed |
| [secret message (cpp)](../../solutions/strings/secret-message.cpp) | strings | reviewed |
| [The Wave (cpp)](../../solutions/binary-search/The_Wave.cpp) | binary-search | reviewed |
| [two sets (cpp)](../../solutions/constructive/two-sets.cpp) | constructive | reviewed |
| [USACO Even More Odd Photos (cpp)](../../solutions/greedy/USACO_Even_More_Odd_Photos.cpp) | greedy | reviewed |
| [USACO Photoshoot (cpp)](../../solutions/greedy/USACO_Photoshoot.cpp) | greedy | reviewed |
| [Vicious Labyrinth (cpp)](../../solutions/constructive/Vicious_Labyrinth.cpp) | constructive | reviewed |
| [watermelon (python)](../../solutions/math/arithmetic/watermelon.py) | math/arithmetic | reviewed |
| [x = int(input()) (python)](../../solutions/math/number-theory/x%20%3D%20int%28input%28%29%29.py) | math/number-theory | reviewed |

<!-- examples:end -->
