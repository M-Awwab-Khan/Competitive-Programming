# Sorted lookup with binary search

Sort a static array once, then answer each "how many are `<= x`", "nearest element to `x`", or "which bucket contains `x`" query with `lower_bound` / `upper_bound` in `O(log n)`.

## Recognition clues

- Many independent queries against a fixed multiset ("how many shops can I afford with `x`").
- Counting pairs `i < j` with `a_i + a_j` in a range: sort, fix one side, binary search the other.
- Locating a position inside cumulative lengths: songs in a playlist, worms in piles, run-length decoded strings.
- Nearest neighbour on a line (closest tower, tallest strictly shorter).
- Order of the input does not matter for the counted quantity.

## Invariant and variants

On sorted `a` (size `n`):

| Question | Expression |
| --- | --- |
| count `< x` | `lower_bound(a, x) - a.begin()` |
| count `<= x` | `upper_bound(a, x) - a.begin()` |
| count in `[lo, hi]` | `upper_bound(hi) - lower_bound(lo)` |
| smallest `>= x` | `*lower_bound(x)` if not `end` |
| largest `<= x` | `*prev(upper_bound(x))` if not `begin` |
| bucket of label `x` in cumulative ends `E` | `lower_bound(E, x)` (first end `>= x`) |

```text
sort(a)
for i in 0..n-1:                        // pairs with sum in [L, R]
    ans += upper_bound(a+i+1, a+n, R-a[i]) - lower_bound(a+i+1, a+n, L-a[i])
```

Variants seen in this repo:

- **Prefix sums + bound:** `E_Eating_Queries.cpp`, `H_Zaglol_vs_the_British_Occupation.cpp`, `cf-eugeny-playlist.cpp`, `G_Cryptogram.cpp` search a non-decreasing cumulative array. `E_Scuza.cpp` searches prefix *maxima*, which are monotone even when the raw array is not.
- **Count `>= x` and subtract overlap:** `C_Two_Colors.cpp` and `1.py` multiply counts for two sides, then remove choices where one item is used twice.
- **Range of pairs as two prefixes:** `H_Number_of_Pairs.cpp` computes `count(sum <= R) - count(sum <= L - 1)`.
- **Circular data:** double the array or split the query into two ranges on wraparound (`C_Traffic_Light.cpp`, `E_Laser_Takahashi.cpp`).
- **Sign of a polynomial from sorted roots:** parity of roots on one side of `x` (`The_Wave.cpp`, `roots.py`).
- **Meet in the middle:** sort one half's subset sums and count matches (`J_Meet_in_the_Middle.cpp`).

Complexity: `O(n log n)` sort plus `O(log n)` per query; memory `O(n)`. If elements are removed between queries, the array is no longer static: use [ordered-set queries](ordered-set-queries.md).

## Common mistakes

- Off-by-one between `lower_bound` and `upper_bound`: "price `<= x`" is `upper_bound(x)` or equivalently `lower_bound(x + 1)` for integers.
- Decrementing an iterator returned at `begin()` (largest `<= x` that does not exist); check before `it--`. `O_Trinity.cpp` is safe only because its search starts at `l + 2`.
- Searching the whole array when pairs require `j > i`: restrict to `a + i + 1`.
- Floating-point keys (polar angles via `atan2` in `E_Laser_Takahashi`) can make equal directions compare unequal; prefer exact integer comparisons where possible.
- Recomputing `accumulate` inside a binary-search check (`E_Robin_Hood_in_Town.cpp`) adds an avoidable `O(n)` per step.
- Debug output left in (`roots.py` prints the index before the answer).

## Related patterns

