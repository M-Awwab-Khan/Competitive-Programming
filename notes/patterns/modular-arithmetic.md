# Modular arithmetic

Keep every intermediate value reduced modulo `m`, and replace division by multiplication with a modular inverse. Also covers periodicity modulo `m`, fast exponentiation, and reducing huge exponents.

## Recognition clues

- "Print the answer modulo `1e9 + 7`" or `998244353`: the true answer is astronomically large, usually a count.
- An exponent, factorial, or product of `n` values with `n` up to `1e6`–`1e18`.
- "Last digit", "remainder when divided by", or a recurrence asked at index `1e18`: look for a period.
- Divisibility by 3 or 9 of a long decimal string: work with the digit sum modulo 9.
- Grouping values by `a[i] % k`, or pairing residues `r` and `k - r`.

## Invariant and variants

Addition, subtraction, and multiplication commute with reduction; division does not.

```cpp
long long power(long long a, long long e, long long m) {
    long long r = 1 % m; a %= m;
    while (e > 0) { if (e & 1) r = r * a % m; a = a * a % m; e >>= 1; }
    return r;
}
// prime m, a % m != 0:  inverse(a) = power(a, m - 2, m)
```

| Variant | Key fact | Repo illustration |
| --- | --- | --- |
| Factorial tables | `fact[i]`, then `inv_fact[N] = fact[N]^(m-2)`, descend with `inv_fact[i] = inv_fact[i+1] * (i+1)` | `B_NCR_With_Mod.cpp`, `C_How_Many_Strings.cpp` |
| Huge exponent `a^(b^c)` | Fermat: reduce the exponent mod `m - 1` when `gcd(a, m) = 1` | `cses-exponentiation2.cpp` |
| Periodic sequence | `f(i) = f(i-1) - f(i-2)` has period 6; Fibonacci mod 10 has period 60 | `cf-B_Jzzhu_and_Sequences.cpp`, `C_Fib_Last_Digit.cpp` |
| Digital root | repeated digit sum of `n > 0` is `1 + (n - 1) % 9` | `summing-digits.cpp`, `L_Recursive_Digit_Sum.cpp` |
| Residue buckets | count `a[i] % k`; pair `r` with `k - r`, treat `0` and `k/2` separately | `B_M_Arrays.cpp`, `gameOfDivision.py` |
| Sum of coefficients | coefficients of `P(x)^k` sum to `P(1)^k` | `C_Kaosar_loves_Polynomials.cpp` |
| Wide intermediate | 64-bit modulus products need `__int128` | `next_prime.cpp`, `A_AND_Pairs.cpp` |

Fast power is `O(log e)`. Factorial tables cost `O(N)` once, then `O(1)` per binomial.

## Common mistakes

- Reducing the exponent by `m - 1` when `a` is a multiple of `m`: if the reduced exponent is 0 the result becomes 1 instead of 0 (noted for `cses-exponentiation2.cpp`).
- `power` returning 1 for `m = 1`; start with `r = 1 % m`.
- Subtraction leaving a negative value; normalise with `(x % m + m) % m`.
- Overflow before reduction: `a * b` with both below `1e9 + 7` fits in `long long`, but not if either factor is unreduced or the modulus is near `1e18`. Shifts like `1LL << n` overflow for `n >= 63` (`D_Product_Subsequences.cpp`).
- Dividing a reduced value by an integer (`x % m / 2`); multiply by the inverse of 2 instead.
- Using Fermat's inverse with a composite modulus.
- Rebuilding factorial tables inside every query.

## Related patterns

