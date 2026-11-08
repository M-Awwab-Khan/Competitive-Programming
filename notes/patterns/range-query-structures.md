# Range query structures: Fenwick and segment trees

Store an associative aggregate over a balanced decomposition of the array so point updates and range queries both take `O(log n)`. Fenwick trees handle invertible sums; segment trees handle any associative merge, lazy range updates, and descents.

## Recognition clues

- Interleaved updates and range queries with `n, q` around `2e5`.
- Aggregate is sum, min, max, gcd, OR/XOR, or any associative merge.
- "Count unused values smaller than `x`" while removing values: Fenwick over values (permutation rank).
- Subtree queries after an Euler tour turn into range queries.
- Offline queries sorted by right endpoint ("last occurrence" tricks, range mex).
- Range flip/assign/add: lazy propagation.

## Invariant and variants

Node `v` covering `[tl, tr]` stores `merge` of its children; a query decomposes `[l, r]` into `O(log n)` maximal nodes.

```cpp
struct Fenwick {                         // 1-based
    vector<ll> b; int n; Fenwick(int n) : b(n + 1), n(n) {}
    void add(int i, ll d) { for (; i <= n; i += i & -i) b[i] += d; }
    ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += b[i]; return s; }
};
```

| Variant | Key detail |
| --- | --- |
| Fenwick point set | `add(i, x - current)` where current is `sum(i) - sum(i - 1)` |
| Fenwick over values | presence bits; `sum(x - 1)` counts smaller unused values; multiply by `(n - i - 1)!` for permutation rank |
| Level-dependent merge | `2^n` leaves; merge alternates OR/XOR by level, answer at the root |
| GCD tree + occurrence lists | `g = gcd(l..r)`; count positions equal to `g` with `lower_bound/upper_bound` in that value's sorted index list |
| Offline last-occurrence | sweep `r`; min tree over values storing last index; descend to the first value with `last < l` (range mex) |
| Lazy toggle | on full cover: `sum = len - sum`, flip the lazy flag; push before recursing |

Build `O(n)`, operations `O(log n)` (`O(log^2 n)` with a gcd merge factor).

## Common mistakes

- Mixing 1-based Fenwick indices with 0-based data; index 0 loops forever in `add`.
- Identity element wrong for the merge (0 for gcd and sum, `+inf` for min).
- Lazy tags not pushed before descending, or child sums not recomputed after.
- Value domain too small for a mex query: if every value appears, the answer lies just past the domain.
- Computing tree depth with floating `log2`; derive it from the integer `n`.
- Sums in `int`.

## Related patterns

Static sums need only [prefix sums](prefix-sums-and-difference-arrays.md). Subtree ranges come from [tree DFS](tree-dfs.md); order statistics can also use [ordered sets](ordered-set-queries.md). Factorials in the rank formula use [modular arithmetic](modular-arithmetic.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [cses subtreequeries (cpp)](../../solutions/trees/cses-subtreequeries.cpp) | trees | reviewed |
| [D. Xenia and Bit Operations (cpp)](../../solutions/data-structures/range-queries/D_Xenia_and_Bit_Operations.cpp) | data-structures/range-queries | reviewed |
| [E. Baby Baraa playing with LEGO (cpp)](../../solutions/data-structures/range-queries/E_Baby_Baraa_playing_with_LEGO.cpp) | data-structures/range-queries | reviewed |
| [E. Danil and a Part-time Job (cpp)](../../solutions/trees/E_Danil_and_a_Part_time_Job.cpp) | trees | reviewed |
| [F. Ant colony (cpp)](../../solutions/data-structures/range-queries/F_Ant_colony.cpp) | data-structures/range-queries | reviewed |
| [G. Permutation Rank (cpp)](../../solutions/math/combinatorics/G_Permutation_Rank.cpp) | math/combinatorics | reviewed |

<!-- examples:end -->
