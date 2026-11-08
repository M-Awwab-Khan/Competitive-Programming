# Divide and conquer on recursive structure

Define the answer for size `n` in terms of answers for smaller pieces (halves, `n - 1`, or a recursively built level) and combine them. The pieces are either independent (true divide and conquer) or share a recursive definition that can be counted without materialising it.

## Recognition clues

- A structure defined recursively: "a level-`n` burger is `B + L(n-1) + P + L(n-1) + B`", Tower of Hanoi, fractal strings.
- A pile or interval that splits into `floor(n/2)` and `ceil(n/2)` until it fits a capacity.
- Output size or length grows like `2^n` while queries ask about a prefix or a count.
- Merge-sort-like counting (inversions) or "solve left, solve right, combine across the middle".

## Invariant and variants

Write the recurrence with its base case, then make sure each call shrinks the size:

```text
T(n)  = 1                         if n <= k
T(n)  = T(floor(n/2)) + T(ceil(n/2))   otherwise
```

Only `O(log n)` distinct sizes appear in that recurrence (at most two per depth), so memoising on `n` (map) makes it fast.

| Variant | Repo idea |
| --- | --- |
| Split into halves | `M_Truckloads.cpp`: bottom-up `dp[i]` over every size `<= n`; fine for moderate `n`, while a map memo touches only `O(log n)` sizes |
| Classic recursion with closed-form count | `tower_of_hanoi.cpp`: `2^n - 1` moves, then move `n-1`, the largest, `n-1` again |
| Recursive structure prefix count | `atcoder-christmas.cpp`: count `P` in the first `x` layers of a level-`n` burger |

For the burger-type structure, precompute `len[n] = 2 * len[n-1] + 3` and `patties[n] = 2 * patties[n-1] + 1`, then descend: if `x` covers the whole left sub-burger, add its full count and continue to the right half; otherwise recurse into it. This is `O(n)` per query instead of `O(2^n)` characters.

Typical complexity follows the master theorem: `T(n) = 2T(n/2) + O(n)` is `O(n log n)`; `T(n) = 2T(n/2) + O(1)` is `O(n)`.

## Common mistakes

- Materialising the full recursive string; `atcoder-christmas.cpp` builds a string of length about `2^(n+2)`, which only works for tiny `n`.
- Off-by-one in floor/ceil splits: `(n + 1) / 2` is the ceiling for non-negative `n`.
- Missing memoisation when the two halves share sizes, or a base case that never fires.
- Overflow of `2^n - 1` or lengths in `int` once `n > 30`.

## Related patterns

Memoised split recurrences overlap with [linear DP](linear-dp.md); range-split DPs are [interval DP](interval-dp.md). Recursive search with undo is [backtracking](backtracking-recursion.md), and halves combined by lookup is [meet in the middle](meet-in-the-middle.md). Segment trees in [range query structures](range-query-structures.md) are divide and conquer over indices. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [atcoder christmas (cpp)](../../solutions/recursion-and-divide-and-conquer/atcoder-christmas.cpp) | recursion-and-divide-and-conquer | reviewed |
| [M Truckloads (cpp)](../../solutions/dynamic-programming/general/M_Truckloads.cpp) | dynamic-programming/general | reviewed |
| [tower of hanoi (cpp)](../../solutions/recursion-and-divide-and-conquer/tower_of_hanoi.cpp) | recursion-and-divide-and-conquer | reviewed |

<!-- examples:end -->
