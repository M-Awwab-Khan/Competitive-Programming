# Tree DFS, subtree aggregates, and binary lifting

Root the tree, DFS with a parent argument, and combine children's results on the way back up. Euler-tour times turn subtrees into contiguous ranges, and binary lifting answers ancestor jumps in `O(log n)`.

## Recognition clues

- `n` vertices and `n - 1` edges, or a parent array: it is a tree.
- "For every vertex, count/sum over its subtree", "remove one edge to split the tree", "number of subordinates".
- Constraints along a root-to-leaf path (e.g. at most `m` consecutive marked vertices).
- Updates/queries "on the subtree of `v`": flatten with an Euler tour.
- "k-th ancestor", or repeatedly following a pointer (`prev greater index`, parent) many times per query: binary lifting.

## Invariant and variants

Post-order invariant: when `dfs(u)` returns, `sub[u]` is final for the whole subtree.

```cpp
void dfs(int u, int p) {
    tin[u] = ++timer; sub[u] = a[u];
    for (int v : adj[u]) if (v != p) { dfs(v, u); sub[u] += sub[v]; }
    tout[u] = timer;              // subtree of u == positions [tin[u], tout[u]]
}
```

| Variant | Recurrence / idea |
| --- | --- |
| Subtree size or sum | `sub[u] = a[u] + sum sub[child]` |
| Edge cut | removing edge `(parent, u)` splits into `sub[u]` and `S - sub[u]` |
| Path state pushed down | pass a running value (consecutive count) as a by-value argument; prune when it exceeds the limit; count leaves (degree 1, not the root) |
| Validity bottom-up | return a tuple such as `(isBST, sum, min, max)` and combine |
| Euler tour + structure | `tin/tout` + Fenwick or lazy segment tree for subtree updates/queries |
| Binary lifting [variant] | `up[v][0] = parent`, `up[v][j] = up[up[v][j-1]][j-1]`; jump along set bits of `k` |

Binary lifting also works on any "pointer to an earlier index" forest, such as previous-greater links from a [monotonic stack](monotonic-stack.md): with a sentinel `0` meaning "none", count jumps while `up[c][j] >= l`.

DFS is `O(n)`; lifting tables cost `O(n log n)` time and memory, queries `O(log n)`.

## Common mistakes

- Revisiting the parent in an undirected adjacency list (no `v != p` or visited check).
- Counting the root as a leaf when it has degree 1.
- Recursion depth `n` on a path graph; raise the stack or iterate.
- Subtree sums and products of part sizes (`x * (S - x)`) overflow `int`.
- Assuming the first number of each edge is the parent; read the edge undirected unless guaranteed.
- Lifting table with too few levels for `n`, or `-1` sentinels that are then used as array indices.
- Leaving debug prints of lifting tables in the output.

## Related patterns

Trees are a special case of [graph BFS/DFS](graph-bfs-dfs.md). Euler-tour ranges plug into [range query structures](range-query-structures.md). Subtree contributions are a form of the [contribution technique](contribution-technique.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [C Kefa and Park (cpp)](../../solutions/trees/C_Kefa_and_Park.cpp) | trees | reviewed |
| [cses subtreequeries (cpp)](../../solutions/trees/cses-subtreequeries.cpp) | trees | reviewed |
| [D - Subordinates (cpp)](../../solutions/trees/D_Subordinates.cpp) | trees | reviewed |
| [E Screenmaxxing (cpp)](../../solutions/trees/E_Screenmaxxing.cpp) | trees | reviewed |
| [E. Danil and a Part-time Job (cpp)](../../solutions/trees/E_Danil_and_a_Part_time_Job.cpp) | trees | reviewed |
| [parentchild (python)](../../solutions/trees/parentchild.py) | trees | reviewed |
| [test (cpp)](../../solutions/data-structures/stacks-and-queues/test.cpp) | data-structures/stacks-and-queues | reviewed |
| [tree (cpp)](../../solutions/trees/tree.cpp) | trees | reviewed |

<!-- examples:end -->
