# Stack matching and cancellation

Scan left to right and keep unmatched items on a stack; when the incoming item completes a pattern with the top, pop instead of push. Whatever remains is irreducible, and the pops count the matches.

## Recognition clues

- Brackets: validity, number of matched pairs, longest regular subsequence.
- "Repeatedly delete occurrences of `ABC` / of string `t` until none remain"; deletions can create new occurrences.
- Players alternately remove adjacent equal pairs: the total number of removals is fixed, so only its parity matters.
- Terrain or areas between matching `\` and `/`.
- Undo/rollback operations ("add", "delete last", "save version k", "restore version k").

## Invariant and variants

The stack holds exactly the reduced form of the processed prefix. For pair cancellation (brackets, adjacent equal letters) the final result does not depend on deletion order; for a general pattern that overlaps itself (`aba` in `ababa`) it can, so the stack implements the leftmost-first deletion process and you must confirm that is what the statement asks for.

```cpp
string st;
for (char c : s) {
    st.push_back(c);
    if (st.size() >= t.size() && st.compare(st.size() - t.size(), t.size(), t) == 0) {
        st.resize(st.size() - t.size()); ++removed;
    }
}
```

| Variant | Stack contents / rule |
| --- | --- |
| Pair counting per bracket type | separate counters or stacks for `()` and `[]` when types are independent |
| Balance counter | only one bracket type: `bal` never negative and ends at 0 |
| Fill `?` brackets | put `(` in the first `n/2 - open` question marks, then validate with the balance counter |
| Pattern deletion | push, then compare the top `|t|` characters |
| Matching positions | push index of `\`; a `/` at `i` pops `j` and adds `i - j` |
| Persistent stack [variant] | nodes `(value, parent)` in a vector, current version is a node index; push appends, pop moves to parent, save/restore store the index |

All are `O(n)` (pattern deletion `O(n |t|)` with naive top comparison).

## Common mistakes

- Popping or reading `top()` on an empty stack (a closing bracket with nothing open).
- Assuming different bracket types interact when the statement treats subsequences of each type separately (or vice versa).
- Rebuilding the string after each deletion: quadratic.
- In the persistent stack, copying the whole stack on save instead of storing a node index.
- Forgetting the "no pair found" sentinel output (e.g. `-1`).

## Related patterns

A [monotonic stack](monotonic-stack.md) pops by value order instead of by matching. Prefix balances are [prefix sums](prefix-sums-and-difference-arrays.md) over `+1/-1`; removal-count games reduce to [parity and invariants](parity-and-invariants.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Regular Bracket Sequence (cpp)](../../solutions/greedy/A_Regular_Bracket_Sequence.cpp) | greedy | reviewed |
| [B Two Brackets (cpp)](../../solutions/data-structures/stacks-and-queues/B_Two_Brackets.cpp) | data-structures/stacks-and-queues | reviewed |
| [D - Take ABC (cpp)](../../solutions/data-structures/stacks-and-queues/D_-_Take_ABC.cpp) | data-structures/stacks-and-queues | reviewed |
| [D String Game (cpp)](../../solutions/data-structures/stacks-and-queues/D_String_Game.cpp) | data-structures/stacks-and-queues | reviewed |
| [K. Wahban and brackets (cpp)](../../solutions/data-structures/stacks-and-queues/K_Wahban_and_brackets.cpp) | data-structures/stacks-and-queues | reviewed |
| [M Notebook (cpp)](../../solutions/data-structures/stacks-and-queues/M_Notebook.cpp) | data-structures/stacks-and-queues | reviewed |
| [uva globalraining (cpp)](../../solutions/data-structures/stacks-and-queues/uva-globalraining.cpp) | data-structures/stacks-and-queues | reviewed |

<!-- examples:end -->
