# XOR properties and cancellation

XOR is associative, commutative, self-inverse (`x ^ x = 0`) and has identity `0`, so it behaves like addition without carries over GF(2). Most XOR problems reduce to cancelling pairs, prefix XORs, or the identity `a + b = (a ^ b) + 2(a & b)`.

## Recognition clues

- "XOR of all elements except one", hidden values recoverable from aggregate XORs.
- Range XOR queries, or flipping/toggling ranges where only the total XOR matters.
- XOR of `0..n-1` (MEX with a prescribed XOR), XOR over all subarrays, or parity of how often each element appears.
- Given both a sum and an XOR (`u = xor`, `v = sum`) and asked for a construction.
- Hamming distance as `popcount(a ^ b)`.

## Invariant and variants

Prefix XOR with `px[0] = 0` and `px[i] = a[0] ^ ... ^ a[i-1]` gives `xor(l..r) = px[r+1] ^ px[l]`. An element contributes to an XOR aggregate only by the parity of its multiplicity.

| Variant | Repo idea |
| --- | --- |
| Remove one element from a total | `AA_Red_Scarf.cpp`: each answer is `total ^ a[i]`; `B_XOR_Array.cpp` updates the total by XORing out the old value and in the new one |
| Range XOR | `H_Range_Xor_Queries.cpp`; `AJ_Data_Structures_Fan.cpp` flips a range between two groups by XORing the range XOR into both totals |
| Parity of appearances | `B_XOR_Subarrays.cpp`: element `i` appears in `(i+1)(n-i)` subarrays; only odd counts survive |
| XOR of `0..n` | `X_MEXor_Mixup.cpp` precomputes it; closed form by `n % 4`: `n, 1, n+1, 0` |
| Sum and XOR construction | `Ehab_The_Exorcist.py`: need `u <= v`, same parity; `x = (v-u)/2`; answer length 0, 1, 2 (`u+x, x` if `u & x == 0`) or 3 (`u, x, x`) |
| Minimise `(a^x) + (b^x)` | `U_XORwice.cpp`: choose `x = a & b`, result `a ^ b` |
| Common run of `n^x` and `n^y` | `B_XOR_Sequences.cpp`: `2^i` for the lowest differing bit `i` of `x ^ y` |
| Small value bound, brute force the key | `AI_Johnny_and_His_Hobbies.cpp`: try every `k < 1024` |

Prefix XOR is `O(n)` build, `O(1)` query. When values are below `2^b`, any XOR of them is also below `2^b`, which bounds brute force over keys.

## Common mistakes

- Off-by-one between 1-indexed `pref[r] ^ pref[l-1]` and 0-indexed `px[r+1] ^ px[l]`.
- In the MEX/XOR construction, the extra element `x ^ b` may equal `a` itself (forbidden), forcing two extra elements.
- Forgetting the parity check (`v - u` odd) or `u > v` before constructing.
- Printing `-1` and then falling through to further output: `T_Bitwise_Operators.py` does not return after the power-of-two case.
- Precedence: `x ^ b == a` is `x ^ (b == a)` in C++; parenthesise.

## Related patterns

XOR identities are a special case of [per-bit reasoning](per-bit-reasoning.md). Prefix XOR is the XOR analogue of [prefix sums and difference arrays](prefix-sums-and-difference-arrays.md), and counting equal prefix XORs follows [prefix sums with a frequency map](prefix-sum-frequency-map.md). Per-element contribution counts connect to the [contribution technique](contribution-technique.md); parity arguments to [parity and invariants](parity-and-invariants.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [AA - Red Scarf (cpp)](../../solutions/bit-manipulation/AA_Red_Scarf.cpp) | bit-manipulation | reviewed |
| [AI - Johnny and His Hobbies (cpp)](../../solutions/brute-force-and-backtracking/AI_Johnny_and_His_Hobbies.cpp) | brute-force-and-backtracking | reviewed |
| [AJ - Data Structures Fan (cpp)](../../solutions/prefix-sums/AJ_Data_Structures_Fan.cpp) | prefix-sums | reviewed |
| [B Fedor and New Game (cpp)](../../solutions/bit-manipulation/B_Fedor_and_New_Game.cpp) | bit-manipulation | reviewed |
| [B XOR Array (cpp)](../../solutions/bit-manipulation/B_XOR_Array.cpp) | bit-manipulation | reviewed |
| [B XOR Sequences (cpp)](../../solutions/bit-manipulation/B_XOR_Sequences.cpp) | bit-manipulation | reviewed |
| [B. XOR Subarrays (cpp)](../../solutions/bit-manipulation/B_XOR_Subarrays.cpp) | bit-manipulation | reviewed |
| [C Yet another XOR problem (cpp)](../../solutions/prefix-sums/C_Yet_another_XOR_problem.cpp) | prefix-sums | reviewed |
| [Ehab The Exorcist (python)](../../solutions/bit-manipulation/Ehab_The_Exorcist.py) | bit-manipulation | reviewed |
| [H - Range Xor Queries (cpp)](../../solutions/prefix-sums/H_Range_Xor_Queries.cpp) | prefix-sums | reviewed |
| [T - Bitwise Operators (python)](../../solutions/bit-manipulation/T_Bitwise_Operators.py) | bit-manipulation | reviewed |
| [U - XORwice (cpp)](../../solutions/bit-manipulation/U_XORwice.cpp) | bit-manipulation | reviewed |
| [X - MEXor Mixup (cpp)](../../solutions/bit-manipulation/X_MEXor_Mixup.cpp) | bit-manipulation | reviewed |

<!-- examples:end -->
