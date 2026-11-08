# Kadane maximum subarray

Scan once, keeping the best sum of a subarray that ends at the current index; restart whenever the carried sum would only hurt.

## Recognition clues

- "Maximum (or minimum) sum of a contiguous segment", values can be negative.
- "Choose one segment to flip / modify; maximise the result": rewrite each element as its *gain* if included, then take the max-gain segment.
- "Best `later - earlier`" (largest drop, best buy-sell): a running max/min of the prefix plays the role of the carried state.
- Extending a segment is allowed only under a local condition between neighbours (alternating parity).

## Invariant and recurrence

`cur` is the maximum sum of a nonempty subarray ending at `i`; `best` is the maximum over all `cur` so far.

```cpp
ll cur = a[0], best = a[0];
for (int i = 1; i < n; ++i) {
    cur = max(a[i], cur + a[i]);   // extend or restart
    best = max(best, cur);
}
```

Initialising with `a[0]` (not `0`) forces a nonempty answer when every element is negative.

| Variant | Transformation | Repo illustration |
| --- | --- | --- |
| Plain max subarray | as above | `cses-maximumsubarraysum.cpp` |
| Best flip gain | `0 -> +1`, `1 -> -1`; answer `ones + best` | `A_Flipping_Game.cpp`, `Range_Operation.cpp` (gain `2i - a_i`) |
| Restart on a broken condition | extend only if parities differ | `C_Yarik_and_Array.cpp` |
| Complement of the min subarray | `total - minSubarray` (min Kadane) | `E_Max_Subarray_Sum.cpp` |
| Proper segment only | run on `a[0..n-2]` and `a[1..n-1]` | `B_Just_Eat_It.cpp` |
| Max of `a_j - a_i`, `i < j` | keep running `max` (or `min`) of earlier values | `amalgamated_artichokes.cpp`, `open-credit-system.cpp` |

Complexity: `O(n)` time, `O(1)` extra memory. Recover the segment by remembering where `cur` last restarted.

## Common mistakes

- Starting from `best = 0`, which silently allows an empty segment; that is wrong when the segment must be nonempty and all values are negative. `B_Just_Eat_It.cpp` starts from `0`; that is harmless there because an empty-segment value of `0 >= total` correctly answers NO whenever `total <= 0`.
- Copy-paste bugs in a second pass: `B_Just_Eat_It.cpp` writes `best2 = max(best, curr2)` instead of `max(best2, curr2)`, dropping earlier maxima of the second run.
- Forced edge cases in gain transforms: `A_Flipping_Game.cpp` must flip at least one element, so all-ones gives `n - 1`.
- Using `int` for sums of up to `2*10^5` values of size `10^9`.
- The complement trick `total - minSubarray` produces an empty "kept" part when the minimum subarray is the whole array; handle that case explicitly.

## Related patterns

Kadane is the simplest [linear DP](linear-dp.md); a subarray sum is a difference of [prefix sums](prefix-sums-and-difference-arrays.md), and "max `P[r] - min P[l]`" is the same scan in prefix form. When the segment length is bounded, use a [monotonic deque](monotonic-deque.md) over prefix sums. Target-sum subarrays belong to [prefix sums with a frequency map](prefix-sum-frequency-map.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Flipping Game (cpp)](../../solutions/dynamic-programming/kadane/A_Flipping_Game.cpp) | dynamic-programming/kadane | reviewed |
| [amalgamated artichokes (cpp)](../../solutions/arrays-and-counting/amalgamated_artichokes.cpp) | arrays-and-counting | reviewed |
| [B. Chaiwalay (cpp)](../../solutions/dynamic-programming/kadane/B_Chaiwalay.cpp) | dynamic-programming/kadane | reviewed |
| [B. Just Eat It! (cpp)](../../solutions/dynamic-programming/kadane/B_Just_Eat_It.cpp) | dynamic-programming/kadane | reviewed |
| [C Yarik and Array (cpp)](../../solutions/dynamic-programming/kadane/C_Yarik_and_Array.cpp) | dynamic-programming/kadane | reviewed |
| [cses maximumsubarraysum (cpp)](../../solutions/dynamic-programming/kadane/cses-maximumsubarraysum.cpp) | dynamic-programming/kadane | reviewed |
| [E Max Subarray Sum (cpp)](../../solutions/dynamic-programming/kadane/E_Max_Subarray_Sum.cpp) | dynamic-programming/kadane | reviewed |
| [open credit system (cpp)](../../solutions/arrays-and-counting/open-credit-system.cpp) | arrays-and-counting | reviewed |
| [Range Operation (cpp)](../../solutions/dynamic-programming/kadane/Range_Operation.cpp) | dynamic-programming/kadane | reviewed |

<!-- examples:end -->
