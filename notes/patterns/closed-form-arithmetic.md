# Closed-form arithmetic and casework

Replace a simulation or search with a direct formula: a series sum, a ceiling or floor division, a bottleneck `min`, or a short case split on the input's shape. The work is in finding the formula and proving the boundary cases.

## Recognition clues

- Values up to `1e9`–`1e18` with `t` up to `1e4` test cases: anything slower than `O(1)` or `O(log)` per case is suspicious.
- "Minimum number of steps/rounds/trips" where every step removes a fixed amount: usually `ceil(total / perStep)`.
- Repeated or periodic structure ("the string repeats infinitely", "every 15 numbers"): count full blocks with `/`, finish the remainder by brute force.
- Several resources consumed together: the answer is the `min` over resources of `available / needed`.
- The answer obviously depends on whether a dimension is 1, 2, or large (knights on a board, grid colouring): casework.
- An expression like `1 + 2 + ... + k` or `k(k+1)/2` appears when the process is written out.

## Invariant and variants

Write the quantity after `k` steps as a function of `k`, then invert it, using integer arithmetic.

| Need | Integer formula (`a >= 0`, `b > 0`) |
| --- | --- |
| `ceil(a / b)` | `(a + b - 1) / b` |
| Multiples of `x` in `[a, b]` | `b / x - (a - 1) / x` |
| Steps to make `a` divisible by `b` | `(b - a % b) % b` |
| Perfect squares in `[l, r]` | `isqrt(r) - isqrt(l - 1)` |
| `k`-th positive integer not divisible by `n` | `k + (k - 1) / (n - 1)` (`cf-kthnondivisible.cpp`) |
| Arithmetic series `a..b` | `(b - a + 1) * (a + b) / 2` |
| Trailing zeros of `n!` | `n/5 + n/25 + ...` (Legendre) |
| Sum of squared distances to one point | minimised at the mean; test `floor` and `ceil` of it |

Periodic counting (`D_Mix_Plate.cpp`, `K_Counting_Test.cpp`, `cf-fizzbuzzremixed.cpp`):

```text
count(x) = (x / period) * perPeriod + bruteForce(x % period)
answer   = count(r) - count(l - 1)
```

When the inverse is not obvious, but the forward function `f(k)` is monotone, binary search `k` instead of solving a quadratic (`F_Brightness_Begins.cpp`, `AB_Klee_s_SUPER_DUPER_LARGE_Array.cpp`). An exact integer square root is `s = sqrtl(x)` followed by `while (s*s > x) s--; while ((s+1)*(s+1) <= x) s++;`.

Telescoping is a frequent shortcut: the sum of adjacent differences of a sorted array is `max - min` (`A_Sasha_and_the_Beautiful_Array.cpp`); merging the two smallest into `sum - 1` repeatedly ends at `total - (n - 1)` (`The_Third_Side.cpp`).

Complexity is `O(1)` or `O(log V)` per query, plus `O(n)` to read input.

## Common mistakes

- Floating-point `ceil`, `sqrt`, or `pow` on large integers. Several sources in this repo (`T_Savings.cpp`, `etruscan_warriors.cpp`, `A_To_Zero.cpp`, `troc-runningforpresident.cpp`, `G_Stamina.cpp`) compute integer answers through `double`; prefer integer ceiling division and a corrected integer square root.
- Products such as `n * max` or `(x / n) * freq` evaluated in `int` before widening (`B_Prefix_Max.cpp`, `K_Counting_Test.cpp`).
- Using `b / x - a / x` for multiples in `[a, b]` without adding the case where `a` itself is a multiple.
- Missing a small case (`n = 1`, one row, `k > n`) that the general formula does not cover; test the smallest inputs by hand.
- Writing `(a + b - 1) / b` for a negative `a`; C++ division truncates toward zero.

## Related patterns

