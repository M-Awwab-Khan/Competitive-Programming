# Two-pointer window over a monotone condition

Move a right endpoint forward and advance the left endpoint only as far as needed. Both pointers move at most `n` times, so the scan is linear apart from the cost of maintaining window state.

## Recognition clues

The technique applies when validity is monotone in the window:

- **Shrink-safe ("small" conditions):** if `[l, r]` is good, every subsegment is good. Examples: sum `<= s` with non-negative elements, at most `k` distinct values, `max - min <= k`, per-letter counts bounded by an available multiset.
- **Grow-safe ("big" conditions):** if `[l, r]` is good, every supersegment is good. Examples: sum `>= s` with non-negative elements, gcd equal to 1.

Then the best left endpoint for each right endpoint is non-decreasing, which is what lets `l` move only forward.

## Invariant and variants

For a shrink-safe condition, after processing `r`, `l` is the smallest index such that `[l, r]` is good:

```text
l = 0
for r in 0..n-1:
    add(a[r])
    while window [l, r] is bad:
        remove(a[l]); l += 1
    use [l, r]
```

| Question | Update after the inner loop |
| --- | --- |
| Longest good segment | `ans = max(ans, r - l + 1)` |
| Number of good segments | `ans += r - l + 1` (every left endpoint in `[l, r]`) |
| Total length of good segments | `ans += len * (len + 1) / 2` with `len = r - l + 1` |
| Best value of a good segment (non-negative values) | `ans = max(ans, windowValue)` |

For a grow-safe condition, shrink *while the window is still good*, recording the shortest length before each removal. To count good segments, fix `l`, extend `r` until the window first becomes good, and add `n - r + 1` where `r` is one past the last included element.

The same pointer motion also merges sorted arrays: for each query in sorted order, advance a pointer in the other sorted array while its value is smaller. With several sorted lists, repeatedly advance the pointer holding the current minimum to minimise `max - min` over one element from each list.

Pairwise counts of a quadratic quantity, such as `"ab"` subsequences in a window, can still be maintained: adding `b` contributes the current number of `a`s; removing a leading `a` removes the current number of `b`s.

A cyclic array can be handled by doubling it and limiting answers to length at most `n`; reduce large targets first by whole cycles.

Time is `O(n)` times the cost of `add`/`remove`/validity checks. Sums and counts usually need 64-bit integers: the number of segments is up to `n(n + 1) / 2`.

## Common mistakes

- Using the technique when negative values break monotonicity; use [prefix sums with a frequency map](prefix-sum-frequency-map.md) instead.
- Reading `a[r]` after `r` reached `n` in the "fix `l`, extend `r`" form.
- Off-by-one between "`r` is the last included index" and "`r` is one past it".
- Storing segment counts in `int`.
- A validity test that needs a non-invertible aggregate (gcd, min, max) cannot be undone by subtraction; use a [two-stack aggregate queue](two-stack-aggregate-queue.md), a [monotonic deque](monotonic-deque.md), or a multiset.

## Related patterns

