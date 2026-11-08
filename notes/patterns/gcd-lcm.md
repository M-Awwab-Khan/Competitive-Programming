# GCD and LCM

Use `gcd(a, b) = gcd(b, a mod b)` and `lcm(a, b) = a / gcd(a, b) * b`. Repeated subtraction, common divisors, and "first common time" problems all collapse to one gcd or lcm over the array.

## Recognition clues

- Operations like "replace `x` by `x - y`" or "subtract a smaller element": the reachable values are multiples of the gcd.
- "Largest number dividing all elements", "common divisors of all numbers": take the gcd, then work with its divisors.
- "First moment all events coincide", "smallest number divisible by both": lcm.
- "Remove or change one element and maximise the gcd": prefix and suffix gcd arrays.
- Equalising by adding a fixed step: the step is the gcd of pairwise differences.

## Invariant and variants

`gcd` is associative and idempotent, with identity 0: `gcd(0, x) = x`. Subtracting one element from another keeps the gcd of the set unchanged.

| Variant | Formula | Repo illustration |
| --- | --- | --- |
| Reduce by subtraction | final values are all `g = gcd(all)`; minimum sum `n * g` | `A_Fox_and_Number_Game.cpp` |
| Exclude one element | `best = max_i gcd(pref[i-1], suff[i+1])` with 0 sentinels | `C_Another_GCD.cpp`, `GCD_on_Blackboard.cpp` |
| Common divisors | divisors of `gcd(all)`, enumerated to `sqrt(g)` | `C_Common_Divisors.cpp` |
| Difference gcd | `g = gcd(a_i - a_0)`; costs are `(max - a_i) / g` | `H_Insert_and_Equalize.cpp` |
| Bets/periods | `L = lcm(k_i)`, give `L / k_i` to each | `C_Earning_on_Bets.cpp`, `H_Fady_mesh_fady.cpp` |
| Union of multiples | inclusion-exclusion with `n / lcm(...)` | `yuki-countmultiples.cpp`, `D_Plus_Minus_Permutation.cpp` |
| Factorials | `gcd(a!, b!) = min(a, b)!` | `cf-iambored.cpp` |
| Direction normalisation | divide `(dx, dy)` by `gcd(|dx|, |dy|)` and fix the sign | `D_A_Linear_Problem.cpp` |

```cpp
pref[0] = 0; for i in 1..n: pref[i] = gcd(pref[i-1], a[i])
suff[n+1] = 0; for i in n..1: suff[i] = gcd(suff[i+1], a[i])
```

Euclid is `O(log min(a, b))`; a gcd over the whole array is `O(n log V)`. The running gcd only drops `O(log V)` times.

## Common mistakes

- Computing `a * b / gcd` instead of `a / gcd * b`; the product overflows first.
- LCM of many values overflows `long long` quickly (`H_Fady_mesh_fady.cpp` has no cap). Stop when it exceeds the bound that matters, or use `__int128`.
- Using `__gcd` with negative arguments; take absolute values or use `std::gcd`.
- Off-by-one in the sentinel index of prefix/suffix arrays (`C_Another_GCD.cpp` uses `pref[i]` and `suff[i+2]` with 1-based arrays).
- `n = 1` in "remove one element" problems: the remaining set is empty and the gcd is unbounded.
- A file named after one algorithm can implement another: `chinese_remainder_theorem.cpp` only computes an lcm.

## Related patterns

Divisors of a gcd are enumerated with [divisor enumeration](divisor-enumeration.md); prime-based reasoning about gcd uses [primes and factorization](primes-sieve-and-factorization.md). Gcd is a non-invertible window aggregate, so a sliding version needs a [two-stack aggregate queue](two-stack-aggregate-queue.md) or [two-pointer window](two-pointer-window.md) with care. Union counts use [inclusion-exclusion](pair-counting-inclusion-exclusion.md), and gcd preservation is a core [invariant](parity-and-invariants.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Fox and Number Game (cpp)](../../solutions/math/number-theory/A_Fox_and_Number_Game.cpp) | math/number-theory | reviewed |
| [C Earning on Bets (cpp)](../../solutions/math/number-theory/C_Earning_on_Bets.cpp) | math/number-theory | reviewed |
| [C Frosted Highway (cpp)](../../solutions/prefix-sums/C_Frosted_Highway.cpp) | prefix-sums | reviewed |
| [C. Another GCD (cpp)](../../solutions/math/number-theory/C_Another_GCD.cpp) | math/number-theory | reviewed |
| [C. Common Divisors (cpp)](../../solutions/math/number-theory/C_Common_Divisors.cpp) | math/number-theory | reviewed |
| [cf ehabandgcd (cpp)](../../solutions/constructive/cf-ehabandgcd.cpp) | constructive | reviewed |
| [cf iambored (cpp)](../../solutions/math/number-theory/cf-iambored.cpp) | math/number-theory | reviewed |
| [cf kingkeymystery (cpp)](../../solutions/math/number-theory/cf-kingkeymystery.cpp) | math/number-theory | reviewed |
| [cf twodivisors (cpp)](../../solutions/math/number-theory/cf-twodivisors.cpp) | math/number-theory | reviewed |
| [chinese remainder theorem (cpp)](../../solutions/math/number-theory/chinese_remainder_theorem.cpp) | math/number-theory | reviewed |
| [csa gcd (cpp)](../../solutions/math/number-theory/csa-gcd.cpp) | math/number-theory | reviewed |
| [D. A Linear Problem (cpp)](../../solutions/geometry/D_A_Linear_Problem.cpp) | geometry | reviewed |
| [D. Plus Minus Permutation (cpp)](../../solutions/math/number-theory/D_Plus_Minus_Permutation.cpp) | math/number-theory | reviewed |
| [E FizzBuzz Sum Hard (cpp)](../../solutions/math/number-theory/E_FizzBuzz_Sum_Hard.cpp) | math/number-theory | reviewed |
| [G Difference Operations (cpp)](../../solutions/math/number-theory/G_Difference_Operations.cpp) | math/number-theory | reviewed |
| [GCD on Blackboard (cpp)](../../solutions/math/number-theory/GCD_on_Blackboard.cpp) | math/number-theory | reviewed |
| [H - Insert and Equalize (cpp)](../../solutions/math/number-theory/H_Insert_and_Equalize.cpp) | math/number-theory | reviewed |
| [H. Fady mesh fady (cpp)](../../solutions/math/number-theory/H_Fady_mesh_fady.cpp) | math/number-theory | reviewed |
| [Journey For Grapes (cpp)](../../solutions/math/number-theory/Journey_For_Grapes.cpp) | math/number-theory | reviewed |
| [largest partition (cpp)](../../solutions/math/number-theory/largest_partition.cpp) | math/number-theory | reviewed |
| [Little Elephant and Divisors (cpp)](../../solutions/math/number-theory/Little_Elephant_and_Divisors.cpp) | math/number-theory | reviewed |
| [yuki countmultiples (cpp)](../../solutions/math/combinatorics/yuki-countmultiples.cpp) | math/combinatorics | reviewed |

<!-- examples:end -->
