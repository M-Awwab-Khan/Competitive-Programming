# Binary search on the answer

Use this when a problem asks for the smallest or largest feasible value and checking one candidate is easier than constructing the optimum directly.

## Recognition clues

Look for “minimum time to produce,” “maximum minimum distance,” or a resource limit under which a target must be achievable. Define `possible(x)` precisely before choosing bounds. Its truth value must change at most once across the search interval.

In `factory_machines.cpp`, feasibility at time `x` means `sum(x / machine_time) >= target`. More time cannot reduce production. In `Aggressive_cows.cpp`, feasibility at distance `d` uses greedy placement in sorted stalls; increasing the required spacing cannot make placement easier.

## Invariant and boundaries

For the smallest feasible integer, maintain an interval containing the answer. With `mid = lo + (hi - lo) / 2`, a feasible midpoint permits `hi = mid`; otherwise use `lo = mid + 1`. This requires a known feasible upper bound.

For the largest feasible integer, keep the best feasible midpoint and search above it, or use an upper midpoint with an appropriate interval invariant. Write the invariant beside the loop rather than mixing updates from different templates.

If checking a candidate costs `T(n)` and the candidate range has width `R`, the search costs `O(T(n) log R)`, plus preprocessing such as sorting.

## Common mistakes

- Binary searching a predicate that is not monotone.
- Using an upper bound that might still be infeasible.
- Overflow in midpoint, products, or accumulated production. Stop accumulating once the target is reached if larger totals are irrelevant.
- Treating a sorted-array bound query as an answer-feasibility search without identifying the predicate.

## Related patterns

Prefix aggregates can make a feasibility check cheap; see [prefix sums with a frequency map](prefix-sum-frequency-map.md) for a different use of cumulative state. See the [pattern hub](INDEX.md) for the other canonical notes.

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [Aggressive cows (cpp)](../../solutions/binary-search/Aggressive_cows.cpp) | binary-search | suggested |
| [E. Building an Aquarium (cpp)](../../solutions/binary-search/E_Building_an_Aquarium.cpp) | binary-search | suggested |
| [factory machines (cpp)](../../solutions/binary-search/factory_machines.cpp) | binary-search | suggested |

<!-- examples:end -->