[Binomial counting](binomial-counting.md) is the main consumer of factorial tables. Primality tests and Euler's totient live in [primes, sieves, and factorization](primes-sieve-and-factorization.md). Residue invariants overlap with [parity and invariants](parity-and-invariants.md), and digit-sum residues with [digit manipulation](digit-manipulation.md). Long periods are found by [simulation with cycle detection](simulation-with-cycle.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A AND Pairs (cpp)](../../solutions/math/arithmetic/A_AND_Pairs.cpp) | math/arithmetic | reviewed |
| [AE - AND Sequences (cpp)](../../solutions/math/combinatorics/AE_AND_Sequences.cpp) | math/combinatorics | reviewed |
| [B Cubes Sum (cpp)](../../solutions/math/arithmetic/B_Cubes_Sum.cpp) | math/arithmetic | reviewed |
| [B M Arrays (cpp)](../../solutions/math/number-theory/B_M_Arrays.cpp) | math/number-theory | reviewed |
| [B NCR With Mod (cpp)](../../solutions/math/combinatorics/B_NCR_With_Mod.cpp) | math/combinatorics | reviewed |
| [B Subtractonacci (cpp)](../../solutions/math/arithmetic/B_Subtractonacci.cpp) | math/arithmetic | reviewed |
| [B. String (cpp)](../../solutions/math/arithmetic/B_String.cpp) | math/arithmetic | reviewed |
| [BIGINT (cpp)](../../solutions/math/number-theory/BIGINT.cpp) | math/number-theory | reviewed |
| [bit strings (cpp)](../../solutions/math/number-theory/bit_strings.cpp) | math/number-theory | reviewed |
| [C Equality (cpp)](../../solutions/math/number-theory/C_Equality.cpp) | math/number-theory | reviewed |
| [C Fib Last Digit (cpp)](../../solutions/math/arithmetic/C_Fib_Last_Digit.cpp) | math/arithmetic | reviewed |
| [C How Many Strings (cpp)](../../solutions/math/combinatorics/C_How_Many_Strings.cpp) | math/combinatorics | reviewed |
| [C Kaosar loves Polynomials (cpp)](../../solutions/math/number-theory/C_Kaosar_loves_Polynomials.cpp) | math/number-theory | reviewed |
| [C. Lucky Numbers (cpp)](../../solutions/math/combinatorics/C_Lucky_Numbers.cpp) | math/combinatorics | reviewed |
| [cf again25 (cpp)](../../solutions/math/arithmetic/cf-again25.cpp) | math/arithmetic | reviewed |
| [cf B Jzzhu and Sequences (cpp)](../../solutions/math/combinatorics/cf-B_Jzzhu_and_Sequences.cpp) | math/combinatorics | reviewed |
| [cses exponentiation (cpp)](../../solutions/math/number-theory/cses-exponentiation.cpp) | math/number-theory | reviewed |
| [cses exponentiation2 (cpp)](../../solutions/math/number-theory/cses-exponentiation2.cpp) | math/number-theory | reviewed |
| [cses twosets (cpp)](../../solutions/dynamic-programming/knapsack/cses-twosets.cpp) | dynamic-programming/knapsack | reviewed |
| [D Divisble Pairs (cpp)](../../solutions/math/number-theory/D_Divisble_Pairs.cpp) | math/number-theory | reviewed |
| [D Max Product (cpp)](../../solutions/greedy/D_Max_Product.cpp) | greedy | reviewed |
| [D Max Product (python)](../../solutions/greedy/D_Max_Product.py) | greedy | reviewed |
| [D Product Subsequences (cpp)](../../solutions/math/combinatorics/D_Product_Subsequences.cpp) | math/combinatorics | reviewed |
| [D Revenge of the C K or e ys (cpp)](../../solutions/math/combinatorics/D_Revenge_of_the_C_K_or_e_ys.cpp) | math/combinatorics | reviewed |
| [G. Permutation Rank (cpp)](../../solutions/math/combinatorics/G_Permutation_Rank.cpp) | math/combinatorics | reviewed |
| [gameOfDivision (python)](../../solutions/games/gameOfDivision.py) | games | reviewed |
| [horner algo (cpp)](../../solutions/math/arithmetic/horner_algo.cpp) | math/arithmetic | reviewed |
| [L Recursive Digit Sum (cpp)](../../solutions/math/number-theory/L_Recursive_Digit_Sum.cpp) | math/number-theory | reviewed |
| [next prime (python)](../../solutions/math/number-theory/next-prime.py) | math/number-theory | reviewed |
| [next prime (cpp)](../../solutions/math/number-theory/next_prime.cpp) | math/number-theory | reviewed |
| [R - AND 0, Sum Big (python)](../../solutions/math/combinatorics/R_AND_0_Sum_Big.py) | math/combinatorics | reviewed |
| [summing digits (cpp)](../../solutions/math/arithmetic/summing-digits.cpp) | math/arithmetic | reviewed |
| [test (python)](../../solutions/math/number-theory/test.py) | math/number-theory | reviewed |

<!-- examples:end -->
