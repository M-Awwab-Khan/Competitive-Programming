# Ordered-set queries

Keep a dynamic sorted collection (`set`, `multiset`, `map`, or a PBDS order-statistics tree) so that insert, erase, nearest-neighbour, min/max and k-th queries all cost `O(log n)` while the collection changes.

## Recognition clues

- "Each customer takes the best remaining item `<= x`" or "the cheapest remaining item `>= k`": matching with removal.
- A sliding window that needs the median, the k-th element, `max - min`, or the mex.
- Inserting cut points and reporting the largest gap after each insertion.
- Ranking or counting "elements greater than me seen so far" (inversions, leaderboard rank) online.
- Josephus-style removal by position from a shrinking circle.

## Invariant and variants

The container always holds exactly the currently available elements, sorted. Every query is a bound plus optional erase:

```cpp
auto it = ms.upper_bound(x);          // largest <= x
if (it == ms.begin()) none();
else { --it; use(*it); ms.erase(it); } // erase ONE copy via iterator
```

| Need | Tool | Repo illustration |
| --- | --- | --- |
| Best remaining `<= x`, then remove | `multiset`, `prev(upper_bound)` | `concert_tickets.cpp`, `cses-moviefestival2.cpp` |
| Smallest remaining `>= x` / `> x` | `multiset::lower_bound` / `upper_bound` | `G_Souvenirs.cpp`, `B_George_and_Round.cpp`, `cses-towers.cpp` |
| Neighbours of a new point + gap multiset | `set` of cuts, `multiset` of gaps, `rbegin` | `cses-trafficlights.cpp` |
| Window `max - min` | `map<value, count>`, erase key at count 0 | `B_Approximating_a_Constant_Range.cpp` |
| Window mex | `set` of missing values, `*begin()` | `C_Mex_Min.cpp` |
| Window median / cost | two multisets with balanced sizes and sums | `B_Sliding_Window_Cost.cpp` |
| k-th / rank | PBDS `find_by_order`, `order_of_key` | `cses-slidingwindowmedian.cpp`, `cses-josephus2.cpp`, `B_Baby_Baraa_in_ALBAIK.cpp`, `qoj4071.cpp` |
| Sweep with active set keyed by `y` | `multimap` / `set` | `Closest_Pair.cpp` |

Two-multiset median: keep `low` (max part) and `high` (min part) with `|low| = |high|` or `|high| + 1`; the median is `*low.rbegin()`. With running sums, the cost to move every element to median `m` is `m*|low| - sumLow + sumHigh - m*|high|`.

PBDS only supports set semantics; store `(value, index)` pairs to allow duplicates.

Complexity: `O(log n)` per operation with a noticeably larger constant than arrays; memory `O(n)`.

## Common mistakes

- `ms.erase(value)` removes **all** copies; erase via an iterator (`ms.erase(ms.find(v))`).
- Erasing by key in a `multimap` (`Closest_Pair.cpp` erases `active.find(y)`) may remove a different point with the same key; store a unique tie-breaker.
- Decrementing `begin()` after `upper_bound`.
- Calling `std::lower_bound(ms.begin(), ms.end(), x)` on a set is linear; use the member function.
- Rebuilding sets per query (`A_The_Rizzler.cpp` recomputes `set_difference` over the remaining set) loses the logarithmic bound.
- Precomputing keys with `pow` doubles beyond 64-bit range (`uva-smallfactors.cpp`) is undefined when converted to `ll`; generate with integer multiplication and overflow checks.

## Related patterns

