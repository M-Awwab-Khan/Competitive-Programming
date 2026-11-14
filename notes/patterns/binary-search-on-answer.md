# Binary search on the answer

Use this when a problem asks for the smallest or largest feasible value and checking one candidate is easier than constructing the optimum directly.

## Recognition clues

Look for “minimum time to produce,” “maximum minimum distance,” or a resource limit under which a target must be achievable. Define `possible(x)` precisely before choosing bounds. Its truth value must change at most once across the search interval.

In `factory_machines.cpp`, feasibility at time `x` means `sum(x / machine_time) >= target`. More time cannot reduce production. In `Aggressive_cows.cpp`, feasibility at distance `d` uses greedy placement in sorted stalls; increasing the required spacing cannot make placement easier.

## Invariant and boundaries

For the smallest feasible integer, maintain an interval containing the answer. With `mid = lo + (hi - lo) / 2`, a feasible midpoint permits `hi = mid`; otherwise use `lo = mid + 1`. This requires a known feasible upper bound.

For the largest feasible integer, keep the best feasible midpoint and search above it, or use an upper midpoint with an appropriate interval invariant. Write the invariant beside the loop rather than mixing updates from different templates.

If checking a candidate costs `T(n)` and the candidate range has width `R`, the search costs `O(T(n) log R)`, plus preprocessing such as sorting.

When no safe upper bound is obvious, start with a small `hi` and double it until `check(hi)` holds; this costs only `O(log answer)` extra checks. If the check compares a product with a target (`(side / w) * (side / h) >= n`), compare `cols >= ceil(n / rows)` instead so nothing overflows.

For a real-valued answer (a length, a time), keep `lo` infeasible and `hi` feasible (or the reverse) and run a fixed number of iterations, for example 100, instead of `while (hi - lo > eps)`. A fixed count always terminates and gives relative precision even when the answer is large.

**Averages and ratios.** To decide whether some choice reaches average or ratio `x`, subtract `x` from every value (`a_i - x`, or `a_i - x * b_i` for `sum a / sum b`) and ask whether the transformed total can be `>= 0` (or `<= 0` when minimising). That turns a ratio into an ordinary sum: pick the `k` largest transformed values, take the best segment of length at least `k` with prefix sums and a running prefix minimum, or run a shortest-path DP on a DAG with edge weights `w - x`.

| Check shape | Monotone because |
| --- | --- |
| Greedy placement with spacing `>= d` (cows in stalls) | larger spacing never fits more items |
| Greedy split into groups with sum `<= x`, count groups | a larger cap never needs more groups |
| Units produced by time `t`, possibly with rest cycles | more time never produces less |
| `sum(min(a_i, x)) >= k * x` (teams of `k` from distinct groups) | each group gives at most one member per team |
| All intervals `[x_i - t v_i, x_i + t v_i]` intersect (meeting point) | intervals only grow with `t` |
| Path exists using only edges of weight `<= x`, within `d` steps | allowing more edges never lengthens the shortest path |

## Common mistakes

- Binary searching a predicate that is not monotone.
- Using an upper bound that might still be infeasible.
- Overflow in midpoint, products, or accumulated production. Stop accumulating once the target is reached if larger totals are irrelevant.
- Treating a sorted-array bound query as an answer-feasibility search without identifying the predicate.

## Related patterns

