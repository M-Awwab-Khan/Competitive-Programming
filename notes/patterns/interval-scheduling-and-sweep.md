# Interval scheduling and event sweep

Turn intervals into sorted endpoints or sorted-by-end segments, then sweep once while maintaining a small state: the last chosen end, the running overlap count, or the furthest end seen so far.

## Recognition clues

- "Maximum number of non-overlapping meetings/movies/segments".
- "Maximum number of people present at once", "minimum rooms/servers/rooms needed".
- "Longest free gap", "total covered length", "union of intervals".
- Coverage of angles or a circle row, where each object blocks an interval.
- Assign intervals to `k` resources so as many as possible fit.

## Invariant and variants

**Earliest end first.** Sort by right endpoint; take a segment iff its start is after the last taken end. Invariant: after each step, the chosen set is maximum among processed segments and its last end is as small as possible (exchange argument).

**Event sweep.** Emit `(t, +1)` at start and `(t_end, -1)` at end, sort, accumulate; the maximum prefix is the maximum overlap. The tie order encodes open/closed endpoints: with `pair<int,int>`, `-1` sorts before `+1` at equal times, which models half-open `[l, r)`.

**Merge/gap.** Sort by start, keep `maxEnd`; a new start `> maxEnd` begins a new block and `start - maxEnd` is a free gap.

| Variant | State | Repo illustration |
| --- | --- | --- |
| Max non-overlapping | last chosen end | `movie_festival.cpp`, `maximum-nonoverlapping-segments.cpp` |
| Max overlap / servers | running `+1/-1` count; servers `ceil(max / k)` | `restaurant_customers.cpp`, `Disastrous_Downtime.cpp` |
| Rooms with assignment | min-heap of `(departure, room)` | `cses-roomallocation.cpp` |
| `k` resources, max intervals | multiset of free times, `prev(upper_bound(start))` | `cses-moviefestival2.cpp` |
| Longest gap / union length | `maxEnd` while sorted by start | `B_foodbreak.cpp`, `D_Counting_Points.cpp` |
| Angular intervals | split at wraparound, merge, largest gap | `coverdrive.py`, `coverdrive2.py` |
| Greedy left-to-right placement | last occupied coordinate | `C_Woodcutters.cpp`, `B_Vaccination.cpp` |
| Spans by last occurrence | extend block end to `last[a[i]]` | `G_1_Into_Blocks_easy_version.cpp` |
| Plane sweep with active set | points within `d` of the sweep line | `Closest_Pair.cpp` |

Complexity: `O(n log n)` for sorting; the sweep is `O(n)` or `O(n log n)` with a heap/multiset.

## Common mistakes

- Sorting by start (or by length) for the max-non-overlapping problem; only earliest end is optimal.
- Wrong tie order at equal coordinates: decide whether touching intervals overlap and encode it in the event order or by using `r + 1` as the end.
- In room assignment, compare the heap top with `>=` vs `>` consistently with whether a room freed at time `t` can be reused at `t` (`cses-roomallocation.cpp` requires departure strictly before arrival).
- `ceil(x / (double)k)` works but integer `(x + k - 1) / k` avoids floating point.
- Integer-lattice coverage via `sqrt` on doubles (`D_Counting_Points.cpp`) can be off by one for large radii; correct `dx` with a while loop.
- Angular intervals that cross `0/360` must be split before merging.

## Related patterns

Interval sweeps are a specialised [sort-then-greedy](sort-then-greedy.md). Offline coverage counts can instead use [difference arrays](prefix-sums-and-difference-arrays.md). Assignment to resources uses a [priority queue](priority-queue-greedy.md) or [ordered set](ordered-set-queries.md), and geometric sweeps rely on [geometry predicates](geometry-predicates.md). Weighted interval selection is a [linear DP](linear-dp.md) with [sorted lookup](sorted-lookup.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B Vaccination (cpp)](../../solutions/greedy/B_Vaccination.cpp) | greedy | reviewed |
| [B. foodbreak (cpp)](../../solutions/intervals/B_foodbreak.cpp) | intervals | reviewed |
| [C - Chokutter Addiction (cpp)](../../solutions/simulation/C_Chokutter_Addiction.cpp) | simulation | reviewed |
| [C Woodcutters (cpp)](../../solutions/greedy/C_Woodcutters.cpp) | greedy | reviewed |
| [Closest Pair (cpp)](../../solutions/geometry/Closest_Pair.cpp) | geometry | reviewed |
| [Closest Pair Uniform (cpp)](../../solutions/geometry/Closest_Pair_Uniform.cpp) | geometry | reviewed |
| [coverdrive (python)](../../solutions/geometry/coverdrive.py) | geometry | reviewed |
| [coverdrive2 (python)](../../solutions/geometry/coverdrive2.py) | geometry | reviewed |
| [cses moviefestival2 (cpp)](../../solutions/greedy/cses-moviefestival2.cpp) | greedy | reviewed |
| [cses roomallocation (cpp)](../../solutions/greedy/cses-roomallocation.cpp) | greedy | reviewed |
| [D Counting Points (cpp)](../../solutions/intervals/D_Counting_Points.cpp) | intervals | reviewed |
| [Disastrous Downtime (cpp)](../../solutions/intervals/Disastrous_Downtime.cpp) | intervals | reviewed |
| [E Burns Road (cpp)](../../solutions/sorting-and-searching/E_Burns_Road.cpp) | sorting-and-searching | reviewed |
| [G1. Into Blocks (easy version) (cpp)](../../solutions/greedy/G_1_Into_Blocks_easy_version.cpp) | greedy | reviewed |
| [maximum nonoverlapping segments (cpp)](../../solutions/greedy/maximum-nonoverlapping-segments.cpp) | greedy | reviewed |
| [movie festival (cpp)](../../solutions/greedy/movie_festival.cpp) | greedy | reviewed |
| [restaurant customers (cpp)](../../solutions/intervals/restaurant_customers.cpp) | intervals | reviewed |

<!-- examples:end -->