[Binary search on the answer](binary-search-on-answer.md) solves many of the same questions in `O(n log n)` when the condition is monotone in length. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A - A (cpp)](../../solutions/two-pointers-and-sliding-window/A_A.cpp) | two-pointers-and-sliding-window | reviewed |
| [A Puzzles (cpp)](../../solutions/sorting-and-searching/A_Puzzles.cpp) | sorting-and-searching | reviewed |
| [apartments (python)](../../solutions/greedy/apartments.py) | greedy | reviewed |
| [atcoder enougharray (cpp)](../../solutions/two-pointers-and-sliding-window/atcoder-enougharray.cpp) | two-pointers-and-sliding-window | reviewed |
| [B 7485 Unlimited Easy version (cpp)](../../solutions/two-pointers-and-sliding-window/B_7485_Unlimited_Easy_version.cpp) | two-pointers-and-sliding-window | reviewed |
| [B Approximating a Constant Range (cpp)](../../solutions/two-pointers-and-sliding-window/B_Approximating_a_Constant_Range.cpp) | two-pointers-and-sliding-window | reviewed |
| [B Equalize (cpp)](../../solutions/two-pointers-and-sliding-window/B_Equalize.cpp) | two-pointers-and-sliding-window | reviewed |
| [B Kefa and Company (cpp)](../../solutions/two-pointers-and-sliding-window/B_Kefa_and_Company.cpp) | two-pointers-and-sliding-window | reviewed |
| [balanced team (python)](../../solutions/two-pointers-and-sliding-window/balanced_team.py) | two-pointers-and-sliding-window | reviewed |
| [Black and White Stripe (cpp)](../../solutions/two-pointers-and-sliding-window/Black_and_White_Stripe.cpp) | two-pointers-and-sliding-window | reviewed |
| [black and white stripe (python)](../../solutions/two-pointers-and-sliding-window/black_and_white_stripe.py) | two-pointers-and-sliding-window | reviewed |
| [C - Mex Min (cpp)](../../solutions/two-pointers-and-sliding-window/C_Mex_Min.cpp) | two-pointers-and-sliding-window | reviewed |
| [C Ancient History Easy (cpp)](../../solutions/two-pointers-and-sliding-window/C_Ancient_History_Easy.cpp) | two-pointers-and-sliding-window | reviewed |
| [C Grandma Capa Knits A Scarf (cpp)](../../solutions/two-pointers-and-sliding-window/C_Grandma_Capa_Knits_A_Scarf.cpp) | two-pointers-and-sliding-window | reviewed |
| [C They Are Everywhere (cpp)](../../solutions/two-pointers-and-sliding-window/C_They_Are_Everywhere.cpp) | two-pointers-and-sliding-window | reviewed |
| [C Vasya and String (cpp)](../../solutions/two-pointers-and-sliding-window/C_Vasya_and_String.cpp) | two-pointers-and-sliding-window | reviewed |
| [C. Sum of Cubes (cpp)](../../solutions/two-pointers-and-sliding-window/C_Sum_of_Cubes.cpp) | two-pointers-and-sliding-window | reviewed |
| [Card Substrings (cpp)](../../solutions/two-pointers-and-sliding-window/Card_Substrings.cpp) | two-pointers-and-sliding-window | reviewed |
| [cf books (cpp)](../../solutions/binary-search/cf-books.cpp) | binary-search | reviewed |
| [cf eatingcandies (cpp)](../../solutions/two-pointers-and-sliding-window/cf-eatingcandies.cpp) | two-pointers-and-sliding-window | reviewed |
| [Che city (cpp)](../../solutions/two-pointers-and-sliding-window/Che_city.cpp) | two-pointers-and-sliding-window | reviewed |
| [clock (cpp)](../../solutions/sorting-and-searching/clock.cpp) | sorting-and-searching | reviewed |
| [Coprime Segment (cpp)](../../solutions/two-pointers-and-sliding-window/Coprime_Segment.cpp) | two-pointers-and-sliding-window | reviewed |
| [cses playlist (cpp)](../../solutions/two-pointers-and-sliding-window/cses-playlist.cpp) | two-pointers-and-sliding-window | reviewed |
| [cses sumofthreevalues (cpp)](../../solutions/two-pointers-and-sliding-window/cses-sumofthreevalues.cpp) | two-pointers-and-sliding-window | reviewed |
| [D - Subarray Distinct Values (cpp)](../../solutions/two-pointers-and-sliding-window/D_Subarray_Distinct_Values.cpp) | two-pointers-and-sliding-window | reviewed |
| [E - Sparse Range (cpp)](../../solutions/two-pointers-and-sliding-window/E_Sparse_Range.cpp) | two-pointers-and-sliding-window | reviewed |
| [E. Binary Deque (cpp)](../../solutions/two-pointers-and-sliding-window/E_Binary_Deque.cpp) | two-pointers-and-sliding-window | reviewed |
| [F Playing with OR (cpp)](../../solutions/two-pointers-and-sliding-window/F_Playing_with_OR.cpp) | two-pointers-and-sliding-window | reviewed |
| [F Playing with OR (python)](../../solutions/two-pointers-and-sliding-window/F_Playing_with_OR.py) | two-pointers-and-sliding-window | reviewed |
| [F. Money Trees (cpp)](../../solutions/two-pointers-and-sliding-window/F_Money_Trees.cpp) | two-pointers-and-sliding-window | reviewed |
| [ferris wheel (cpp)](../../solutions/greedy/ferris_wheel.cpp) | greedy | reviewed |
| [friends and the restaurant (python)](../../solutions/greedy/friends_and_the_restaurant.py) | greedy | reviewed |
| [G - Three Parts of the Array (cpp)](../../solutions/two-pointers-and-sliding-window/G_Three_Parts_of_the_Array.cpp) | two-pointers-and-sliding-window | reviewed |
| [H. Product of Four Elements (cpp)](../../solutions/two-pointers-and-sliding-window/H_Product_of_Four_Elements.cpp) | two-pointers-and-sliding-window | reviewed |
| [k distinct subarrays (python)](../../solutions/two-pointers-and-sliding-window/k_distinct_subarrays.py) | two-pointers-and-sliding-window | reviewed |
| [kattis closestsum (cpp)](../../solutions/two-pointers-and-sliding-window/kattis-closestsum.cpp) | two-pointers-and-sliding-window | reviewed |
| [Knapsack on a Segment (cpp)](../../solutions/two-pointers-and-sliding-window/Knapsack_on_a_Segment.cpp) | two-pointers-and-sliding-window | reviewed |
| [Looped Playlist (cpp)](../../solutions/two-pointers-and-sliding-window/Looped_Playlist.cpp) | two-pointers-and-sliding-window | reviewed |
| [maximum sum subarray size K (cpp)](../../algorithms/two-pointers-and-sliding-window/maximum_sum_subarray_size_K.cpp) | two-pointers-and-sliding-window | reviewed |
| [Not Very Rude Substring (cpp)](../../solutions/two-pointers-and-sliding-window/Not_Very_Rude_Substring.cpp) | two-pointers-and-sliding-window | reviewed |
| [Number of Segments with Big Sum (cpp)](../../solutions/two-pointers-and-sliding-window/Number_of_Segments_with_Big_Sum.cpp) | two-pointers-and-sliding-window | reviewed |
| [Number of Segments with Small Sum (cpp)](../../solutions/two-pointers-and-sliding-window/Number_of_Segments_with_Small_Sum.cpp) | two-pointers-and-sliding-window | reviewed |
| [Number of Smaller (cpp)](../../solutions/two-pointers-and-sliding-window/Number_of_Smaller.cpp) | two-pointers-and-sliding-window | reviewed |
| [paint numbers (python)](../../solutions/greedy/paint_numbers.py) | greedy | reviewed |
| [Segment with Big Sum (cpp)](../../solutions/two-pointers-and-sliding-window/Segment_with_Big_Sum.cpp) | two-pointers-and-sliding-window | reviewed |
| [Segment with Small Sum (cpp)](../../solutions/two-pointers-and-sliding-window/Segment_with_Small_Sum.cpp) | two-pointers-and-sliding-window | reviewed |
| [Segments with Small Set (cpp)](../../solutions/two-pointers-and-sliding-window/Segments_with_Small_Set.cpp) | two-pointers-and-sliding-window | reviewed |
| [Segments with Small Spread (cpp)](../../solutions/two-pointers-and-sliding-window/Segments_with_Small_Spread.cpp) | two-pointers-and-sliding-window | reviewed |
| [smallest subarray (cpp)](../../solutions/two-pointers-and-sliding-window/smallest_subarray.cpp) | two-pointers-and-sliding-window | reviewed |
| [Stylish clothes (cpp)](../../solutions/two-pointers-and-sliding-window/Stylish_clothes.cpp) | two-pointers-and-sliding-window | reviewed |
| [subsequence (python)](../../solutions/two-pointers-and-sliding-window/subsequence.py) | two-pointers-and-sliding-window | reviewed |
| [Total Length (cpp)](../../solutions/two-pointers-and-sliding-window/Total_Length.cpp) | two-pointers-and-sliding-window | reviewed |
| [USACO Diamond Collector (cpp)](../../solutions/two-pointers-and-sliding-window/USACO_Diamond_Collector.cpp) | two-pointers-and-sliding-window | reviewed |
| [USACO Diamond Collector Silver (cpp)](../../solutions/two-pointers-and-sliding-window/USACO_Diamond_Collector_Silver.cpp) | two-pointers-and-sliding-window | reviewed |
| [utpc merging sorted list (cpp)](../../solutions/two-pointers-and-sliding-window/utpc-merging-sorted-list.cpp) | two-pointers-and-sliding-window | reviewed |
| [uva smallest subarray (python)](../../solutions/two-pointers-and-sliding-window/uva-smallest-subarray.py) | two-pointers-and-sliding-window | reviewed |
| [Why did the Cow Cross the Road 2 (cpp)](../../solutions/two-pointers-and-sliding-window/Why_did_the_Cow_Cross_the_Road_2.cpp) | two-pointers-and-sliding-window | reviewed |

<!-- examples:end -->
