# Prefix sums with a frequency map

Transform a subarray condition into a relationship between two prefix states, then count or locate matching earlier states.

## Recognition clues

For half-open prefixes `P[0] = 0` and `P[r] = a[0] + ... + a[r-1]`, a subarray sum is `P[r] - P[l]`. A target sum `k` therefore needs an earlier state `P[l] = P[r] - k`.

This remains useful with negative elements, where a window that shrinks when its sum becomes too large may not be valid. For divisibility by `m`, store normalized prefix remainders instead: equal remainders identify a divisible subarray.

## Invariant and variants

For counting subarrays with sum `k`:

```text
frequency[0] = 1
prefix = 0
for value in array:
    prefix += value
    answer += frequency[prefix - k]
    frequency[prefix] += 1
```

The map contains earlier prefixes when the answer is counted. Inserting the current prefix afterward prevents counting an empty subarray when `k = 0`.

For the longest matching subarray, store the first occurrence of each prefix, not its frequency. The standalone examples in this repo illustrate both variants. For counting equal-state pairs after building a frequency table, each group of size `c` contributes `c * (c - 1) / 2`.

Hash maps give expected `O(n)` time and `O(n)` space; ordered maps give `O(n log n)` time. Use a wide type for sums and counts. In C++, normalize a possibly negative remainder with `(x % m + m) % m` for positive `m`.

## Common mistakes

- Forgetting the empty prefix.
- Overwriting the earliest index in the longest-subarray variant.
- Counting with current rather than earlier prefixes.
- Assuming a positive-only sliding window remains valid with negatives.

## Related patterns

A bounded-length sum problem can combine prefix states with a [monotonic deque](monotonic-deque.md). Interval sums can also make [interval DP](interval-dp.md) transitions cheaper. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [good subarrays (cpp)](../../solutions/arrays-and-counting/good_subarrays.cpp) | arrays-and-counting | suggested |
| [longest subarray with sum k (cpp)](../../algorithms/prefix-sums/longest_subarray_with_sum_k.cpp) | prefix-sums | reviewed |
| [subarray divisibility (cpp)](../../solutions/prefix-sums/subarray-divisibility.cpp) | prefix-sums | suggested |
| [subarray sum equals k (cpp)](../../algorithms/prefix-sums/subarray_sum_equals_k.cpp) | prefix-sums | reviewed |

<!-- examples:end -->
