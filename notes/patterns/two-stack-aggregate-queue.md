# Queue with an aggregate built from two stacks

Maintain an associative aggregate (gcd, min, max, and similar) over a FIFO window, even when the operation cannot be undone by subtraction.

## Recognition clues

A [two-pointer window](two-pointer-window.md) needs the gcd, minimum, or maximum of the current window, and removing the leftmost element must not require recomputing from scratch.

## Invariant

Keep an `in` stack for pushes and an `out` stack for pops. Each stack entry stores its value and the aggregate of itself and every entry below it in the same stack.

- `push(x)`: aggregate is `x` combined with `in.top().agg`.
- `pop()`: if `out` is empty, move every element from `in` to `out`, recomputing aggregates as they are pushed onto `out`; then pop `out`.
- `query()`: combine `in.top().agg` and `out.top().agg`, handling empty stacks.

The front of the queue is the top of `out`, so elements leave in insertion order. Every element is transferred at most once, so each operation is amortised `O(1)` plus the cost of the combining operation (`O(log V)` for gcd).

## Common mistakes

- Querying an empty queue: both stacks empty means no aggregate exists.
- Forgetting to recompute aggregates during transfer; copied `in` aggregates describe the wrong prefix.
- Requiring commutativity: the operation only needs to be associative if the combination order matches the queue order.

## Related patterns

For only `min`/`max`, a [monotonic deque](monotonic-deque.md) is an alternative. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B 7485 Unlimited Easy version (cpp)](../../solutions/two-pointers-and-sliding-window/B_7485_Unlimited_Easy_version.cpp) | two-pointers-and-sliding-window | reviewed |
| [Coprime Segment (cpp)](../../solutions/two-pointers-and-sliding-window/Coprime_Segment.cpp) | two-pointers-and-sliding-window | reviewed |
| [Segments with Small Spread (cpp)](../../solutions/two-pointers-and-sliding-window/Segments_with_Small_Spread.cpp) | two-pointers-and-sliding-window | reviewed |

<!-- examples:end -->
