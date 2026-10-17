# Monotonic deque

Keep only candidates that can still become the minimum or maximum of a moving window. Each index enters once and leaves at most once.

## Recognition clues

Use this when boundaries advance monotonically and each step needs an extremum over the active window. A maximum window stores candidate indices in decreasing value order; a minimum window stores them in increasing value order.

The standalone `sliding_window_max.cpp` contains both maximum and minimum variants. `D_Good_Sets.cpp` uses one deque for each extremum while moving the left boundary until `max - min <= k`.

## Invariant

For each new right endpoint:

1. Remove expired indices from the front.
2. Remove dominated candidates from the back.
3. Append the new index.
4. Read the best candidate from the front when the window is valid.

A newer index with at least as good a value dominates an older one for future windows, because it expires later. Whether equal values are retained or discarded depends on how expiry and duplicate values are represented; storing indices makes both choices manageable.

With one insertion and at most one removal per index, the total time is `O(n)`. Space is `O(w)` for a fixed window of width `w`, and at most `O(n)` for a variable window.

## Common mistakes

- Storing only values and losing track of which duplicate expired.
- Reading the front after all candidates have been removed.
- Expiring against the wrong inclusive/exclusive boundary.
- Applying domination when a later candidate cannot replace an earlier one for the queries that remain.

For bounded-length maximum subarray sums, use a deque of prefix minima over the allowed starting indices. The historical `maximum_subarray_sum_ii.py` attempts this combination; its presence is not a correctness guarantee.

## Related patterns

See [prefix sums with a frequency map](prefix-sum-frequency-map.md) for alternative ways to retain earlier prefix states, and the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [D. Good Sets (cpp)](../../solutions/two-pointers-and-sliding-window/D_Good_Sets.cpp) | two-pointers-and-sliding-window | reviewed |
| [maximum subarray sum ii (python)](../../solutions/two-pointers-and-sliding-window/maximum_subarray_sum_ii.py) | two-pointers-and-sliding-window | reviewed |
| [sliding window max (cpp)](../../algorithms/two-pointers-and-sliding-window/sliding_window_max.cpp) | two-pointers-and-sliding-window | suggested |

<!-- examples:end -->
