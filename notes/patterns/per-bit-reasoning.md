# Per-bit reasoning

AND, OR and XOR act on each bit independently, so a bitwise question usually splits into up to 30–60 independent one-bit questions. Decide the answer bit by bit, usually from the most significant bit down or by counting per bit.

## Recognition clues

- The statement combines values with `&`, `|` or `^` and asks for a maximum, minimum, count or feasibility.
- Constraints such as `a_i < 2^30` or `n <= 10^18`, where looping over values is impossible but looping over 60 bits is free.
- Conditions like `x + y == x ^ y`, `a & b >= a ^ b`, or "AND of a range is non-zero".
- Sums of distinct powers of two, splitting a number into `k` powers of two, or "largest power of two not exceeding `n`".
- Removing an element from an OR/AND aggregate (not invertible), which suggests per-bit counts.

## Invariant and variants

Key identities:

- `a + b = (a ^ b) + 2 * (a & b)`; hence `a + b == a ^ b` iff `a & b == 0`.
- The highest set bit dominates comparisons: `a & b >= a ^ b` iff `a` and `b` share the same most significant bit.
- Submasks of `n` number `2^popcount(n)`; `x` with `x & n == 0` and `x < 2^(msb+1)` uses only the zero bits of `n`.
- `n & (n - 1)` clears the lowest set bit; `n & -n` isolates it.

| Variant | Repo idea |
| --- | --- |
| Group by most significant bit | `W_Rock_and_Lever.cpp`: sum `C(cnt, 2)` per msb group |
| Count zero bits below msb | `Z_Sum_vs_XOR.cpp`, `Y_The_Great_XOR.cpp`, `A_And_Zero.cpp` |
| Per-bit prefix counts | `AH_And_It_s_Non_Zero.cpp`: `pref[i][b]` = zeros in bit `b` among `1..i`; keep the best single bit |
| Per-bit window counts to remove from an OR | `O_Cat_Fox_and_the_Lonely_Array.cpp`: `cnt[b]` over a sliding window, combined with binary search on length |
| Greedy set bits low to high under a bound | `A_Bits.cpp`: OR in the lowest unset bit while `<= r` |
| Split powers of two | `AG_Powers_Of_Two.cpp`: start with `popcount(n)` terms, split the largest until `k` terms |
| AND of misplaced elements | `B_AND_Sorting.cpp`: AND every `a[i] != i` |
| Independent choice per bit | `R_AND_0_Sum_Big.py`: each of `k` bits is cleared in exactly one of `n` elements, `n^k` arrays |

Per-bit counting costs `O(n * B)` for `B` bits. Use `__builtin_popcountll`, `63 - __builtin_clzll(x)` for the msb of a nonzero 64-bit value.

## Common mistakes

- `1 << 32` or `1 << j` for `j >= 31` on an `int` is undefined behaviour; `B_AND_Sorting.cpp` writes `(1 << 32) - 1`. Use `1LL << j` or `~0LL`/`-1` as the AND identity.
- `__builtin_clz(0)` is undefined; special-case `n = 0` (`Z_Sum_vs_XOR.cpp` returns 1 for `n = 0`).
- Using `log2` on doubles to find the msb; it can round wrongly for large 64-bit values.
- Forgetting that OR and AND cannot be "subtracted" when an element leaves a window; keep per-bit counts instead.
- Operator precedence: `a & b == 0` parses as `a & (b == 0)`; parenthesise.
- An `O(x)` scan over candidate submasks (as in `C_Creating_Keys_for_StORages_Has_Become_My_Main_Skill.cpp`) can be too slow when `x` is large; enumerate submasks directly.

## Related patterns

XOR-specific cancellation tricks live in [XOR properties](xor-properties.md). Enumerating all submasks or subsets is [subset enumeration](subset-enumeration.md), and DP over masks is [bitmask DP](bitmask-dp.md). Per-bit prefix tables reuse [prefix sums and difference arrays](prefix-sums-and-difference-arrays.md); per-bit window counts pair naturally with [binary search on the answer](binary-search-on-answer.md) and the [two-stack aggregate queue](two-stack-aggregate-queue.md). Counting pairs inside msb groups is [pair counting](pair-counting-inclusion-exclusion.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A And Zero (cpp)](../../solutions/bit-manipulation/A_And_Zero.cpp) | bit-manipulation | reviewed |
| [A Not Greater (cpp)](../../solutions/bit-manipulation/A_Not_Greater.cpp) | bit-manipulation | reviewed |
| [A. Bits (cpp)](../../solutions/bit-manipulation/A_Bits.cpp) | bit-manipulation | reviewed |
| [AG - Powers Of Two (cpp)](../../solutions/bit-manipulation/AG_Powers_Of_Two.cpp) | bit-manipulation | reviewed |
| [AH - And It's Non-Zero (cpp)](../../solutions/bit-manipulation/AH_And_It_s_Non_Zero.cpp) | bit-manipulation | reviewed |
| [Alya And Permutation (cpp)](../../solutions/constructive/Alya_And_Permutation.cpp) | constructive | reviewed |
| [B XOR Sequences (cpp)](../../solutions/bit-manipulation/B_XOR_Sequences.cpp) | bit-manipulation | reviewed |
| [B. AND Sorting (cpp)](../../solutions/bit-manipulation/B_AND_Sorting.cpp) | bit-manipulation | reviewed |
| [B. Make Almost Equal With Mod (cpp)](../../solutions/bit-manipulation/B_Make_Almost_Equal_With_Mod.cpp) | bit-manipulation | reviewed |
| [B. Max AND (cpp)](../../solutions/bit-manipulation/B_Max_AND.cpp) | bit-manipulation | reviewed |
| [C Creating Keys for StORages Has Become My Main Skill (cpp)](../../solutions/constructive/C_Creating_Keys_for_StORages_Has_Become_My_Main_Skill.cpp) | constructive | reviewed |
| [C XOR and Triangle (cpp)](../../solutions/bit-manipulation/C_XOR_and_Triangle.cpp) | bit-manipulation | reviewed |
| [C. Game with Multiset (cpp)](../../solutions/bit-manipulation/C_Game_with_Multiset.cpp) | bit-manipulation | reviewed |
| [D All AND (cpp)](../../solutions/bit-manipulation/D_All_AND.cpp) | bit-manipulation | reviewed |
| [O - Cat, Fox and the Lonely Array (cpp)](../../solutions/binary-search/O_Cat_Fox_and_the_Lonely_Array.cpp) | binary-search | reviewed |
| [R - AND 0, Sum Big (python)](../../solutions/math/combinatorics/R_AND_0_Sum_Big.py) | math/combinatorics | reviewed |
| [S - And Then There Were K (cpp)](../../solutions/bit-manipulation/S_And_Then_There_Were_K.cpp) | bit-manipulation | reviewed |
| [W - Rock and Lever (cpp)](../../solutions/bit-manipulation/W_Rock_and_Lever.cpp) | bit-manipulation | reviewed |
| [Y - The Great XOR (cpp)](../../solutions/bit-manipulation/Y_The_Great_XOR.cpp) | bit-manipulation | reviewed |
| [Z - Sum vs XOR (cpp)](../../solutions/bit-manipulation/Z_Sum_vs_XOR.cpp) | bit-manipulation | reviewed |

<!-- examples:end -->