When the searched quantity is the *answer* rather than an element, use [binary search on the answer](binary-search-on-answer.md). Cumulative arrays come from [prefix sums and difference arrays](prefix-sums-and-difference-arrays.md). Pair counting with sorted arrays overlaps [two-pointer windows](two-pointer-window.md) and [pair counting with inclusion-exclusion](pair-counting-inclusion-exclusion.md); split enumeration is [meet in the middle](meet-in-the-middle.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [1 (python)](../../solutions/sorting-and-searching/1.py) | sorting-and-searching | reviewed |
| [A Drink Accordingly (cpp)](../../solutions/sorting-and-searching/A_Drink_Accordingly.cpp) | sorting-and-searching | reviewed |
| [B Chat Online (cpp)](../../solutions/binary-search/B_Chat_Online.cpp) | binary-search | reviewed |
| [B. Interesting drink (cpp)](../../solutions/sorting-and-searching/B_Interesting_drink.cpp) | sorting-and-searching | reviewed |
| [B. Worms (cpp)](../../solutions/prefix-sums/B_Worms.cpp) | prefix-sums | reviewed |
| [C 2 Skibidus and Fanum Tax hard version (cpp)](../../solutions/greedy/C_2_Skibidus_and_Fanum_Tax_hard_version.cpp) | greedy | reviewed |
| [C Two Colors (cpp)](../../solutions/sorting-and-searching/C_Two_Colors.cpp) | sorting-and-searching | reviewed |
| [C. Fady: Ya baraaaa el mat3am feeeen (cpp)](../../solutions/sorting-and-searching/C_Fady_Ya_baraaaa_el_mat_3_am_feeeen.cpp) | sorting-and-searching | reviewed |
| [C. Flower City Fence (cpp)](../../solutions/sorting-and-searching/C_Flower_City_Fence.cpp) | sorting-and-searching | reviewed |
| [C. Traffic Light (cpp)](../../solutions/binary-search/C_Traffic_Light.cpp) | binary-search | reviewed |
| [cf cellularnetwork (cpp)](../../solutions/binary-search/cf-cellularnetwork.cpp) | binary-search | reviewed |
| [cf countingpairs (cpp)](../../solutions/sorting-and-searching/cf-countingpairs.cpp) | sorting-and-searching | reviewed |
| [cf countingpairs (python)](../../solutions/sorting-and-searching/cf-countingpairs.py) | sorting-and-searching | reviewed |
| [cf eugeny playlist (cpp)](../../solutions/binary-search/cf-eugeny-playlist.cpp) | binary-search | reviewed |
| [counting haybales (python)](../../solutions/sorting-and-searching/counting-haybales.py) | sorting-and-searching | reviewed |
| [E - Laser Takahashi (cpp)](../../solutions/geometry/E_Laser_Takahashi.cpp) | geometry | reviewed |
| [E - Laser Takahashi (python)](../../solutions/geometry/E_Laser_Takahashi.py) | geometry | reviewed |
| [E - Robin Hood in Town (cpp)](../../solutions/binary-search/E_Robin_Hood_in_Town.cpp) | binary-search | reviewed |
| [E. Eating Queries (cpp)](../../solutions/prefix-sums/E_Eating_Queries.cpp) | prefix-sums | reviewed |
| [E. Scuza (cpp)](../../solutions/prefix-sums/E_Scuza.cpp) | prefix-sums | reviewed |
| [F Divisors Count (cpp)](../../solutions/math/number-theory/F_Divisors_Count.cpp) | math/number-theory | reviewed |
| [F Frosted Highway Hard (cpp)](../../solutions/math/number-theory/F_Frosted_Highway_Hard.cpp) | math/number-theory | reviewed |
| [F. Ant colony (cpp)](../../solutions/data-structures/range-queries/F_Ant_colony.cpp) | data-structures/range-queries | reviewed |
| [F. Yet Another Problem About Pairs Satisfying an Inequality (cpp)](../../solutions/sorting-and-searching/F_Yet_Another_Problem_About_Pairs_Satisfying_an_Inequality.cpp) | sorting-and-searching | reviewed |
| [G - Queries about less or equal elements (cpp)](../../solutions/sorting-and-searching/G_Queries_about_less_or_equal_elements.cpp) | sorting-and-searching | reviewed |
| [G Cryptogram (cpp)](../../solutions/strings/G_Cryptogram.cpp) | strings | reviewed |
| [H - Number of Pairs (cpp)](../../solutions/binary-search/H_Number_of_Pairs.cpp) | binary-search | reviewed |
| [H. Zaglol vs. the British Occupation (cpp)](../../solutions/binary-search/H_Zaglol_vs_the_British_Occupation.cpp) | binary-search | reviewed |
| [J - Meet in the Middle (cpp)](../../solutions/meet-in-the-middle/J_Meet_in_the_Middle.cpp) | meet-in-the-middle | reviewed |
| [kattis roompainting (cpp)](../../solutions/binary-search/kattis-roompainting.cpp) | binary-search | reviewed |
| [luchu bandr (cpp)](../../solutions/binary-search/luchu_bandr.cpp) | binary-search | reviewed |
| [Monster Game (cpp)](../../solutions/binary-search/Monster_Game.cpp) | binary-search | reviewed |
| [O - Trinity (cpp)](../../solutions/binary-search/O_Trinity.cpp) | binary-search | reviewed |
| [roots (python)](../../solutions/binary-search/roots.py) | binary-search | reviewed |
| [The Wave (cpp)](../../solutions/binary-search/The_Wave.cpp) | binary-search | reviewed |

<!-- examples:end -->
