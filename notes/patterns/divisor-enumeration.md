# Divisor enumeration and harmonic multiples

Enumerate the divisors of one number by pairing `i` with `n / i` for `i <= sqrt(n)`, or enumerate multiples of every `d <= N` for a total cost of `N/1 + N/2 + ... = O(N log N)`.

## Recognition clues

- "Split the total into equal parts" or "all piles must be equal": the part size divides the total.
- "Common divisors", "k-th smallest divisor", "sum of divisors equals n".
- A product constraint like `a[i] * a[j] = i + j <= 2n`: for fixed `i`, only multiples of `a[i]` are candidates.
- "Maximum gcd of any pair", "for each value, how many elements divide it / are divisible by it" with values up to `1e6`.
- Statements that remove "the smallest multiple" or touch every multiple of an index.

## Invariant and variants

```cpp
for (long long i = 1; i * i <= n; ++i)
    if (n % i == 0) { add(i); if (i != n / i) add(n / i); }
```

Highly composite numbers have few divisors: at most 1344 below `1e9` and 103680 below `1e18`, so checking each divisor with an `O(n)` test is usually affordable.

| Variant | Loop | Repo illustration |
| --- | --- | --- |
| Pair divisors | `i` and `n / i` up to `sqrt(n)` | `cses-countdivisors.cpp`, `k-th_divisor.cpp` |
| Divisors of the total as candidates | test each `L` dividing the sum | `USACO_Sleeping_in_Class.cpp`, `C_AtCoder_Riko.cpp` |
| Divisors of a gcd | count divisors of `gcd(all)` | `C_Common_Divisors.cpp` |

### Harmonic multiples loop

```cpp
for (int d = 1; d <= N; ++d)
    for (int m = d; m <= N; m += d) work(d, m);   // O(N log N) total
```

| Use | Repo illustration |
| --- | --- |
| Max pair gcd: largest `d` with at least two multiples present | `cses-commondivisors.cpp` |
| Spread each value's frequency to its multiples | `cf-wewerebothchildren.cpp` |
| Per-number divisor aggregate (count, XOR) | `F_Divisors_Count.cpp`, `J_Zaghloul_and_the_spies.cpp` |
| Candidates `j = s - i` for multiples `s` of `a[i]` up to `2n` | `B_Pleasant_Pairs.cpp` |
| Visit multiples of `d`, stop at the first protected one | `C_Removing_Smallest_Multiples.cpp` |

Single-number enumeration is `O(sqrt n)`. The harmonic loop is `O(N log N)` and needs counts indexed by value, so values must be bounded (about `1e6`–`1e7`).

## Common mistakes

- Counting `sqrt(n)` twice for perfect squares.
- Expecting sorted output from pairing: the `n / i` half is descending; sort or collect two lists.
- Loop bound `i * i <= n` overflowing `int` for `n` near `2^31`; use `long long i`.
- Dropping a pair because the `i < j` check is missing or wrong (`B_Pleasant_Pairs.cpp` needs `j > i`).
- Brute-forcing every `x` up to `n` with an `O(sqrt x)` divisor sum (`sumofdivisors.cpp`) when `n` is large; a divisor-sum sieve is `O(n log n)`.
- Indexing a value-count array with values outside `1..N` (`cf-wewerebothchildren.cpp` silently ignores them, which is right only if they cannot matter).

## Related patterns

Prime-factor based counts (`d(n)` from exponents) are in [primes and factorization](primes-sieve-and-factorization.md); divisors of a gcd come from [gcd and lcm](gcd-lcm.md). Summing `floor(n / i)` over all `i` is a [contribution](contribution-technique.md) argument. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B Easy Number Challenge (cpp)](../../solutions/math/number-theory/B_Easy_Number_Challenge.cpp) | math/number-theory | reviewed |
| [B Pleasant Pairs (cpp)](../../solutions/brute-force-and-backtracking/B_Pleasant_Pairs.cpp) | brute-force-and-backtracking | reviewed |
| [C - AtCoder Riko (cpp)](../../solutions/math/number-theory/C_AtCoder_Riko.cpp) | math/number-theory | reviewed |
| [C Removing Smallest Multiples (cpp)](../../solutions/math/number-theory/C_Removing_Smallest_Multiples.cpp) | math/number-theory | reviewed |
| [C. Common Divisors (cpp)](../../solutions/math/number-theory/C_Common_Divisors.cpp) | math/number-theory | reviewed |
| [cf wewerebothchildren (cpp)](../../solutions/math/number-theory/cf-wewerebothchildren.cpp) | math/number-theory | reviewed |
| [cses commondivisors (cpp)](../../solutions/math/number-theory/cses-commondivisors.cpp) | math/number-theory | reviewed |
| [cses countdivisors (cpp)](../../solutions/math/number-theory/cses-countdivisors.cpp) | math/number-theory | reviewed |
| [F Divisors Count (cpp)](../../solutions/math/number-theory/F_Divisors_Count.cpp) | math/number-theory | reviewed |
| [F Frosted Highway Hard (cpp)](../../solutions/math/number-theory/F_Frosted_Highway_Hard.cpp) | math/number-theory | reviewed |
| [J. Zaghloul and the spies (cpp)](../../solutions/prefix-sums/J_Zaghloul_and_the_spies.cpp) | prefix-sums | reviewed |
| [k-th divisor (cpp)](../../solutions/math/number-theory/k-th_divisor.cpp) | math/number-theory | reviewed |
| [sumofdivisors (cpp)](../../solutions/math/number-theory/sumofdivisors.cpp) | math/number-theory | reviewed |
| [USACO Sleeping in Class (cpp)](../../solutions/greedy/USACO_Sleeping_in_Class.cpp) | greedy | reviewed |

<!-- examples:end -->
