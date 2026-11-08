# Pair counting with inclusion-exclusion

## Recognition clues

Each item has two attributes, and two items are compatible only when both attributes differ. Count partners from attribute frequencies instead of enumerating all pairs.

## Invariant and formula

For `k` distinct items `(u, v)`, let `left[u]` and `right[v]` count occurrences of each attribute. For an item `(u, v)`, the number of compatible partners is:

```text
k - left[u] - right[v] + 1
```

The forbidden sets contain items sharing either endpoint. When each ordered endpoint pair occurs at most once, their intersection contains only the current item. Add it back once after subtracting both sets. Summing over all items counts each unordered compatible pair twice, so divide by two.

If identical endpoint pairs can repeat, replace `+1` with the frequency of `(u, v)`. The intersection then contains every copy, not just the current item.

With array frequency tables sized to endpoint domains `a` and `b`, time is `O(a + b + k)` including initialization, and space is `O(a + b + k)` when storing all items. Hash maps can give expected `O(k)` time and space for sparse domains.

## Common mistakes

- Using `+1` when duplicate endpoint pairs are allowed.
- Forgetting to divide the summed partner count by two.
- Using a narrow type for an answer that can grow quadratically in `k`.
- Treating paired endpoint arrays as unrelated sets and losing each item's association.

## Related patterns

[Prefix sums with a frequency map](prefix-sum-frequency-map.md) also count pairs through frequencies, after transforming subarrays into prefix states. [Binomial counting](binomial-counting.md) counts selections by partitioning them into disjoint cases.

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [1 (python)](../../solutions/sorting-and-searching/1.py) | sorting-and-searching | reviewed |
| [C Two Colors (cpp)](../../solutions/sorting-and-searching/C_Two_Colors.cpp) | sorting-and-searching | reviewed |
| [C. White Sheet (cpp)](../../solutions/geometry/C_White_Sheet.cpp) | geometry | reviewed |
| [cf ballinberland (cpp)](../../solutions/arrays-and-counting/cf-ballinberland.cpp) | arrays-and-counting | reviewed |
| [E Again Divisors (cpp)](../../solutions/math/number-theory/E_Again_Divisors.cpp) | math/number-theory | reviewed |
| [E FizzBuzz Sum Hard (cpp)](../../solutions/math/number-theory/E_FizzBuzz_Sum_Hard.cpp) | math/number-theory | reviewed |
| [H - Hits Different (cpp)](../../solutions/dynamic-programming/general/H_Hits_Different.cpp) | dynamic-programming/general | reviewed |
| [H - Number of Pairs (cpp)](../../solutions/binary-search/H_Number_of_Pairs.cpp) | binary-search | reviewed |
| [two knights (cpp)](../../solutions/math/combinatorics/two-knights.cpp) | math/combinatorics | reviewed |
| [yuki countmultiples (cpp)](../../solutions/math/combinatorics/yuki-countmultiples.cpp) | math/combinatorics | reviewed |

<!-- examples:end -->
