# Constructive answers from small cases

When the task is "output any array/permutation/string with property P, or say it is impossible", solve tiny `n` by hand or brute force, spot a pattern that extends, hardcode the exceptions, and prove the general pattern.

## Recognition clues

- "Print any valid permutation/array/string", "if there are several answers, print any", "or report that none exists".
- The checker is lenient but the property looks hard to optimise directly.
- Impossibility for a handful of small `n` (`n = 2, 3`), or for one parity of `n`.
- Properties about adjacent pairs, sums of prefixes, or residues: interleaving, alternating, or splitting by parity often works.
- Large `n` with an `O(n)` output size: the construction must be explicit, not searched.

## Invariant and variants

Workflow: brute force all candidates for `n <= 6` (offline), list which `n` are impossible, then find one family of answers that is easy to describe and prove.

| Construction idea | Repo illustration |
| --- | --- |
| All evens, then all odds (adjacent difference never 1) | `permutations.cpp` |
| Evens then odds joined by a valid bridge pair (`4 5`) so every adjacent sum is composite | `K_Superultra_s_Favorite_Permutation.cpp` |
| Identity `1..n` already works (multiples of `k` sum to a multiple of `k`) | `A_Array_Divisibility.cpp`, `A_Perfect_Root.cpp` |
| Rotate or shift the given permutation by one | `AQ_Minimize_Equal_Sum_Subarrays.cpp`, `A_Little_Elephant_and_Function.cpp` |
| Step-2 permutation `1, 3, 5, ... mod n` for odd `n` | `C_Combination_Lock.cpp` |
| Greedy append, swap the next two when a prefix sum hits a bad value | `B_Perfecto.cpp`, `cf-perfecto.py` |
| Symmetric offsets around a centre | `A_Find_K_Distinct_Points_with_Fixed_Center.cpp` |
| Alternate two values so every adjacent pair satisfies the rule | `B_Alternating_Series.cpp`, `A_Boys_and_Girls.cpp` |
| Small precomputed prefix, then a repeating block | `L_Everyone_Loves_Tres.cpp`, `almost_ternary_matrix.py` |
| Reflected recursion | `gray_code.cpp` |
| Constant offset answer (`a = b + n`) | `cf-goodoldtimes.cpp` |

Board-packing casework is the same idea: one row, two rows (blocks of four columns), and the general checkerboard case (`C_Max_Non_Attacking_Knights.cpp`, `uva-knights.cpp`).

Output size dictates the cost: `O(n)` per test case, with the impossibility test in `O(1)`.

## Common mistakes

- Assuming the pattern found for small even `n` also holds for odd `n` (or the reverse). `Alya_And_Permutation.cpp` uses the same fixed prefix regardless of parity.
- Missing an exception: `n = 1` is often valid while `n = 2, 3` are not (`permutations.cpp`).
- A greedy patch that runs past the end (`B_Perfecto.cpp` must check `i + 1 <= n` before swapping).
- Not verifying the construction with a brute-force checker on all small `n` before submitting.
- Printing a construction for an impossible case because the impossibility test was done after output started.

## Related patterns

