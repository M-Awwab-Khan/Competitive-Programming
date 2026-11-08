# Primes, sieves, and factorization

Test primality by trial division up to `sqrt(n)` for one value, sieve when many values up to `N` are queried, and store the smallest prime factor (SPF) when you need factorizations quickly. Large single values use Miller-Rabin.

## Recognition clues

- "Exactly three divisors", "almost prime", "number of prime factors", "split into primes".
- Many queries with values up to `1e6`–`1e7`: precompute a sieve once.
- Operations that divide by small primes (`/2`, `/3`, `*2/3`): strip those primes and check nothing else remains.
- Equalising by moving prime factors between elements: pool exponents per prime.
- A single value up to `1e18` and "next prime" or "is it prime": deterministic Miller-Rabin.

## Invariant and variants

Every composite `n` has a prime factor `<= sqrt(n)`. The SPF sieve gives `factorize(x)` in `O(log x)` by dividing by `spf[x]` repeatedly.

```cpp
for (int i = 2; i <= N; ++i) if (spf[i] == 0)
    for (int j = i; j <= N; j += i) if (spf[j] == 0) spf[j] = i;
```

| Variant | Key fact | Repo illustration |
| --- | --- | --- |
| Eratosthenes | start crossing at `p*p`; `O(N log log N)` | `B_T_primes.cpp`, `B_Hungry_Sequence.cpp` |
| T-primes | exactly three divisors iff `p^2` with `p` prime | `B_T_primes.cpp` |
| SPF + prefix counts | `Omega(i) = Omega(i / spf[i]) + 1`; prime factors of `a!/b!` is `pref[a] - pref[b]` | `D_Soldier_and_Number_Game.cpp` |
| Distinct prime count | insert SPFs into a set while dividing | `A_Almost_Prime.cpp`, `yuki-primefactorization.cpp` |
| Pool exponents | equal values reachable iff each prime's total exponent is divisible by `n` | `D_Divide_And_Equalize.cpp` |
| Divisor count | `d(n) = product (e_i + 1)` | `B_Easy_Number_Challenge.cpp` |
| Strip fixed primes | count factors of 2 and 3, require remainder 1 | `B_Multiply_by_2_divide_by_6.cpp`, `A_Divide_it.cpp` |
| Euler phi sieve | `phi[j] -= phi[j] / p` for multiples `j` of prime `p` | `B_Farouk_and_Password.cpp` |

### Goldbach decompositions

Every even number `>= 4` is a sum of two primes (verified far beyond contest limits). For `n` that is not prime: 2 primes if `n` is even or `n - 2` is prime, otherwise 3 (`3 +` an even number) (`D_Taxes.cpp`). To write `n` as at most three primes, take the largest prime `p < n`; prime gaps are small, so `n - p` is tiny and can be split by brute force (`D_Dima_and_Lisa.cpp`).

### Miller-Rabin

Write `n - 1 = d * 2^s`, then test witnesses `a`. Bases `{2, 3, 5, 7, 11}` are deterministic only for `n < 2.15e12`; the seven bases `{2, 325, 9375, 28178, 450775, 9780504, 1795265022}` cover all 64-bit `n`. Multiplications need `__int128` (`next_prime.cpp`, `next-prime.py`). Each test is `O(k log n)`.

## Common mistakes

- Treating 1 as prime, or rejecting 2 because an even check runs before the `n == 2` check (`next_prime.cpp`'s `isPrime(2)` returns false).
- Trial division bound `i <= round(sqrt(a))` with floating point; use `i * i <= a`.
- Claiming small-base Miller-Rabin is deterministic for all 64-bit inputs (`next-prime.py` comment).
- Checking `sqrt(x)` as a perfect square without correcting the floating result for `x` near `1e12` and above.
- Summing many totients or divisor counts in `int` (`B_Farouk_and_Password.cpp`).
- Allocating a sieve per test case instead of once.

## Related patterns

Enumerating all divisors rather than prime factors is [divisor enumeration](divisor-enumeration.md). Modular exponentiation inside Miller-Rabin is [modular arithmetic](modular-arithmetic.md). Gcd questions often factor through [gcd and lcm](gcd-lcm.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A. Almost Prime (cpp)](../../solutions/math/number-theory/A_Almost_Prime.cpp) | math/number-theory | reviewed |
| [A. Divide it! (cpp)](../../solutions/math/number-theory/A_Divide_it.cpp) | math/number-theory | reviewed |
| [B Coins (cpp)](../../solutions/math/number-theory/B_Coins.cpp) | math/number-theory | reviewed |
| [B Easy Number Challenge (cpp)](../../solutions/math/number-theory/B_Easy_Number_Challenge.cpp) | math/number-theory | reviewed |
| [B Hungry Sequence (cpp)](../../solutions/math/number-theory/B_Hungry_Sequence.cpp) | math/number-theory | reviewed |
| [B T primes (cpp)](../../solutions/math/number-theory/B_T_primes.cpp) | math/number-theory | reviewed |
| [B. Different Divisors (cpp)](../../solutions/math/number-theory/B_Different_Divisors.cpp) | math/number-theory | reviewed |
| [B. El GCD haywady Ashraf fe 7eta tanya (cpp)](../../solutions/math/number-theory/B_El_GCD_haywady_Ashraf_fe_7_eta_tanya.cpp) | math/number-theory | reviewed |
| [B. Farouk and Password (cpp)](../../solutions/math/number-theory/B_Farouk_and_Password.cpp) | math/number-theory | reviewed |
| [B. Multiply by 2, divide by 6 (cpp)](../../solutions/math/number-theory/B_Multiply_by_2_divide_by_6.cpp) | math/number-theory | reviewed |
| [D Dima and Lisa (cpp)](../../solutions/math/number-theory/D_Dima_and_Lisa.cpp) | math/number-theory | reviewed |
| [D Divide And Equalize (cpp)](../../solutions/math/number-theory/D_Divide_And_Equalize.cpp) | math/number-theory | reviewed |
| [D Taxes (cpp)](../../solutions/math/number-theory/D_Taxes.cpp) | math/number-theory | reviewed |
| [D. Soldier and Number Game (cpp)](../../solutions/math/number-theory/D_Soldier_and_Number_Game.cpp) | math/number-theory | reviewed |
| [kattis pascal (cpp)](../../solutions/math/number-theory/kattis-pascal.cpp) | math/number-theory | reviewed |
| [next prime (python)](../../solutions/math/number-theory/next-prime.py) | math/number-theory | reviewed |
| [next prime (cpp)](../../solutions/math/number-theory/next_prime.cpp) | math/number-theory | reviewed |
| [test2 (cpp)](../../solutions/math/number-theory/test2.cpp) | math/number-theory | reviewed |
| [yuki primefactorization (cpp)](../../solutions/math/number-theory/yuki-primefactorization.cpp) | math/number-theory | reviewed |

<!-- examples:end -->
