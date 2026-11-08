# Priority-queue greedy

When the best next choice depends on items that have arrived or been modified so far, keep the candidates in a heap and repeatedly take the extreme one in `O(log n)`.

## Recognition clues

- Items become available over time (by year, by arrival) and each step consumes the strongest/cheapest available one.
- "Repeatedly take the largest, split or modify it, put it back" (`k` operations on the current maximum).
- Resource reuse: the resource that frees up earliest is the one to reuse.
- A naive solution re-sorts after every step: replace the re-sort with a heap.

## Invariant and variants

The heap contains exactly the currently eligible candidates, keyed by the greedy criterion; each step pops the top, which an exchange argument shows is always safe to choose now.

```cpp
priority_queue<T> pq;                                // max-heap
priority_queue<T, vector<T>, greater<T>> mn;         // min-heap
for (event in time order) {
    push every candidate that becomes available;
    if (!pq.empty()) { auto best = pq.top(); pq.pop(); act(best); maybe push(modified best); }
}
```

| Variant | Key | Repo illustration |
| --- | --- | --- |
| Arrivals then pop the strongest | `(strength, year)` max-heap | `knigsoftheforest.cpp` |
| Reuse earliest-free resource | `(departure, room)` min-heap | `cses-roomallocation.cpp` |
| Split the largest until `k` parts | largest power of two; `multiset` used as a heap | `AG_Powers_Of_Two.cpp` |
| Take from the largest remaining capacity | max-heap of empty seats | `B_Airport.cpp` (re-sorts instead of using a heap) |

In `AG_Powers_Of_Two.cpp` the start is the set bits of `n`: the minimum number of powers is `popcount(n)`, the maximum is `n` (all ones), and each split increases the count by exactly one, so every `k` in `[popcount(n), n]` is reachable.

Complexity: `O((n + operations) log n)`; memory `O(n)`. A `multiset` gives both ends and arbitrary deletion at a higher constant.

## Common mistakes

- Re-sorting the whole array after each operation (`B_Airport.cpp` does `O(n m log m)`) instead of pop-and-push.
- Forgetting that `std::priority_queue` is a max-heap; use `greater<>` or negate keys for a min-heap.
- Tie-breaking on the second pair component unintentionally: `(strength, year)` breaks ties by the larger year.
- Popping from an empty heap; check `empty()` before `top()`.
- Off-by-one on reuse: decide whether a resource freed at time `t` can serve an arrival at time `t`.

## Related patterns

If all keys are known up front and never change, [sort-then-greedy](sort-then-greedy.md) is enough. Room allocation is the heap form of [interval scheduling](interval-scheduling-and-sweep.md). When erasing arbitrary elements or querying both ends, use [ordered-set queries](ordered-set-queries.md); for window extremes, a [monotonic deque](monotonic-deque.md). Shortest-path relaxations (Dijkstra) are the graph version, see [shortest paths](shortest-paths.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [AG - Powers Of Two (cpp)](../../solutions/bit-manipulation/AG_Powers_Of_Two.cpp) | bit-manipulation | reviewed |
| [B Airport (cpp)](../../solutions/greedy/B_Airport.cpp) | greedy | reviewed |
| [cses roomallocation (cpp)](../../solutions/greedy/cses-roomallocation.cpp) | greedy | reviewed |
| [knigsoftheforest (cpp)](../../solutions/data-structures/heaps/knigsoftheforest.cpp) | data-structures/heaps | reviewed |

<!-- examples:end -->