Impossibility proofs usually come from [parity and invariants](parity-and-invariants.md). Casework formulas overlap with [closed-form arithmetic](closed-form-arithmetic.md). Constructions over residues use [modular arithmetic](modular-arithmetic.md), and some ask for orderings found by [sort-then-greedy](sort-then-greedy.md). Small cases can be explored with [backtracking](backtracking-recursion.md) or [subset enumeration](subset-enumeration.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Array Divisibility (cpp)](../../solutions/constructive/A_Array_Divisibility.cpp) | constructive | reviewed |
| [A Boys and Girls (cpp)](../../solutions/constructive/A_Boys_and_Girls.cpp) | constructive | reviewed |
| [A Diverse Game (cpp)](../../solutions/constructive/A_Diverse_Game.cpp) | constructive | reviewed |
| [A Farmer John s Challenge (cpp)](../../solutions/constructive/A_Farmer_John_s_Challenge.cpp) | constructive | reviewed |
| [A Find K Distinct Points with Fixed Center (cpp)](../../solutions/constructive/A_Find_K_Distinct_Points_with_Fixed_Center.cpp) | constructive | reviewed |
| [A Little Elephant and Function (cpp)](../../solutions/constructive/A_Little_Elephant_and_Function.cpp) | constructive | reviewed |
| [A Shohag Loves Mod (cpp)](../../solutions/constructive/A_Shohag_Loves_Mod.cpp) | constructive | reviewed |
| [A Submission Bait II (cpp)](../../solutions/constructive/A_Submission_Bait_II.cpp) | constructive | reviewed |
| [A. Increasing and Decreasing (cpp)](../../solutions/constructive/A_Increasing_and_Decreasing.cpp) | constructive | reviewed |
| [A. Perfect Root (cpp)](../../solutions/constructive/A_Perfect_Root.cpp) | constructive | reviewed |
| [almost ternary matrix (python)](../../solutions/constructive/almost_ternary_matrix.py) | constructive | reviewed |
| [Alya And Permutation (cpp)](../../solutions/constructive/Alya_And_Permutation.cpp) | constructive | reviewed |
| [AQ - Minimize Equal Sum Subarrays (cpp)](../../solutions/constructive/AQ_Minimize_Equal_Sum_Subarrays.cpp) | constructive | reviewed |
| [B Generate Permutation (cpp)](../../solutions/constructive/B_Generate_Permutation.cpp) | constructive | reviewed |
| [B Minimise Oneness (cpp)](../../solutions/constructive/B_Minimise_Oneness.cpp) | constructive | reviewed |
| [B Perfecto (cpp)](../../solutions/constructive/B_Perfecto.cpp) | constructive | reviewed |
| [B Weird Function (cpp)](../../solutions/constructive/B_Weird_Function.cpp) | constructive | reviewed |
| [B. Alternating Series (cpp)](../../solutions/constructive/B_Alternating_Series.cpp) | constructive | reviewed |
| [B. Sequence Game (cpp)](../../solutions/constructive/B_Sequence_Game.cpp) | constructive | reviewed |
| [C Differential Sorting (cpp)](../../solutions/constructive/C_Differential_Sorting.cpp) | constructive | reviewed |
| [C Make Them Equal (cpp)](../../solutions/greedy/C_Make_Them_Equal.cpp) | greedy | reviewed |
| [C Max Non Attacking Knights (cpp)](../../solutions/math/arithmetic/C_Max_Non_Attacking_Knights.cpp) | math/arithmetic | reviewed |
| [C. Combination Lock (cpp)](../../solutions/constructive/C_Combination_Lock.cpp) | constructive | reviewed |
| [C. Gormint Skool (cpp)](../../solutions/constructive/C_Gormint_Skool.cpp) | constructive | reviewed |
| [C. Penchick and BBQ Buns (cpp)](../../solutions/constructive/C_Penchick_and_BBQ_Buns.cpp) | constructive | reviewed |
| [cf goodoldtimes (cpp)](../../solutions/constructive/cf-goodoldtimes.cpp) | constructive | reviewed |
| [cf perfecto (python)](../../solutions/constructive/cf-perfecto.py) | constructive | reviewed |
| [D Districts Connection (cpp)](../../solutions/constructive/D_Districts_Connection.cpp) | constructive | reviewed |
| [D Sum Neq (cpp)](../../solutions/constructive/D_Sum_Neq.cpp) | constructive | reviewed |
| [D1. Sage's Birthday (easy version) (cpp)](../../solutions/constructive/D_1_Sage_s_Birthday_easy_version.cpp) | constructive | reviewed |
| [gray code (cpp)](../../solutions/constructive/gray_code.cpp) | constructive | reviewed |
| [K - Superultra's Favorite Permutation (cpp)](../../solutions/constructive/K_Superultra_s_Favorite_Permutation.cpp) | constructive | reviewed |
| [L - Everyone Loves Tres (cpp)](../../solutions/constructive/L_Everyone_Loves_Tres.cpp) | constructive | reviewed |
| [permutations (cpp)](../../solutions/constructive/permutations.cpp) | constructive | reviewed |
| [uva knights (cpp)](../../solutions/math/arithmetic/uva-knights.cpp) | math/arithmetic | reviewed |
| [Vicious Labyrinth (cpp)](../../solutions/constructive/Vicious_Labyrinth.cpp) | constructive | reviewed |
| [W - Perpendicular Segments (cpp)](../../solutions/constructive/W_Perpendicular_Segments.cpp) | constructive | reviewed |

<!-- examples:end -->
