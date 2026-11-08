# Contribution technique

Instead of iterating over all pairs, subarrays, or subsets and summing a quantity, swap the order of summation: for each element, count how many of those structures it belongs to and multiply by its value.

## Recognition clues

- "Sum over all subarrays/pairs/segments of ..." with `n` up to `2e5`: the number of structures is quadratic, but the answer fits a linear pass.
- "Sum of all pairwise absolute differences".
- "Sum of `f(i)` for `i = 1..n`" where `f` is a divisor sum: count how often each divisor appears.
- Choosing an arrangement to maximise or minimise a weighted sum: compute each position's weight, then pair weights by the rearrangement inequality.
- "Count distinct results of erasing...": each new character contributes a fixed number of distinct strings.

## Invariant and variants

`sum over structures S of sum over x in S of value(x) = sum over x of value(x) * (#structures containing x)`.

| Quantity | Weight of element `i` (0-indexed, length `n`) | Repo illustration |
| --- | --- | --- |
| Sum of all subarray sums | `(i + 1) * (n - i)` subarrays contain `i` | `H_Permutator.cpp`, `E_Sum_of_Subarrays.cpp` |
| Sum of pairwise `|a_i - a_j|` | after sorting: `a[i] * i - a[i] * (n - 1 - i)` | `B_Playing_in_a_Casino.cpp`, `playing_in_a_casino.py` |
| Segments covering a point | point `i`: `(i + 1)(n - i) - 1`; integers strictly between points `i-1` and `i`: `i * (n - i)` | `X_All_Pairs_Segments.cpp` |
| Sum of divisor sums `sum sigma(k)` | divisor `d` appears `floor(n / d)` times | `cses-sumofdivisors.cpp` |
| Distinct strings left after repeatedly erasing the first or second letter | each first occurrence at `i` adds `n - i` | `B_Erase_First_or_Second_Letter.cpp` |

When a product `sum weight[i] * b[pi(i)]` must be optimised, sort weights descending and `b` ascending (minimise) or both the same way (maximise), as in `H_Permutator.cpp`.

For `sum_{d=1..n} d * floor(n / d)` with `n` up to `1e12`, group `d` by equal `q = n / d`: the block is `d..n / q`, contributing `q * (sum of d over the block)`. That is `O(sqrt n)` blocks.

Columns or coordinates are often independent (`B_Playing_in_a_Casino.cpp` sorts each column separately).

A linear contribution pass is `O(n)` after an `O(n log n)` sort if order matters.

## Common mistakes

- Off-by-one in `(i + 1) * (n - i)` when switching between 0- and 1-based indexing.
- Weight products overflowing `int`: `a[i] * (i + 1) * (n - i)` reaches about `1e9 * 1e10`; cast before multiplying and consider `__int128` or a modulus.
- Recomputing contributions per query in `O(n)` when prefix sums of `a[k] * k` and `a[k]` would answer each query in `O(1)` (`E_Sum_of_Subarrays.cpp`).
- Looping `d = 1..n` for divisor sums when `n` is `1e12` (`cses-sumofdivisors.cpp`); use quotient blocks, and reduce block sums modulo `m` carefully (divide by 2 before reducing, or use an inverse).
- Forgetting to sort before the pairwise absolute difference formula.

## Related patterns

Pair counts with overlaps use [pair counting with inclusion-exclusion](pair-counting-inclusion-exclusion.md); combinatorial weights often need [binomial counting](binomial-counting.md). Per-element subarray ranges bounded by "next greater" use a [monotonic stack](monotonic-stack.md), and bitwise sums split into [per-bit](per-bit-reasoning.md) contributions. Prefix sums of weights are [prefix sums and difference arrays](prefix-sums-and-difference-arrays.md); divisor counts relate to [divisor enumeration](divisor-enumeration.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B. Erase First or Second Letter (cpp)](../../solutions/strings/B_Erase_First_or_Second_Letter.cpp) | strings | reviewed |
| [B. Playing in a Casino (cpp)](../../solutions/math/combinatorics/B_Playing_in_a_Casino.cpp) | math/combinatorics | reviewed |
| [cses sumofdivisors (cpp)](../../solutions/math/number-theory/cses-sumofdivisors.cpp) | math/number-theory | reviewed |
| [E - Sum of Subarrays (cpp)](../../solutions/arrays-and-counting/E_Sum_of_Subarrays.cpp) | arrays-and-counting | reviewed |
| [H. Permutator (cpp)](../../solutions/greedy/H_Permutator.cpp) | greedy | reviewed |
| [I. Swap(Mohamed, !Mohamed) (cpp)](../../solutions/prefix-sums/I_Swap_Mohamed_Mohamed.cpp) | prefix-sums | reviewed |
| [playing in a casino (python)](../../solutions/sorting-and-searching/playing_in_a_casino.py) | sorting-and-searching | reviewed |
| [X - All Pairs Segments (cpp)](../../solutions/math/combinatorics/X_All_Pairs_Segments.cpp) | math/combinatorics | reviewed |

<!-- examples:end -->
