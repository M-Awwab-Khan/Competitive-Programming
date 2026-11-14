# Sort then greedy

Sort by the key that an exchange argument says must come first, then make one irrevocable choice per element in that order.

## Recognition clues

- "Maximum number of items/tasks/people you can serve", "minimum total cost", "can you beat all of them" with no order imposed by the input.
- Swapping two adjacent items in an optimal answer can be compared locally (exchange argument): `x` before `y` is never worse when `key(x) <= key(y)`.
- Pairing two multisets or elements of one multiset: smallest-with-largest, i-th-with-i-th, heaviest-with-lightest.
- Reachability that grows monotonically as you absorb items (current strength, reachable sum, available RAM).

## Invariant and variants

After processing the first `i` items in sorted order, the chosen set is optimal among the first `i` items (or can be extended to an optimal full solution). Prove it by swapping any out-of-order pair in an optimal answer.

| Order / greedy | Why it works | Repo illustration |
| --- | --- | --- |
| Ascending, absorb while reachable | Taking the weakest first only increases current power | `A_Dragons.py`, `download_more_ram.py`, `B_Collecting_Game.cpp` |
| Smallest unreachable sum `reach` (start 1); stop when `a_i > reach`, else `reach += a_i` | All of `[1, reach)` stays representable | `missing_coin_sum.cpp`, `G_2_Subsequence_Addition_Hard_Version.cpp` |
| Shortest processing time first | Sum of finish times is minimised by SPT | `cses-tasksanddeadline.cpp`, `C_Rudolf_and_the_Another_Competition.cpp` |
| Earliest end first | Leaves the most room for the rest | `movie_festival.cpp` (see [interval scheduling](interval-scheduling-and-sweep.md)) |
| Rearrangement inequality | Pair largest weight with smallest (or largest) partner | `H_Permutator.cpp`, `Balatro.cpp`, `C_Building_Permutation.cpp` |
| Two ends of a sorted array | Heaviest must go somewhere; pair with lightest if it fits | `ferris_wheel.cpp`, `apartments.py`, `A_Very_Different_Array.cpp` |
| Take the `k` best gains | Gains are independent | `songs_compression.py`, `sellstocks.py`, `C_Stable_Groups.cpp` |
| Sort by a combined key | Feasibility of a pair depends on `a + b` | `F_1_Complete_the_Projects_easy_version.cpp` |

### Median minimises absolute deviation

`sum |a_i - x|` is minimised at any median: moving `x` past a point changes the sum by (points left) minus (points right). `cses-sticks.cpp` sorts and uses `a[n/2]`. For even `n`, any `x` in `[a[n/2-1], a[n/2]]` works. Squared deviation is minimised at the mean instead.

Complexity: `O(n log n)` for the sort, `O(n)` for the scan, unless the greedy step needs a [priority queue](priority-queue-greedy.md) or [ordered set](ordered-set-queries.md).

## Common mistakes

- Greedy by the wrong key: test a two-element exchange before coding.
- Simulating increments one at a time: `B_Soldier_and_Badges.cpp` bumps duplicates in a nested loop, `O(n^2)` worst case; instead keep `next = max(next, a_i)` and add `next - a_i`.
- Overflow in accumulated sums or products of weights (`(i+1)(n-i) * a_i * b_i`).
- Losing original indices when the output needs them: sort pairs `(value, index)`.
- Ties: when equal keys matter, specify a secondary key (`(score desc, penalty asc, index)`).

## Related patterns

