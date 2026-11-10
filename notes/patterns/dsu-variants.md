# Disjoint set union and its variants

Maintain a partition under merges. Each set is a tree with a representative root. Path compression plus union by size keep operations nearly constant amortised.

## Recognition clues

- Connectivity or "same group?" queries while groups only merge.
- Per-group aggregates (size, min, max, sum) that combine on merge.
- Deletions that become merges when queries are processed in reverse.
- "Next free / next alive position" queries on a line or circle.
- Values or offsets relative to a group leader (depth to a boss, experience added to a whole group).

## Invariant and variants

`find(x)` returns the root; `unite(a, b)` links root to root. Store aggregate data only at roots and combine it when linking the smaller root under the larger one.

| Variant | Idea |
| --- | --- |
| Aggregates per set | On `unite`, merge `size`, `min`, `max` into the surviving root; query `agg[find(x)]`. |
| Offline deletions | Read all operations, apply them backwards so each `cut` becomes a `union`, store answers, reverse the output. The `cut` operations must remove all edges initially present. |
| Next free cell | Point each occupied position to `position + 1`; `find(p)` is the first free position at or after `p`. Use a sentinel `n + 1`, and wrap a circle by querying `find(1)`. Same idea as "people leaving": a removed person merges with the next one, and the max of the set is the nearest one still present. |
| Range merge | Keep a second `next` pointer that skips indices already merged with their right neighbour, so merging `[l, r]` does amortised `O(n)` total work. |
| Weighted / potential DSU | Store `d[x]` = value of `x` relative to its parent. During path compression, compress the parent first, then add the parent's offset: `d[x] += d[p]`. |
| Group-wide add (lazy) | Add to `lazy[root]`. On linking `y` under `x`, set `d[y] = lazy[y] - lazy[x]` so old members keep their values. A member's value is `lazy[root] + (sum of d along its path)`. |
| Parity (bipartite) DSU | Store `p[x]` = colour of `x` XOR colour of its parent; compress with `p[x] ^= p[parent]`. An edge inside one component is fine only if `p[u] ^ p[v] == 1`; when merging roots, set `p[rv] = p[u] ^ p[v] ^ 1`. Finds the first edge that breaks bipartiteness online. |
| Undo / rollback | Drop path compression, record each union on a stack, and pop to undo. Needed for checkpoints and offline deletions; see [rollback DSU](rollback-dsu.md). |

With union by size and path compression, operations take `O(alpha(n))` amortised. Path compression alone gives `O(log n)` amortised. Weighted variants that must link a specific root under another (for example, the boss relationship) cannot use union by size; they rely on path compression only.

## Common mistakes

- Updating aggregates or offsets on a non-root, or forgetting to call `find` first.
- Compressing a weighted path in the wrong order: `d[parent]` must already be relative to the root before it is added.
- Recursive `find` on a long chain before compression can overflow the stack. Use an iterative find or union by size when linking order is free.
- Missing sentinels in next-free arrays (`n + 1`, or `2n` space for wrap-around tricks).
- Using a group-wide lazy value without subtracting the new root's lazy value from a joining root.
- DSU cannot split sets online; it needs an offline reversal, a [rollback DSU](rollback-dsu.md), or another structure.

## Related patterns

Kruskal's MST and threshold connectivity use the plain union. Combine with [binary search on the answer](binary-search-on-answer.md) when a merge threshold is monotone. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A. Knight Tournament (cpp)](../../solutions/data-structures/disjoint-set/A_Knight_Tournament.cpp) | data-structures/disjoint-set | reviewed |
| [B Max Spanning Tree (cpp)](../../solutions/graphs/spanning-trees/B_Max_Spanning_Tree.cpp) | graphs/spanning-trees | reviewed |
| [Bosses (cpp)](../../solutions/data-structures/disjoint-set/Bosses.cpp) | data-structures/disjoint-set | reviewed |
| [Cutting a graph (cpp)](../../solutions/data-structures/disjoint-set/Cutting_a_graph.cpp) | data-structures/disjoint-set | reviewed |
| [D. Roads not only in Berland (cpp)](../../solutions/data-structures/disjoint-set/D_Roads_not_only_in_Berland.cpp) | data-structures/disjoint-set | reviewed |
| [Disjoint Sets Union (cpp)](../../solutions/data-structures/disjoint-set/Disjoint_Sets_Union.cpp) | data-structures/disjoint-set | reviewed |
| [Disjoint Sets Union 2 (cpp)](../../solutions/data-structures/disjoint-set/Disjoint_Sets_Union_2.cpp) | data-structures/disjoint-set | reviewed |
| [Experience (cpp)](../../solutions/data-structures/disjoint-set/Experience.cpp) | data-structures/disjoint-set | reviewed |
| [First Non-Bipartite Edge (cpp)](../../solutions/data-structures/disjoint-set/First_Non-Bipartite_Edge.cpp) | data-structures/disjoint-set | reviewed |
| [kruskal (cpp)](../../solutions/graphs/spanning-trees/kruskal.cpp) | graphs/spanning-trees | reviewed |
| [Parking (cpp)](../../solutions/data-structures/disjoint-set/Parking.cpp) | data-structures/disjoint-set | reviewed |
| [People are leaving (cpp)](../../solutions/data-structures/disjoint-set/People_are_leaving.cpp) | data-structures/disjoint-set | reviewed |
| [Restructuring Company (cpp)](../../solutions/data-structures/disjoint-set/Restructuring_Company.cpp) | data-structures/disjoint-set | reviewed |
| [Spanning Tree (cpp)](../../solutions/graphs/spanning-trees/Spanning_Tree.cpp) | graphs/spanning-trees | reviewed |

<!-- examples:end -->
