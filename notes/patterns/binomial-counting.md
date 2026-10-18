# Counting selections with binomial coefficients

## Recognition clues

Positions are distinct, selection order is fixed or irrelevant, and validity depends on how many selected elements belong to each group. Partition valid selections by that count.

## Formula and precomputation

For a binary sequence with `ones` ones and `zeros` zeros, the number of length-`k` subsequences containing exactly `i` ones is:

```text
C(ones, i) * C(zeros, k - i)
```

Choosing positions uniquely determines their subsequence order. Cases for different `i` are disjoint. For odd `k`, the median is one precisely when `i >= (k + 1) / 2`; sum the product over feasible values of `i`. With even `k`, the median convention must be specified before choosing a threshold.

For a prime modulus `p` and maximum factorial index `M < p`:

```text
fact[i] = i! mod p
invFact[M] = fact[M]^(p - 2) mod p
invFact[i] = invFact[i + 1] * (i + 1) mod p
C(n, r) = fact[n] * invFact[r] * invFact[n - r] mod p
```

Return zero for `r < 0` or `r > n`. Precomputation costs `O(M + log p)` time and `O(M)` space; each combination query is `O(1)`. The counting loop is `O(k)`. The local implementation reads frequencies through an ordered map in `O(n log d)` time for `d` distinct values (`d <= 2` for binary input).

## Common mistakes and bounds

- Multiplying independent choices without first ensuring the cases are disjoint.
- Using the odd-length threshold with an unspecified even-length median.
- Indexing factorials past their precomputed limit. The local example sets `M = 200001`.
- Applying Fermat inversion to a composite modulus or to a factorial equal to zero modulo the prime.
- Overflowing products before reduction. Reduce between multiplications and use a sufficiently wide type.
- Accumulating too many modular terms without reduction. The local example reduces its sum only at the end; its bounded loop and modulus fit `long long`, but the approach needs reconsideration for larger bounds.

## Related patterns

[Pair counting with inclusion-exclusion](pair-counting-inclusion-exclusion.md) subtracts overlapping forbidden choices. The [contest math reference](../contest-prep/div3-speed-programming.md) provides additional formulas and reusable snippets.

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [cf expectedmedian (cpp)](../../solutions/math/combinatorics/cf-expectedmedian.cpp) | math/combinatorics | reviewed |

<!-- examples:end -->
