# Interval dynamic programming

Define a state over a contiguous interval and build it from smaller intervals. The interval endpoints summarize the remaining subproblem.

## Recognition clues

Look for merging adjacent groups, choosing the first/last operation inside a range, or taking values from the ends of a sequence. Ask what remains after one choice: if it is a smaller interval, endpoint states may be sufficient.

## Recurrences and order

For adjacent merging, `dp[l][r]` can represent the minimum cost to merge the entire interval:

```text
dp[l][l] = 0
dp[l][r] = min over l <= k < r:
    dp[l][k] + dp[k+1][r] + cost(l, r)
```

`N_Slimes.cpp` uses this form, with the interval sum as its merge cost. Prefix sums make `cost(l, r)` constant time. Enumerating lengths, left endpoints, and splits gives `O(n^3)` time and `O(n^2)` memory for this recurrence.

For a game taking values from either end, store the best score difference for the current player:

```text
dp[l][r] = max(a[l] - dp[l+1][r], a[r] - dp[l][r-1])
```

`L_Deque.cpp` and `cses-removalgame.cpp` use this idea. Two choices per interval give `O(n^2)` time and memory in the straightforward implementation. Both formulations require an order where smaller intervals are already available, or memoized recursion with correct base cases.

## Common mistakes

- Choosing a state that omits information needed by later decisions.
- Mixing inclusive and half-open bounds.
- Leaving unreachable minimization states at zero.
- Assuming every two-dimensional DP is an interval DP.
- Using an uncomputed sentinel value that is also a valid answer without handling that ambiguity.

## Related patterns

[Prefix aggregates](prefix-sum-frequency-map.md) can accelerate interval costs. A moving interval maintained by a [monotonic deque](monotonic-deque.md) uses different state and ordering assumptions. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [cses removalgame (cpp)](../../solutions/dynamic-programming/intervals/cses-removalgame.cpp) | dynamic-programming/intervals | suggested |
| [L - Deque (cpp)](../../solutions/dynamic-programming/intervals/L_Deque.cpp) | dynamic-programming/intervals | suggested |
| [N - Slimes (cpp)](../../solutions/dynamic-programming/intervals/N_Slimes.cpp) | dynamic-programming/intervals | suggested |

<!-- examples:end -->
