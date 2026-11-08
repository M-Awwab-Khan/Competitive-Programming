# Monotonic stack for nearest smaller or greater elements

Keep a stack of indices whose values are monotone; before pushing `i`, pop every index that can never again be the answer for a later element. The top after popping is the nearest element to the left satisfying the comparison.

## Recognition clues

- "For each position, the nearest smaller/greater value to the left (or right)".
- Spans, visible buildings, next warmer day, how far a value extends as the minimum.
- Largest rectangle in a histogram, sum of subarray minimums (each element's range of dominance).
- A "jump to the previous greater element" pointer that queries then follow repeatedly.

## Invariant and variants

After processing `i`, the stack holds, bottom to top, the indices `j <= i` that are not dominated by any later index; their values are strictly increasing (for "nearest smaller").

```cpp
vector<int> st;                                  // indices
for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
    left[i] = st.empty() ? -1 : st.back();       // nearest strictly smaller to the left
    st.push_back(i);
}
```

| Want | Pop condition |
| --- | --- |
| Nearest strictly smaller | `a[top] >= a[i]` |
| Nearest smaller or equal | `a[top] > a[i]` |
| Nearest strictly greater | `a[top] <= a[i]` |
| Nearest greater or equal | `a[top] < a[i]` |
| Nearest to the right | scan from the right, or assign `right[top] = i` when popping |

Each index is pushed and popped at most once: `O(n)`. Stacking the previous-greater pointers into a [binary lifting](tree-dfs.md) table lets a query count chain links inside `[l, r]` in `O(log n)`.

For contribution sums, use strict on one side and non-strict on the other so equal values are counted exactly once.

## Common mistakes

- Pushing values instead of indices, then needing positions or distances.
- Picking the wrong strictness, which double-counts or skips ties.
- Printing 0-based indices when 1-based are required (or using 0 as "none" while 0 is a valid index).
- Fixed-size global tables (`N`, number of lifting levels) silently bounding the supported input.

## Related patterns

A [monotonic deque](monotonic-deque.md) adds removal from the front for sliding windows. [Stack matching](stack-matching.md) pops by pairing rather than value order. Dominance ranges feed the [contribution technique](contribution-technique.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [cses nearestsmallervalues (cpp)](../../solutions/data-structures/stacks-and-queues/cses-nearestsmallervalues.cpp) | data-structures/stacks-and-queues | reviewed |
| [test (cpp)](../../solutions/data-structures/stacks-and-queues/test.cpp) | data-structures/stacks-and-queues | reviewed |

<!-- examples:end -->
