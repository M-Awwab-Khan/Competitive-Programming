# Backtracking and exhaustive recursion

Build a candidate one decision at a time, recurse, then undo the decision. Prune branches that cannot lead to a valid or better answer. Correctness comes from covering every choice, and speed comes from pruning and a small search depth.

## Recognition clues

- Generate all strings, codes, permutations or expressions of small length (`<= 10` positions, digits 1–9, `?` wildcards).
- Count simple paths, or find any assignment satisfying row/column constraints, with no polynomial structure visible.
- A recursive split rule (`n -> n/3, 2n/3`) where the reachable states are few.
- Statement asks for "all distinct" outputs in lexicographic order.

## Invariant and variants

On entry to `rec(state)`, the state reflects exactly the decisions on the current path; every mutation made before a recursive call is reversed after it.

```cpp
void rec(int depth) {
    if (depth == n) { record(); return; }
    for (auto c : choices(depth)) {
        if (!feasible(c)) continue;      // prune
        apply(c); rec(depth + 1); undo(c);
    }
}
```

| Variant | Repo idea |
| --- | --- |
| Distinct permutations in order | `creating-strings.cpp`: sort, skip a character already tried at this depth |
| Generate numbers | `B_Lucky_Numbers_easy.cpp`: all 4/7 strings up to length 10 |
| Wildcards | `C_Dreamoon_and_WiFi.cpp`: each `?` becomes `+` or `-`, probability = matches / `2^q` |
| Constraint grid | `Grid_Sums_Backtracking.cpp`: row masks with fixed popcount, prune columns with `csum < 0` or `csum > rowsLeft`, restore on return |
| Simple paths | `I_Count_Simple_Paths.cpp`: mark on entry, unmark on return, stop at a cap |
| Small simulation tree | `USACO_Back_And_Forth.cpp`: 4 days of transfers, pass copies, collect results in a set |
| Recursive split | `D_Gold_Rush.cpp`: prune when `n < m` or `n % 3 != 0` |
| Expression search | `DMOJ_24.py`: combine four numbers with arithmetic operations |

Cost is the size of the explored tree: `b^d` for branching `b` and depth `d` before pruning.

## Common mistakes

- Forgetting to undo a mutation (visited flag, column demand) on every exit path, including early `return true`.
- Passing large containers by value at every level (`creating-strings.cpp` copies `visited`); prefer references plus undo.
- No memoisation when subproblems repeat: `cf-1-3-5.cpp` recomputes coin choices exponentially; convert to [linear DP](linear-dp.md).
- No cycle guard when recursing on a graph (`longest_path.cpp`), or encoding multi-digit labels as single characters.
- Not stopping at a required output cap, which turns a bounded count into an exponential walk.

## Related patterns

Mask loops without incremental state are [subset enumeration](subset-enumeration.md). Running two half-depth searches and joining them is [meet in the middle](meet-in-the-middle.md). If states repeat, memoise into [linear DP](linear-dp.md) or [bitmask DP](bitmask-dp.md). Graph walks without undo are [graph BFS/DFS](graph-bfs-dfs.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B. Lucky Numbers (easy) (cpp)](../../solutions/brute-force-and-backtracking/B_Lucky_Numbers_easy.cpp) | brute-force-and-backtracking | reviewed |
| [C Dreamoon and WiFi (cpp)](../../solutions/brute-force-and-backtracking/C_Dreamoon_and_WiFi.cpp) | brute-force-and-backtracking | reviewed |
| [cf 1 3 5 (cpp)](../../solutions/recursion-and-divide-and-conquer/cf-1-3-5.cpp) | recursion-and-divide-and-conquer | reviewed |
| [creating strings (cpp)](../../solutions/brute-force-and-backtracking/creating-strings.cpp) | brute-force-and-backtracking | reviewed |
| [D Gold Rush (cpp)](../../solutions/recursion-and-divide-and-conquer/D_Gold_Rush.cpp) | recursion-and-divide-and-conquer | reviewed |
| [DMOJ 24 (python)](../../solutions/brute-force-and-backtracking/DMOJ_24.py) | brute-force-and-backtracking | reviewed |
| [Grid Sums Backtracking (cpp)](../../solutions/brute-force-and-backtracking/Grid_Sums_Backtracking.cpp) | brute-force-and-backtracking | reviewed |
| [I Count Simple Paths (cpp)](../../solutions/graphs/traversal/I_Count_Simple_Paths.cpp) | graphs/traversal | reviewed |
| [J Apple s Farm (cpp)](../../solutions/meet-in-the-middle/J_Apple_s_Farm.cpp) | meet-in-the-middle | reviewed |
| [longest path (cpp)](../../solutions/graphs/traversal/longest_path.cpp) | graphs/traversal | reviewed |
| [USACO Back And Forth (cpp)](../../solutions/brute-force-and-backtracking/USACO_Back_And_Forth.cpp) | brute-force-and-backtracking | reviewed |
| [uva mastermindhelper (cpp)](../../solutions/brute-force-and-backtracking/uva-mastermindhelper.cpp) | brute-force-and-backtracking | reviewed |

<!-- examples:end -->