If the choice depends on items seen so far rather than a fixed order, switch to a [priority-queue greedy](priority-queue-greedy.md). Matching against the nearest available partner uses [sorted lookup](sorted-lookup.md) or [ordered-set queries](ordered-set-queries.md); paired pointers from both ends are a [two-pointer](two-pointer-window.md) scan. Monotone feasibility often pairs with [binary search on the answer](binary-search-on-answer.md), and weight-by-occurrence sums use the [contribution technique](contribution-technique.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A - Very Different Array (cpp)](../../solutions/greedy/A_Very_Different_Array.cpp) | greedy | reviewed |
| [A A Gift From Orangutan (cpp)](../../solutions/sorting-and-searching/A_A_Gift_From_Orangutan.cpp) | sorting-and-searching | reviewed |
| [A Appleman and Toastman (cpp)](../../solutions/greedy/A_Appleman_and_Toastman.cpp) | greedy | reviewed |
| [A Business trip (cpp)](../../solutions/greedy/A_Business_trip.cpp) | greedy | reviewed |
| [A Cups of Cocoa (cpp)](../../solutions/greedy/A_Cups_of_Cocoa.cpp) | greedy | reviewed |
| [A Dragons (python)](../../solutions/greedy/A_Dragons.py) | greedy | reviewed |
| [A-B Knapsack (cpp)](../../solutions/greedy/A-B_Knapsack.cpp) | greedy | reviewed |
| [A. Knapsack (cpp)](../../solutions/greedy/A_Knapsack.cpp) | greedy | reviewed |
| [A. Red Bus (cpp)](../../solutions/sorting-and-searching/A_Red_Bus.cpp) | sorting-and-searching | reviewed |
| [A. Strange Birthday Party (cpp)](../../solutions/greedy/A_Strange_Birthday_Party.cpp) | greedy | reviewed |
| [apartments (python)](../../solutions/greedy/apartments.py) | greedy | reviewed |
| [array coloring (python)](../../solutions/greedy/array_coloring.py) | greedy | reviewed |
| [B Array Recoloring (cpp)](../../solutions/greedy/B_Array_Recoloring.cpp) | greedy | reviewed |
| [B Budget Allotment (cpp)](../../solutions/greedy/B_Budget_Allotment.cpp) | greedy | reviewed |
| [B Devu the Dumb Guy (cpp)](../../solutions/greedy/B_Devu_the_Dumb_Guy.cpp) | greedy | reviewed |
| [B George and Round (cpp)](../../solutions/greedy/B_George_and_Round.cpp) | greedy | reviewed |
| [B Soldier and Badges (cpp)](../../solutions/greedy/B_Soldier_and_Badges.cpp) | greedy | reviewed |
| [B The Child and Set (cpp)](../../solutions/greedy/B_The_Child_and_Set.cpp) | greedy | reviewed |
| [B. Buying Lemonade (cpp)](../../solutions/greedy/B_Buying_Lemonade.cpp) | greedy | reviewed |
| [B. Collecting Game (cpp)](../../solutions/greedy/B_Collecting_Game.cpp) | greedy | reviewed |
| [B. Equal Rectangles (python)](../../solutions/sorting-and-searching/B_Equal_Rectangles.py) | sorting-and-searching | reviewed |
| [Balatro (cpp)](../../solutions/greedy/Balatro.cpp) | greedy | reviewed |
| [Books on a Shelf (cpp)](../../solutions/constructive/Books_on_a_Shelf.cpp) | constructive | reviewed |
| [bottles and gems (cpp)](../../solutions/greedy/bottles_and_gems.cpp) | greedy | reviewed |
| [C Building Permutation (cpp)](../../solutions/greedy/C_Building_Permutation.cpp) | greedy | reviewed |
| [C Photographer (cpp)](../../solutions/greedy/C_Photographer.cpp) | greedy | reviewed |
| [C Stable Groups (cpp)](../../solutions/greedy/C_Stable_Groups.cpp) | greedy | reviewed |
| [C. Exams (cpp)](../../solutions/greedy/C_Exams.cpp) | greedy | reviewed |
| [C. Kero ! Kero ! El3ab ya Kero ! (cpp)](../../solutions/games/C_Kero_Kero_El_3_ab_ya_Kero.cpp) | games | reviewed |
| [C. Rudolf and the Another Competition (cpp)](../../solutions/sorting-and-searching/C_Rudolf_and_the_Another_Competition.cpp) | sorting-and-searching | reviewed |
| [C. Virus (cpp)](../../solutions/greedy/C_Virus.cpp) | greedy | reviewed |
| [cf B Appleman and Card Game (cpp)](../../solutions/greedy/cf-B_Appleman_and_Card_Game.cpp) | greedy | reviewed |
| [cf gorilla and the exam (cpp)](../../solutions/greedy/cf-gorilla-and-the-exam.cpp) | greedy | reviewed |
| [cf news about credit (cpp)](../../solutions/greedy/cf-news-about-credit.cpp) | greedy | reviewed |
| [cses sticks (cpp)](../../solutions/greedy/cses-sticks.cpp) | greedy | reviewed |
| [cses tasksanddeadline (cpp)](../../solutions/greedy/cses-tasksanddeadline.cpp) | greedy | reviewed |
| [cses towers (cpp)](../../solutions/data-structures/ordered-sets/cses-towers.cpp) | data-structures/ordered-sets | reviewed |
| [D Queue (cpp)](../../solutions/greedy/D_Queue.cpp) | greedy | reviewed |
| [D Skibidus and Sigma (cpp)](../../solutions/greedy/D_Skibidus_and_Sigma.cpp) | greedy | reviewed |
| [D. Destruction of the Dandelion Fields (cpp)](../../solutions/greedy/D_Destruction_of_the_Dandelion_Fields.cpp) | greedy | reviewed |
| [download more ram (python)](../../solutions/greedy/download_more_ram.py) | greedy | reviewed |
| [E khba loves to sleep (cpp)](../../solutions/greedy/E_khba_loves_to_sleep.cpp) | greedy | reviewed |
| [E Make Empty (cpp)](../../solutions/greedy/E_Make_Empty.cpp) | greedy | reviewed |
| [E. Boxers (cpp)](../../solutions/greedy/E_Boxers.cpp) | greedy | reviewed |
| [F1. Complete the Projects (easy version) (cpp)](../../solutions/greedy/F_1_Complete_the_Projects_easy_version.cpp) | greedy | reviewed |
| [ferris wheel (cpp)](../../solutions/greedy/ferris_wheel.cpp) | greedy | reviewed |
| [friends and the restaurant (python)](../../solutions/greedy/friends_and_the_restaurant.py) | greedy | reviewed |
| [G. Matching (cpp)](../../solutions/greedy/G_Matching.cpp) | greedy | reviewed |
| [G2. Subsequence Addition (Hard Version) (cpp)](../../solutions/greedy/G_2_Subsequence_Addition_Hard_Version.cpp) | greedy | reviewed |
| [H. Permutator (cpp)](../../solutions/greedy/H_Permutator.cpp) | greedy | reviewed |
| [I Chores (cpp)](../../solutions/greedy/I_Chores.cpp) | greedy | reviewed |
| [kayaking (python)](../../solutions/brute-force-and-backtracking/kayaking.py) | brute-force-and-backtracking | reviewed |
| [maximum nonoverlapping segments (cpp)](../../solutions/greedy/maximum-nonoverlapping-segments.cpp) | greedy | reviewed |
| [missing coin sum (cpp)](../../solutions/greedy/missing_coin_sum.cpp) | greedy | reviewed |
| [movie festival (cpp)](../../solutions/greedy/movie_festival.cpp) | greedy | reviewed |
| [Oil business (cpp)](../../solutions/graphs/spanning-trees/Oil_business.cpp) | graphs/spanning-trees | reviewed |
| [paint numbers (python)](../../solutions/greedy/paint_numbers.py) | greedy | reviewed |
| [Pair Selection (cpp)](../../solutions/binary-search/Pair_Selection.cpp) | binary-search | reviewed |
| [sellstocks (python)](../../solutions/greedy/sellstocks.py) | greedy | reviewed |
| [songs compression (python)](../../solutions/greedy/songs_compression.py) | greedy | reviewed |
| [USACO Why Did the Cow Cross the Road III (cpp)](../../solutions/simulation/USACO_Why_Did_the_Cow_Cross_the_Road_III.cpp) | simulation | reviewed |
| [very different array (python)](../../solutions/greedy/very_different_array.py) | greedy | reviewed |
| [Young Explorers (cpp)](../../solutions/greedy/Young_Explorers.cpp) | greedy | reviewed |

<!-- examples:end -->