For a static array, plain [sorted lookup](sorted-lookup.md) is simpler and faster. If only the minimum or maximum is ever needed, a [priority queue](priority-queue-greedy.md) or [monotonic deque](monotonic-deque.md) suffices. Matching with removal is usually the inner step of a [sort-then-greedy](sort-then-greedy.md) or [interval-scheduling](interval-scheduling-and-sweep.md) solution, and inversion counting can also use [range-query structures](range-query-structures.md). Window variants pair with [two-pointer windows](two-pointer-window.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A The Rizzler (cpp)](../../solutions/data-structures/ordered-sets/A_The_Rizzler.cpp) | data-structures/ordered-sets | reviewed |
| [B - Sliding Window Cost (cpp)](../../solutions/data-structures/ordered-sets/B_Sliding_Window_Cost.cpp) | data-structures/ordered-sets | reviewed |
| [B Approximating a Constant Range (cpp)](../../solutions/two-pointers-and-sliding-window/B_Approximating_a_Constant_Range.cpp) | two-pointers-and-sliding-window | reviewed |
| [B George and Round (cpp)](../../solutions/greedy/B_George_and_Round.cpp) | greedy | reviewed |
| [B M Arrays (cpp)](../../solutions/greedy/B_M_Arrays__0a29afd8.cpp) | greedy | reviewed |
| [B. Baby Baraa in ALBAIK (cpp)](../../solutions/data-structures/ordered-sets/B_Baby_Baraa_in_ALBAIK.cpp) | data-structures/ordered-sets | reviewed |
| [C - Mex Min (cpp)](../../solutions/two-pointers-and-sliding-window/C_Mex_Min.cpp) | two-pointers-and-sliding-window | reviewed |
| [C Rearrange (cpp)](../../solutions/greedy/C_Rearrange.cpp) | greedy | reviewed |
| [C. Dora and Search (cpp)](../../solutions/two-pointers-and-sliding-window/C_Dora_and_Search.cpp) | two-pointers-and-sliding-window | reviewed |
| [Closest Pair (cpp)](../../solutions/geometry/Closest_Pair.cpp) | geometry | reviewed |
| [Closest Pair Uniform (cpp)](../../solutions/geometry/Closest_Pair_Uniform.cpp) | geometry | reviewed |
| [concert tickets (cpp)](../../solutions/data-structures/ordered-sets/concert_tickets.cpp) | data-structures/ordered-sets | reviewed |
| [cses josephus2 (cpp)](../../solutions/data-structures/ordered-sets/cses-josephus2.cpp) | data-structures/ordered-sets | reviewed |
| [cses moviefestival2 (cpp)](../../solutions/greedy/cses-moviefestival2.cpp) | greedy | reviewed |
| [cses slidingwindowmedian (cpp)](../../solutions/data-structures/ordered-sets/cses-slidingwindowmedian.cpp) | data-structures/ordered-sets | reviewed |
| [cses towers (cpp)](../../solutions/data-structures/ordered-sets/cses-towers.cpp) | data-structures/ordered-sets | reviewed |
| [cses trafficlights (cpp)](../../solutions/data-structures/ordered-sets/cses-trafficlights.cpp) | data-structures/ordered-sets | reviewed |
| [D Matryoshkas (cpp)](../../solutions/greedy/D_Matryoshkas.cpp) | greedy | reviewed |
| [D. Distinct Characters Queries (cpp)](../../solutions/data-structures/ordered-sets/D_Distinct_Characters_Queries.cpp) | data-structures/ordered-sets | reviewed |
| [E - Sparse Range (cpp)](../../solutions/two-pointers-and-sliding-window/E_Sparse_Range.cpp) | two-pointers-and-sliding-window | reviewed |
| [G - Souvenirs (cpp)](../../solutions/greedy/G_Souvenirs.cpp) | greedy | reviewed |
| [qoj4071 (cpp)](../../solutions/data-structures/ordered-sets/qoj4071.cpp) | data-structures/ordered-sets | reviewed |
| [uva jollo (cpp)](../../solutions/greedy/uva-jollo.cpp) | greedy | reviewed |
| [uva smallfactors (cpp)](../../solutions/binary-search/uva-smallfactors.cpp) | binary-search | reviewed |

<!-- examples:end -->