Prefix aggregates can make a feasibility check cheap; see [prefix sums with a frequency map](prefix-sum-frequency-map.md) for a different use of cumulative state. See the [pattern hub](INDEX.md) for the other canonical notes.

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [Aggressive cows (cpp)](../../solutions/binary-search/Aggressive_cows.cpp) | binary-search | reviewed |
| [array division (python)](../../solutions/binary-search/array_division.py) | binary-search | reviewed |
| [B - Maximum Median (cpp)](../../solutions/binary-search/B_Maximum_Median.cpp) | binary-search | reviewed |
| [B Burning Midnight Oil (cpp)](../../solutions/binary-search/B_Burning_Midnight_Oil.cpp) | binary-search | reviewed |
| [B Cubes Sum (cpp)](../../solutions/math/arithmetic/B_Cubes_Sum.cpp) | math/arithmetic | reviewed |
| [B Cubes Sum (python)](../../solutions/math/arithmetic/B_Cubes_Sum.py) | math/arithmetic | reviewed |
| [B. Fear of the Dark (cpp)](../../solutions/binary-search/B_Fear_of_the_Dark.cpp) | binary-search | reviewed |
| [B. Getting Points (cpp)](../../solutions/binary-search/B_Getting_Points.cpp) | binary-search | reviewed |
| [B. Vanya and Lanterns (cpp)](../../solutions/binary-search/B_Vanya_and_Lanterns.cpp) | binary-search | reviewed |
| [bake fishes (python)](../../solutions/binary-search/bake_fishes.py) | binary-search | reviewed |
| [C - C (cpp)](../../solutions/binary-search/C_C.cpp) | binary-search | reviewed |
| [C - ICPC Practice (cpp)](../../solutions/binary-search/C_ICPC_Practice.cpp) | binary-search | reviewed |
| [C Limited Repainting (cpp)](../../solutions/binary-search/C_Limited_Repainting.cpp) | binary-search | reviewed |
| [cf books (cpp)](../../solutions/binary-search/cf-books.cpp) | binary-search | reviewed |
| [Children Holiday (cpp)](../../solutions/binary-search/Children_Holiday.cpp) | binary-search | reviewed |
| [covid (python)](../../solutions/binary-search/covid.py) | binary-search | reviewed |
| [Cows in Stalls (cpp)](../../solutions/binary-search/Cows_in_Stalls.cpp) | binary-search | reviewed |
| [D. Javed Nihari (cpp)](../../solutions/binary-search/D_Javed_Nihari.cpp) | binary-search | reviewed |
| [D1. Magic Powder - 1 (cpp)](../../solutions/binary-search/D_1_Magic_Powder_1.cpp) | binary-search | reviewed |
| [D2. Magic Powder - 2 (cpp)](../../solutions/binary-search/D_2_Magic_Powder_2.cpp) | binary-search | reviewed |
| [E - Cut in Half (cpp)](../../solutions/binary-search/E_Cut_in_Half.cpp) | binary-search | reviewed |
| [E - Robin Hood in Town (cpp)](../../solutions/binary-search/E_Robin_Hood_in_Town.cpp) | binary-search | reviewed |
| [E Feed the Beast (cpp)](../../solutions/binary-search/E_Feed_the_Beast.cpp) | binary-search | reviewed |
| [E. Building an Aquarium (cpp)](../../solutions/binary-search/E_Building_an_Aquarium.cpp) | binary-search | reviewed |
| [E. Cardboard for Pictures (cpp)](../../solutions/binary-search/E_Cardboard_for_Pictures.cpp) | binary-search | reviewed |
| [Eko (cpp)](../../solutions/binary-search/Eko.cpp) | binary-search | reviewed |
| [Equation (cpp)](../../solutions/binary-search/Equation.cpp) | binary-search | reviewed |
| [factory machines (cpp)](../../solutions/binary-search/factory_machines.cpp) | binary-search | reviewed |
| [G The Veneto Relay (cpp)](../../solutions/binary-search/G_The_Veneto_Relay.cpp) | binary-search | reviewed |
| [Get together (cpp)](../../solutions/binary-search/Get_together.cpp) | binary-search | reviewed |
| [Hamburgers (cpp)](../../solutions/binary-search/Hamburgers.cpp) | binary-search | reviewed |
| [I - Meeting on the Line (cpp)](../../solutions/binary-search/I_Meeting_on_the_Line.cpp) | binary-search | reviewed |
| [J - Magic Ship (cpp)](../../solutions/binary-search/J_Magic_Ship.cpp) | binary-search | reviewed |
| [K - The Meeting Place Cannot Be Changed (cpp)](../../solutions/binary-search/K_The_Meeting_Place_Cannot_Be_Changed.cpp) | binary-search | reviewed |
| [M - Mafia (cpp)](../../solutions/binary-search/M_Mafia.cpp) | binary-search | reviewed |
| [magic powder ii (cpp)](../../solutions/binary-search/magic_powder_ii.cpp) | binary-search | reviewed |
| [Maximum Average Segment (cpp)](../../solutions/binary-search/Maximum_Average_Segment.cpp) | binary-search | reviewed |
| [maximum median (cpp)](../../solutions/binary-search/maximum_median.cpp) | binary-search | reviewed |
| [Minimum Average Path (cpp)](../../solutions/binary-search/Minimum_Average_Path.cpp) | binary-search | reviewed |
| [Minimum maximum on the Path (cpp)](../../solutions/binary-search/Minimum_maximum_on_the_Path.cpp) | binary-search | reviewed |
| [moobuzz (cpp)](../../solutions/binary-search/moobuzz.cpp) | binary-search | reviewed |
| [O - Cat, Fox and the Lonely Array (cpp)](../../solutions/binary-search/O_Cat_Fox_and_the_Lonely_Array.cpp) | binary-search | reviewed |
| [Packing Rectangles (cpp)](../../solutions/binary-search/Packing_Rectangles.cpp) | binary-search | reviewed |
| [Pair Selection (cpp)](../../solutions/binary-search/Pair_Selection.cpp) | binary-search | reviewed |
| [poinsnoned dagger (python)](../../solutions/binary-search/poinsnoned_dagger.py) | binary-search | reviewed |
| [Rameez And The Missing Numbers (cpp)](../../solutions/binary-search/Rameez_And_The_Missing_Numbers.cpp) | binary-search | reviewed |
| [Ropes (cpp)](../../solutions/binary-search/Ropes.cpp) | binary-search | reviewed |
| [Splitting an Array (cpp)](../../solutions/binary-search/Splitting_an_Array.cpp) | binary-search | reviewed |
| [Student Councils (cpp)](../../solutions/binary-search/Student_Councils.cpp) | binary-search | reviewed |
| [T - Set (cpp)](../../solutions/binary-search/T_Set.cpp) | binary-search | reviewed |
| [TripTastic (cpp)](../../solutions/binary-search/TripTastic.cpp) | binary-search | reviewed |
| [utpc 3 11 a (cpp)](../../solutions/binary-search/utpc-3-11-a.cpp) | binary-search | reviewed |
| [utpc 3 11 e (cpp)](../../solutions/binary-search/utpc-3-11-e.cpp) | binary-search | reviewed |
| [uva throughthedesert (cpp)](../../solutions/binary-search/uva-throughthedesert.cpp) | binary-search | reviewed |
| [Very Easy Task (cpp)](../../solutions/binary-search/Very_Easy_Task.cpp) | binary-search | reviewed |

<!-- examples:end -->
