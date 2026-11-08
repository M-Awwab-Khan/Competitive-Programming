# Palindromes: counts, pairs, and two-ended scans

A palindrome is determined by mirrored pairs plus at most one centre. Most problems reduce either to letter-count parity (rearrangement questions) or to a two-pointer scan from both ends (deletion/fix questions).

## Recognition clues

- "Can the letters be rearranged into a palindrome?", "build one", "split into `k` palindromes".
- "Delete all occurrences of one chosen letter (minimum count) to make it a palindrome".
- Binary strings with a required number of equal/unequal mirror pairs.
- Games where the player who faces a palindromable multiset wins.

## Invariant and variants

Rearrangement: possible iff the number of letters with odd count is at most 1 (exactly `n % 2`). A multiset gives `sum(cnt / 2)` mirror pairs.

Two-ended scan: with `l = 0, r = n - 1`, if `s[l] == s[r]` move both; otherwise one side must be deleted. Fixing the deletable letter `c` makes the choice forced, so try all 26 letters.

```cpp
for (char c = 'a'; c <= 'z'; ++c) {
    int l = 0, r = n - 1, del = 0; bool ok = true;
    while (l < r) {
        if (s[l] == s[r]) ++l, --r;
        else if (s[l] == c) ++l, ++del;
        else if (s[r] == c) --r, ++del;
        else { ok = false; break; }
    }
    if (ok) best = min(best, del);
}
```

| Variant | Formula / construction |
| --- | --- |
| Build a palindrome | left half = each letter `cnt/2` times, centre = the odd letter, right = reversed left |
| Binary pairs | `x` zeros, `y` ones: at most `x/2 + y/2` equal pairs; the mixed pairs each use one of each |
| `k` groups | pairs available `P = sum cnt/2`; each group of length `L` uses `L/2` pairs plus a free centre |
| Game parity | the first player wins when the odd-count number is 0 or odd; no simulation needed |

Counting is `O(n + alphabet)`; the 26-letter scan is `O(26 n)`.

## Common mistakes

- Printing "impossible" without returning, so a construction is printed as well.
- Using an uninitialised "odd character" variable when no letter is odd.
- Simulating game turns by copying and rechecking the string (cubic) instead of using the parity rule.
- Greedy distribution of letters into groups that ignores leftover singles usable as centres.

## Related patterns

Counting letters is a [frequency table](frequency-table.md); the scan is a [two-pointer](two-pointer-window.md) motion from both ends. Odd-count reasoning is [parity and invariants](parity-and-invariants.md); the game reduction is [game theory](game-theory.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B Little Girl and Game (cpp)](../../solutions/games/B_Little_Girl_and_Game.cpp) | games | reviewed |
| [C Grandma Capa Knits A Scarf (cpp)](../../solutions/two-pointers-and-sliding-window/C_Grandma_Capa_Knits_A_Scarf.cpp) | two-pointers-and-sliding-window | reviewed |
| [cf notquiteapalindromicstring (cpp)](../../solutions/strings/cf_notquiteapalindromicstring.cpp) | strings | reviewed |
| [D. Palindromes Coloring (cpp)](../../solutions/strings/D_Palindromes_Coloring.cpp) | strings | reviewed |
| [palindrome reorder (cpp)](../../solutions/strings/palindrome_reorder.cpp) | strings | reviewed |

<!-- examples:end -->
