# Ternary search on a unimodal function

Minimise (or maximise) a function that strictly decreases then increases by comparing two interior probes and discarding the third of the range that cannot contain the optimum.

## Recognition clues

- "Choose a time / meeting point / target height `x` to minimise a cost" where the cost is a sum or max of convex pieces: `|a_i - x|`, `w_i |h_i - x|`, `max(x - a_i, 0)`, `max_i(S_i T + D_i) - min_i(S_i T + D_i)`.
- A smooth continuous objective on a bounded interval with a single interior extremum (`(x^2 + bx + c) / sin x` on `(0, pi/2)`).
- Brute force over every `x` is too slow, but evaluating one `x` is `O(n)`.

## Invariant and variants

The optimum always lies in `[l, r]`. For a convex `f` and probes `m1 < m2`:

- `f(m1) > f(m2)`: the minimum is right of `m1`, so set `l = m1` (integers: `l = m1 + 1`).
- otherwise: a minimum is at or left of `m2`, so set `r = m2` (integers: `r = m2 - 1` is safe, since `f(m1) <= f(m2)` keeps an equally good point).

```cpp
while (r - l > 3) {                       // integer version
    ll m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
    if (f(m1) > f(m2)) l = m1 + 1; else r = m2 - 1;
}
for (ll x = l; x <= r; ++x) best = min(best, f(x));   // finish by scanning
```

For reals, run a fixed number of iterations (100–200 shrink by `(2/3)^k`) instead of an epsilon loop.

| Variant | Why unimodal | Repo illustration |
| --- | --- | --- |
| Spread of linear positions over time | `max` of lines is convex, `min` is concave, difference convex | `N_Race_Time.cpp` (reals, 200 iterations) |
| Raise `a` below `x`, lower `b` above `x` | sum of convex hinge functions | `P_Devu_and_his_Brother.cpp` (integers, scan tail) |
| Weighted absolute distance | sum of `w_i |h_i - x|` is convex piecewise linear | `building_reconstruction.cpp` |
| Smooth objective on an open interval | single interior minimum | `O_Is_This_JEE.cpp` (epsilon loop) |

Complexity: `O(log_{3/2}(range) * cost(f))`. For `building_reconstruction.cpp`, the weighted median also gives the optimum after sorting, without searching.

## Common mistakes

- Applying ternary search to a function with flat regions that is not convex: equal probe values no longer tell which side to drop.
- Integer loop ending at `r - l > 2` or stepping `l = m1` without `+1`, which can loop forever; stop at a small window and scan it.
- Evaluating the answer at `l` only after a real-valued search; evaluate at `(l + r) / 2` or take the min over the final bracket.
- Domain endpoints where `f` is undefined (`sin x = 0` at `0`): shift bounds by an epsilon as `O_Is_This_JEE.cpp` does.
- Overflow in the cost sum (`|h - x| * w` up to about `10^18`): use `long long`/`__int128` and keep bounds within the data range.
- Using an epsilon stopping rule with large coordinates where `r - l` cannot drop below `eps` in `double`.

## Related patterns

If the predicate is monotone rather than unimodal, use [binary search on the answer](binary-search-on-answer.md). Sums of `|a_i - x|` without weights are minimised at the median, see [sort-then-greedy](sort-then-greedy.md). Convexity arguments overlap with [closed-form arithmetic](closed-form-arithmetic.md) when the optimum can be computed directly, and real-valued objectives with [geometry predicates](geometry-predicates.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [building reconstruction (cpp)](../../solutions/ternary-search/building_reconstruction.cpp) | ternary-search | reviewed |
| [N - Race Time! (cpp)](../../solutions/ternary-search/N_Race_Time.cpp) | ternary-search | reviewed |
| [O - Is This JEE (cpp)](../../solutions/ternary-search/O_Is_This_JEE.cpp) | ternary-search | reviewed |
| [P - Devu and his Brother (cpp)](../../solutions/ternary-search/P_Devu_and_his_Brother.cpp) | ternary-search | reviewed |

<!-- examples:end -->