Formulas usually come from an [invariant](parity-and-invariants.md) or from [modular arithmetic](modular-arithmetic.md). When the formula is only monotone, use [binary search on the answer](binary-search-on-answer.md). Counting with overlaps uses [inclusion-exclusion](pair-counting-inclusion-exclusion.md); sums over all pairs or subarrays use the [contribution technique](contribution-technique.md). Small-case casework is shared with [constructive small cases](constructive-small-cases.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A - Between a and b ... (cpp)](../../solutions/math/arithmetic/A_Between_a_and_b.cpp) | math/arithmetic | reviewed |
| [A - Keep the Apples (cpp)](../../solutions/math/arithmetic/A_Keep_the_Apples.cpp) | math/arithmetic | reviewed |
| [A - Scary Fee (cpp)](../../solutions/math/arithmetic/A_Scary_Fee.cpp) | math/arithmetic | reviewed |
| [A Adjacent Digit Sums (cpp)](../../solutions/math/arithmetic/A_Adjacent_Digit_Sums.cpp) | math/arithmetic | reviewed |
| [A AND Pairs (cpp)](../../solutions/math/arithmetic/A_AND_Pairs.cpp) | math/arithmetic | reviewed |
| [A Cups of Cocoa (cpp)](../../solutions/greedy/A_Cups_of_Cocoa.cpp) | greedy | reviewed |
| [A Dima and Friends (cpp)](../../solutions/math/arithmetic/A_Dima_and_Friends.cpp) | math/arithmetic | reviewed |
| [A Distanced Coloring (cpp)](../../solutions/math/arithmetic/A_Distanced_Coloring.cpp) | math/arithmetic | reviewed |
| [A Divisibility Problem (cpp)](../../solutions/math/arithmetic/A_Divisibility_Problem.cpp) | math/arithmetic | reviewed |
| [A Draw a Square (cpp)](../../solutions/geometry/A_Draw_a_Square.cpp) | geometry | reviewed |
| [A Even Odds (cpp)](../../solutions/math/arithmetic/A_Even_Odds.cpp) | math/arithmetic | reviewed |
| [A Final Verdict (cpp)](../../solutions/math/arithmetic/A_Final_Verdict.cpp) | math/arithmetic | reviewed |
| [A Guest From the Past (cpp)](../../solutions/greedy/A_Guest_From_the_Past.cpp) | greedy | reviewed |
| [A MEX Table (cpp)](../../solutions/math/arithmetic/A_MEX_Table.cpp) | math/arithmetic | reviewed |
| [A Opening Ceremony (cpp)](../../solutions/geometry/A_Opening_Ceremony.cpp) | geometry | reviewed |
| [A Race (cpp)](../../solutions/math/arithmetic/A_Race.cpp) | math/arithmetic | reviewed |
| [A Sasha and the Beautiful Array (cpp)](../../solutions/math/arithmetic/A_Sasha_and_the_Beautiful_Array.cpp) | math/arithmetic | reviewed |
| [A Shape Perimeter (cpp)](../../solutions/geometry/A_Shape_Perimeter.cpp) | geometry | reviewed |
| [A Soldier and Bananas (cpp)](../../solutions/math/arithmetic/A_Soldier_and_Bananas.cpp) | math/arithmetic | reviewed |
| [A The number of positions (python)](../../solutions/math/arithmetic/A_The_number_of_positions.py) | math/arithmetic | reviewed |
| [A To Zero (cpp)](../../solutions/math/arithmetic/A_To_Zero.cpp) | math/arithmetic | reviewed |
| [A Two Bags of Potatoes (cpp)](../../solutions/math/arithmetic/A_Two_Bags_of_Potatoes.cpp) | math/arithmetic | reviewed |
| [A Vasya and the Bus (cpp)](../../solutions/math/arithmetic/A_Vasya_and_the_Bus.cpp) | math/arithmetic | reviewed |
| [A Zhan s Blender (cpp)](../../solutions/math/arithmetic/A_Zhan_s_Blender.cpp) | math/arithmetic | reviewed |
| [A. K-divisible Sum (cpp)](../../solutions/math/arithmetic/A_K_divisible_Sum.cpp) | math/arithmetic | reviewed |
| [A. Letter Home (cpp)](../../solutions/math/arithmetic/A_Letter_Home.cpp) | math/arithmetic | reviewed |
| [A. Lever (cpp)](../../solutions/arrays-and-counting/A_Lever.cpp) | arrays-and-counting | reviewed |
| [A. Math Problem (python)](../../solutions/math/arithmetic/A_Math_Problem.py) | math/arithmetic | reviewed |
| [A. Santa Claus and Candies (cpp)](../../solutions/constructive/A_Santa_Claus_and_Candies.cpp) | constructive | reviewed |
| [A. Soft Drinking (cpp)](../../solutions/math/arithmetic/A_Soft_Drinking.cpp) | math/arithmetic | reviewed |
| [AA - Robin Hood and the Major Oak (cpp)](../../solutions/math/arithmetic/AA_Robin_Hood_and_the_Major_Oak.cpp) | math/arithmetic | reviewed |
| [AB - Klee's SUPER DUPER LARGE Array!!! (cpp)](../../solutions/binary-search/AB_Klee_s_SUPER_DUPER_LARGE_Array.cpp) | binary-search | reviewed |
| [atcoder ratinggoal (cpp)](../../solutions/math/arithmetic/atcoder-ratinggoal.cpp) | math/arithmetic | reviewed |
| [B Amr and Pins (cpp)](../../solutions/geometry/B_Amr_and_Pins.cpp) | geometry | reviewed |
| [B Cubes Sum (python)](../../solutions/math/arithmetic/B_Cubes_Sum.py) | math/arithmetic | reviewed |
| [B Divergent Series (cpp)](../../solutions/math/arithmetic/B_Divergent_Series.cpp) | math/arithmetic | reviewed |
| [B Having Been a Treasurer in the Past I Help Goblins Deceive (cpp)](../../solutions/math/combinatorics/B_Having_Been_a_Treasurer_in_the_Past_I_Help_Goblins_Deceive.cpp) | math/combinatorics | reviewed |
| [B Random Teams (cpp)](../../solutions/math/combinatorics/B_Random_Teams.cpp) | math/combinatorics | reviewed |
| [B Sasha and the Drawing (cpp)](../../solutions/constructive/B_Sasha_and_the_Drawing.cpp) | constructive | reviewed |
| [B Simple Game (cpp)](../../solutions/games/B_Simple_Game.cpp) | games | reviewed |
| [B Supply Chain (cpp)](../../solutions/math/arithmetic/B_Supply_Chain.cpp) | math/arithmetic | reviewed |
| [B Tab Closing (cpp)](../../solutions/math/arithmetic/B_Tab_Closing.cpp) | math/arithmetic | reviewed |
| [B Valuable Resources (cpp)](../../solutions/geometry/B_Valuable_Resources.cpp) | geometry | reviewed |
| [B. Buying Lemonade (cpp)](../../solutions/greedy/B_Buying_Lemonade.cpp) | greedy | reviewed |
| [B. Fancy Coins (cpp)](../../solutions/greedy/B_Fancy_Coins.cpp) | greedy | reviewed |
| [B. Getting Points (cpp)](../../solutions/binary-search/B_Getting_Points.cpp) | binary-search | reviewed |
| [B. Lasers (cpp)](../../solutions/math/arithmetic/B_Lasers.cpp) | math/arithmetic | reviewed |
| [B. Multiply by 2, divide by 6 (cpp)](../../solutions/math/number-theory/B_Multiply_by_2_divide_by_6.cpp) | math/number-theory | reviewed |
| [B. Paint a Strip (cpp)](../../solutions/math/arithmetic/B_Paint_a_Strip.cpp) | math/arithmetic | reviewed |
| [B. Points on Plane (cpp)](../../solutions/binary-search/B_Points_on_Plane.cpp) | binary-search | reviewed |
| [B. Prefix Max (cpp)](../../solutions/greedy/B_Prefix_Max.cpp) | greedy | reviewed |
| [B. Two Tables (cpp)](../../solutions/geometry/B_Two_Tables.cpp) | geometry | reviewed |
| [beautiful matrix (python)](../../solutions/math/arithmetic/beautiful_matrix.py) | math/arithmetic | reviewed |
| [C - Lock All Doors (python)](../../solutions/simulation/C_Lock_All_Doors.py) | simulation | reviewed |
| [C A and B and Team Training (cpp)](../../solutions/math/arithmetic/C_A_and_B_and_Team_Training.cpp) | math/arithmetic | reviewed |
| [C Be Together (cpp)](../../solutions/math/arithmetic/C_Be_Together.cpp) | math/arithmetic | reviewed |
| [C Dolce Vita (cpp)](../../solutions/sorting-and-searching/C_Dolce_Vita.cpp) | sorting-and-searching | reviewed |
| [C Lucky Numbers (python)](../../solutions/math/combinatorics/C_Lucky_Numbers.py) | math/combinatorics | reviewed |
| [C Max Non Attacking Knights (cpp)](../../solutions/math/arithmetic/C_Max_Non_Attacking_Knights.cpp) | math/arithmetic | reviewed |
| [C Pythagorean Triples (cpp)](../../solutions/constructive/C_Pythagorean_Triples.cpp) | constructive | reviewed |
| [C Sums (python)](../../solutions/math/arithmetic/C_Sums.py) | math/arithmetic | reviewed |
| [C. Increase and Copy (cpp)](../../solutions/math/arithmetic/C_Increase_and_Copy.cpp) | math/arithmetic | reviewed |
| [cf A Adding Digits (cpp)](../../solutions/constructive/cf-A_Adding_Digits.cpp) | constructive | reviewed |
| [cf adding digits (python)](../../solutions/constructive/cf-adding-digits.py) | constructive | reviewed |
| [cf cheaptravel (cpp)](../../solutions/brute-force-and-backtracking/cf-cheaptravel.cpp) | brute-force-and-backtracking | reviewed |
| [cf clockwork (cpp)](../../solutions/greedy/cf-clockwork.cpp) | greedy | reviewed |
| [cf fancyfence (cpp)](../../solutions/math/arithmetic/cf-fancyfence.cpp) | math/arithmetic | reviewed |
| [cf fizzbuzzremixed (cpp)](../../solutions/math/arithmetic/cf-fizzbuzzremixed.cpp) | math/arithmetic | reviewed |
| [cf fun (cpp)](../../solutions/brute-force-and-backtracking/cf-fun.cpp) | brute-force-and-backtracking | reviewed |
| [cf kthnondivisible (cpp)](../../solutions/math/arithmetic/cf-kthnondivisible.cpp) | math/arithmetic | reviewed |
| [cf newmenewarray (cpp)](../../solutions/math/arithmetic/cf-newmenewarray.cpp) | math/arithmetic | reviewed |
| [Children Holiday (cpp)](../../solutions/binary-search/Children_Holiday.cpp) | binary-search | reviewed |
| [coin piles (cpp)](../../solutions/math/arithmetic/coin_piles.cpp) | math/arithmetic | reviewed |
| [cses readingbooks (cpp)](../../solutions/greedy/cses-readingbooks.cpp) | greedy | reviewed |
| [D - Circle Lattice Points (python)](../../solutions/geometry/D_Circle_Lattice_Points.py) | geometry | reviewed |
| [D - Mix Plate (cpp)](../../solutions/math/arithmetic/D_Mix_Plate.cpp) | math/arithmetic | reviewed |
| [D Decorating Christmas Tree (cpp)](../../solutions/greedy/D_Decorating_Christmas_Tree.cpp) | greedy | reviewed |
| [D Grouping Odds (python)](../../solutions/math/arithmetic/D_Grouping_Odds.py) | math/arithmetic | reviewed |
| [D. Plus Minus Permutation (cpp)](../../solutions/math/number-theory/D_Plus_Minus_Permutation.cpp) | math/number-theory | reviewed |
| [D. Sahla bas Sa7la (cpp)](../../solutions/math/arithmetic/D_Sahla_bas_Sa_7_la.cpp) | math/arithmetic | reviewed |
| [E - Integer Moves (python)](../../solutions/geometry/E_Integer_Moves.py) | geometry | reviewed |
| [E Generosity (cpp)](../../solutions/math/arithmetic/E_Generosity.cpp) | math/arithmetic | reviewed |
| [E Job Fair (cpp)](../../solutions/greedy/E_Job_Fair.cpp) | greedy | reviewed |
| [E. Insane Problem (cpp)](../../solutions/binary-search/E_Insane_Problem.cpp) | binary-search | reviewed |
| [etruscan warriors (cpp)](../../solutions/math/arithmetic/etruscan_warriors.cpp) | math/arithmetic | reviewed |
| [ezzat (python)](../../solutions/greedy/ezzat.py) | greedy | reviewed |
| [F - Brightness Begins (cpp)](../../solutions/binary-search/F_Brightness_Begins.cpp) | binary-search | reviewed |
| [F - Digits (cpp)](../../solutions/math/number-theory/F_Digits.cpp) | math/number-theory | reviewed |
| [F Library Fine (python)](../../solutions/math/arithmetic/F_Library_Fine.py) | math/arithmetic | reviewed |
| [G - Bowling Frame (cpp)](../../solutions/binary-search/G_Bowling_Frame.cpp) | binary-search | reviewed |
| [G - G (cpp)](../../solutions/math/arithmetic/G_G.cpp) | math/arithmetic | reviewed |
| [G Even Odds (cpp)](../../solutions/math/arithmetic/G_Even_Odds.cpp) | math/arithmetic | reviewed |
| [G Stamina (cpp)](../../solutions/math/arithmetic/G_Stamina.cpp) | math/arithmetic | reviewed |
| [H Make Equal (python)](../../solutions/math/arithmetic/H_Make_Equal.py) | math/arithmetic | reviewed |
| [hackerrank lowest triangle (cpp)](../../solutions/math/arithmetic/hackerrank-lowest-triangle.cpp) | math/arithmetic | reviewed |
| [J Arrival of the General (python)](../../solutions/greedy/J_Arrival_of_the_General.py) | greedy | reviewed |
| [J Domino piling (cpp)](../../solutions/math/arithmetic/J_Domino_piling.cpp) | math/arithmetic | reviewed |
| [K - Counting Test (cpp)](../../solutions/prefix-sums/K_Counting_Test.cpp) | prefix-sums | reviewed |
| [kattis bubbletea (cpp)](../../solutions/brute-force-and-backtracking/kattis-bubbletea.cpp) | brute-force-and-backtracking | reviewed |
| [L - Interesting Function (cpp)](../../solutions/math/arithmetic/L_Interesting_Function.cpp) | math/arithmetic | reviewed |
| [M Floor Number (cpp)](../../solutions/math/arithmetic/M_Floor_Number.cpp) | math/arithmetic | reviewed |
| [missing number (cpp)](../../solutions/math/arithmetic/missing-number.cpp) | math/arithmetic | reviewed |
| [moobuzz (cpp)](../../solutions/binary-search/moobuzz.cpp) | binary-search | reviewed |
| [N Square Counting (cpp)](../../solutions/math/arithmetic/N_Square_Counting.cpp) | math/arithmetic | reviewed |
| [number spiral (cpp)](../../solutions/math/arithmetic/number_spiral.cpp) | math/arithmetic | reviewed |
| [O Vasya and Coins (cpp)](../../solutions/math/arithmetic/O_Vasya_and_Coins.cpp) | math/arithmetic | reviewed |
| [Problem 1. Fence Painting (cpp)](../../solutions/intervals/Problem_1_Fence_Painting.cpp) | intervals | reviewed |
| [Problem 1. Square Pasture (cpp)](../../solutions/geometry/Problem_1_Square_Pasture.cpp) | geometry | reviewed |
| [Q Food for Animals (cpp)](../../solutions/math/arithmetic/Q_Food_for_Animals.cpp) | math/arithmetic | reviewed |
| [q8 (python)](../../solutions/math/arithmetic/q8.py) | math/arithmetic | reviewed |
| [searching for nessy (cpp)](../../solutions/math/arithmetic/searching_for_nessy.cpp) | math/arithmetic | reviewed |
| [T Savings (cpp)](../../solutions/math/arithmetic/T_Savings.cpp) | math/arithmetic | reviewed |
| [tarifa (cpp)](../../solutions/math/arithmetic/tarifa.cpp) | math/arithmetic | reviewed |
| [The Third Side (cpp)](../../solutions/greedy/The_Third_Side.cpp) | greedy | reviewed |
| [time travelling temperatures (cpp)](../../solutions/math/arithmetic/time-travelling-temperatures.cpp) | math/arithmetic | reviewed |
| [traffic lights (cpp)](../../references/model-solutions/math/arithmetic/traffic-lights.cpp) | math/arithmetic | reviewed |
| [trailing zeros (cpp)](../../solutions/math/number-theory/trailing_zeros.cpp) | math/number-theory | reviewed |
| [troc runningforpresident (cpp)](../../solutions/math/arithmetic/troc-runningforpresident.cpp) | math/arithmetic | reviewed |
| [two tables (python)](../../solutions/geometry/two-tables.py) | geometry | reviewed |
| [uva chess (cpp)](../../solutions/math/arithmetic/uva-chess.cpp) | math/arithmetic | reviewed |
| [uva knights (cpp)](../../solutions/math/arithmetic/uva-knights.cpp) | math/arithmetic | reviewed |
| [uva tariffplan (cpp)](../../solutions/math/arithmetic/uva-tariffplan.cpp) | math/arithmetic | reviewed |
| [wooden ladder (python)](../../solutions/greedy/wooden_ladder.py) | greedy | reviewed |
| [X - Profitable Interest Rate (cpp)](../../solutions/math/arithmetic/X_Profitable_Interest_Rate.cpp) | math/arithmetic | reviewed |
| [x axis (python)](../../solutions/math/arithmetic/x-axis.py) | math/arithmetic | reviewed |

<!-- examples:end -->
