# Minimum and maximum spanning trees with Kruskal

Sort edges by weight and add each one whose endpoints are in different DSU components. By the cut property, the cheapest edge crossing any cut is safe, so the greedy builds an optimal spanning tree.

## Recognition clues

- "Connect all cities with minimum total cost", "remove edges to keep the graph connected with maximum kept weight".
- Weighted undirected graph and the answer is a sum over `n - 1` chosen edges.
- "The tree must contain edge `j`": force it first, then run Kruskal on the rest.
- Maximise the minimum edge on paths, or maximum spanning tree: sort descending.

## Invariant and variants

After processing edges in sorted order, the chosen edges form a minimum spanning forest of the edges seen so far.

```cpp
sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a.w < b.w; });
DSU d(n); ll total = 0; int used = 0;
for (auto &e : edges) if (d.unite(e.u, e.v)) { total += e.w; if (++used == n - 1) break; }
bool connected = (used == n - 1);
```

| Variant | Change |
| --- | --- |
| Maximum spanning tree | sort in descending order |
| Forced edge | unite its endpoints and add its cost before the loop; skip it by id inside the loop; start the counter at 1 |
| Spanning forest | do not require `n - 1`; sum what is added |
| Minimise the maximum edge (bottleneck) | the MST also minimises its largest edge; answer is the weight of the last edge Kruskal adds |
| Minimise `max - min` over a spanning tree | for each start `l` in sorted order, run Kruskal on `edges[l..]` from a fresh DSU; the first spanning tree has the smallest maximum for that minimum. `O(m^2 α)` |
| Delete edges within a budget, keep connectivity | build a maximum spanning tree to keep; delete the remaining edges cheapest first while the budget allows |
| DSU flavour | path compression + union by rank, or a rollback DSU (no compression) if undo is needed |

Time is `O(m log m)` for sorting plus near-constant DSU operations.

## Common mistakes

- Not validating connectivity: if fewer than `n - 1` edges are added, there is no spanning tree.
- Skipping a forced edge by comparing weights instead of a stable edge id after sorting.
- Total weight in `int`.
- Mixing 0-based and 1-based vertex labels when sizing the DSU.
- Starting the edge counter at 1 for a forced edge that is a self-loop: it adds cost but merges nothing, so count only successful unions.

## Related patterns

The component structure is [DSU](dsu-variants.md); the ordering is [sort-then-greedy](sort-then-greedy.md). For connectivity without weights, see [graph BFS/DFS](graph-bfs-dfs.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B Max Spanning Tree (cpp)](../../solutions/graphs/spanning-trees/B_Max_Spanning_Tree.cpp) | graphs/spanning-trees | reviewed |
| [Dense spanning tree (cpp)](../../solutions/graphs/spanning-trees/Dense_spanning_tree.cpp) | graphs/spanning-trees | reviewed |
| [kruskal (cpp)](../../solutions/graphs/spanning-trees/kruskal.cpp) | graphs/spanning-trees | reviewed |
| [No refuel (cpp)](../../solutions/graphs/spanning-trees/No_refuel.cpp) | graphs/spanning-trees | reviewed |
| [Oil business (cpp)](../../solutions/graphs/spanning-trees/Oil_business.cpp) | graphs/spanning-trees | reviewed |
| [Spanning Tree (cpp)](../../solutions/graphs/spanning-trees/Spanning_Tree.cpp) | graphs/spanning-trees | reviewed |

<!-- examples:end -->
