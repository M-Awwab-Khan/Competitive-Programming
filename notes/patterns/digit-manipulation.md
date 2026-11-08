# Digit manipulation

Treat a number as a sequence of decimal (or binary/hex) digits: extract them with `% 10` and `/ 10`, or read the number as a string and decide digit by digit. Greedy choices are usually made from the most significant digit.

## Recognition clues

- Statements about "the sum of digits", "insert/delete/change a digit", "lexicographically or numerically largest/smallest".
- Inputs given as strings of up to `1e5`–`2e5` digits: too long for any integer type.
- Divisibility by 3 or 9 (digit sum), by 2, 5, or 10 (last digit), by 4 or 25 (last two digits).
- The digit sum is small (at most `9 * digits`, e.g. 90 for `1e10`), so a variable can be searched in a short range around a square root (`B_Non_square_Equation.cpp`).
- Effects of `+1` on the digit sum: it rises by 1 unless there are trailing 9s, each of which drops it by 9 (`A_Adjacent_Digit_Sums.cpp`).

## Invariant and variants

```cpp
int digitSum(long long x) { int s = 0; while (x > 0) { s += x % 10; x /= 10; } return s; }
```

| Variant | Decision rule | Repo illustration |
| --- | --- | --- |
| Maximise by insertion | insert `d` before the first digit smaller than `d` | `A_insert_digit.cpp` |
| Maximise with limited adjacent swaps | bring the largest digit within the next `k` positions forward | `B_Pasha_Maximizes.cpp` |
| Minimise with `k` changes | first digit to `1` (or `0` if one digit), later digits to `0` | `D_Ania_and_Minimizing.py` |
| Replace `d` by `9 - d` | take the smaller digit, but never create a leading zero | `A_Chewbaсca_and_Number.cpp` |
| Maximise digit sum `<= n` | candidates: `n`, or decrement one digit and set all later digits to 9 | `I_Maximize_Sum_of_Digits.cpp` |
| Count digit changes from `l` to `r` | sum over powers of ten `p` of `r/p - l/p` | `L_Interesting_Function.cpp` |
| Digit DP shortcut | `dp[i] = 1 + min dp[i - d]` over digits `d` of `i` | `cses-removingdigits.cpp` |
| Counting numbers made of fixed digits | `2^len` numbers per length for digits `{4, 7}` | `C_Lucky_Numbers.cpp` |

Per-digit loops cost `O(log10 V)` per number. String processing is `O(L)`; candidate enumeration such as "decrement digit `i`, fill with 9s" is `O(L^2)` unless the digit sum is updated incrementally.

## Common mistakes

- Producing a leading zero after a change or deletion.
- Converting a long digit string with `stoll` when it may exceed 18 digits.
- Digital root of 0 versus multiples of 9: `n % 9 == 0` maps to 9 only for `n > 0`.
- String formatting of decimals: `Divide_by_100.py` decides whether to print the decimal point from one fractional digit, so values like `.05` lose it. Strip trailing zeros only after deciding the fractional part is non-empty.
- Looping over every combination of changed digits when only residues modulo 9 matter; cap each count at 8 (`C_Uninteresting_Number.cpp` does not).

## Related patterns

Digit sums are residues, so see [modular arithmetic](modular-arithmetic.md). Binary digits are handled in [per-bit reasoning](per-bit-reasoning.md). Greedy digit choices are a special case of [sort-then-greedy](sort-then-greedy.md) thinking, and digit-indexed recurrences belong to [linear DP](linear-dp.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A - Repdigit (cpp)](../../solutions/math/arithmetic/A_Repdigit.cpp) | math/arithmetic | reviewed |
| [A Adjacent Digit Sums (cpp)](../../solutions/math/arithmetic/A_Adjacent_Digit_Sums.cpp) | math/arithmetic | reviewed |
| [A Chewbaсca and Number (cpp)](../../solutions/greedy/A_Chewba%D1%81ca_and_Number.cpp) | greedy | reviewed |
| [A insert digit (cpp)](../../solutions/greedy/A_insert_digit.cpp) | greedy | reviewed |
| [B - Digit Sum (cpp)](../../solutions/brute-force-and-backtracking/B_Digit_Sum.cpp) | brute-force-and-backtracking | reviewed |
| [B - Sum of Digits Sequence (cpp)](../../solutions/math/arithmetic/B_Sum_of_Digits_Sequence.cpp) | math/arithmetic | reviewed |
| [B 0 F (python)](../../solutions/strings/B_0_F.py) | strings | reviewed |
| [B Core Programmer 39 s Job (cpp)](../../solutions/math/arithmetic/B_Core_Programmer_39_s_Job.cpp) | math/arithmetic | reviewed |
| [B Non square Equation (cpp)](../../solutions/math/number-theory/B_Non_square_Equation.cpp) | math/number-theory | reviewed |
| [B Pasha Maximizes (cpp)](../../solutions/greedy/B_Pasha_Maximizes.cpp) | greedy | reviewed |
| [B Unary (python)](../../solutions/strings/B_Unary.py) | strings | reviewed |
| [B Unnatural Conditions (cpp)](../../solutions/constructive/B_Unnatural_Conditions.cpp) | constructive | reviewed |
| [B. Expensive Number (cpp)](../../solutions/greedy/B_Expensive_Number.cpp) | greedy | reviewed |
| [binary (cpp)](../../solutions/bit-manipulation/binary.cpp) | bit-manipulation | reviewed |
| [C. K-th root (cpp)](../../solutions/math/arithmetic/C_K_th_root.cpp) | math/arithmetic | reviewed |
| [C. Uninteresting Number (cpp)](../../solutions/math/arithmetic/C_Uninteresting_Number.cpp) | math/arithmetic | reviewed |
| [cf vladsumofdigits (cpp)](../../solutions/prefix-sums/cf-vladsumofdigits.cpp) | prefix-sums | reviewed |
| [cses removingdigits (cpp)](../../solutions/dynamic-programming/general/cses-removingdigits.cpp) | dynamic-programming/general | reviewed |
| [D - Ania and Minimizing (python)](../../solutions/greedy/D_Ania_and_Minimizing.py) | greedy | reviewed |
| [D Max Product (cpp)](../../solutions/greedy/D_Max_Product.cpp) | greedy | reviewed |
| [D Max Product (python)](../../solutions/greedy/D_Max_Product.py) | greedy | reviewed |
| [D. Sahla bas Sa7la (cpp)](../../solutions/math/arithmetic/D_Sahla_bas_Sa_7_la.cpp) | math/arithmetic | reviewed |
| [Divide by 100... (python)](../../solutions/strings/Divide_by_100.py) | strings | reviewed |
| [I - Maximize Sum of Digits (cpp)](../../solutions/math/arithmetic/I_Maximize_Sum_of_Digits.cpp) | math/arithmetic | reviewed |
| [L - Interesting Function (cpp)](../../solutions/math/arithmetic/L_Interesting_Function.cpp) | math/arithmetic | reviewed |
| [L Recursive Digit Sum (cpp)](../../solutions/math/number-theory/L_Recursive_Digit_Sum.cpp) | math/number-theory | reviewed |
| [love calculator (cpp)](../../solutions/math/arithmetic/love-calculator.cpp) | math/arithmetic | reviewed |
| [summing digits (cpp)](../../solutions/math/arithmetic/summing-digits.cpp) | math/arithmetic | reviewed |

<!-- examples:end -->
