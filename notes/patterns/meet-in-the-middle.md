# Meet in the middle

Split a search of size `2^n` (or a path of length `L`) into two halves, enumerate each half independently (`2^(n/2)` each), and combine the halves with sorting, binary search or a hash map. This turns roughly `2^40` into roughly `2^20 * 20`.

## Recognition clues

- `n` around 35–40 with "choose a subset" or "assign each item one of two options" — too big for plain [subset enumeration](subset-enumeration.md), too small or value-heavy for a [knapsack](knapsack-dp.md).
- Huge weights or a modulus that rules out sum-indexed DP.
- Four-value or pair-of-pairs sums (`a + b + c + d = x`), where pairs are the "halves".
- Grid paths of length `n + m - 2` with `n, m` around 20: walk half the moves from each corner and meet on the anti-diagonal.

## Invariant and variants

Every full choice is a unique pair (left part, right part), so the answer is a join over left values `l` and right values `r` satisfying a condition on `l + r`:

```cpp
// count subsets with A <= sum <= B
sort(R.begin(), R.end());
for (ll l : L)
    ans += upper_bound(R.begin(), R.end(), B - l) - lower_bound(R.begin(), R.end(), A - l);
```

| Variant | Join | Repo idea |
| --- | --- | --- |
| Count sum `== x` / in `[A, B]` | sorted right half, bounds | `J_Meet_in_the_Middle.cpp`, `K_Subset_Sums.cpp` |
| Maximise sum mod `m` | sort right residues; for each `x` take largest `y <= m-1-x`, else largest overall (wraps) | `H_Maximum_Subsequence.cpp` |
| Four values summing to `x` | map from pair sum to earlier pairs | `cses-sumoffourvalues.cpp`, `sum-of-four-values.py` |
| Grid path sums mod `k` | per-meeting-cell remainder maps | `J_Apple_s_Farm.cpp` |

Time `O(2^(n/2) * n)` for generation plus `O(2^(n/2) log)` for the join; memory `O(2^(n/2))`. For the four-sum variant, insert pairs `(i, j)` only after querying with `j` as the left index so indices are automatically disjoint, giving `O(n^2)` expected time.

## Common mistakes

- Counting the meeting cell twice in a grid-path split; subtract it once, as `J_Apple_s_Farm.cpp` does when joining.
- Negative remainders in C++: `(s - g) % k` can be negative; normalise with `((x % k) + k) % k`.
- Storing all pairs per sum and then scanning them for disjoint indices is `O(n^2)` memory and can be quadratic per lookup; the "query earlier, then insert" order avoids this.
- Using `int` for subset sums of large values or for the pair count (up to `2^40`).
- `unordered_map` with adversarial keys can degrade; prefer sorting plus binary search when counts are needed.

## Related patterns

Each half is ordinary [subset enumeration](subset-enumeration.md) or [backtracking](backtracking-recursion.md). The join step is [sorted lookup](sorted-lookup.md) or a hash map like [prefix sums with a frequency map](prefix-sum-frequency-map.md). Modular joins rely on [modular arithmetic](modular-arithmetic.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [cses sumoffourvalues (cpp)](../../solutions/meet-in-the-middle/cses-sumoffourvalues.cpp) | meet-in-the-middle | reviewed |
| [H - Maximum Subsequence (cpp)](../../solutions/meet-in-the-middle/H_Maximum_Subsequence.cpp) | meet-in-the-middle | reviewed |
| [J - Meet in the Middle (cpp)](../../solutions/meet-in-the-middle/J_Meet_in_the_Middle.cpp) | meet-in-the-middle | reviewed |
| [J Apple s Farm (cpp)](../../solutions/meet-in-the-middle/J_Apple_s_Farm.cpp) | meet-in-the-middle | reviewed |
| [K - Subset Sums (cpp)](../../solutions/meet-in-the-middle/K_Subset_Sums.cpp) | meet-in-the-middle | reviewed |
| [sum of four values (python)](../../solutions/sorting-and-searching/sum-of-four-values.py) | sorting-and-searching | reviewed |

<!-- examples:end -->
