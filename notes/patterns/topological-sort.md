# Topological order, indegree peeling, and DAG DP

Process a directed acyclic graph so every vertex comes after all of its predecessors. Kahn's algorithm repeatedly removes zero-indegree vertices; the same peeling idea strips leaves off an undirected graph, and the order enables DP over the DAG.

## Recognition clues

- "A must come before B", "X is stronger than Y", prerequisites, dependency order.
- "Is the order unique?" or "find a permutation consistent with these comparisons".
- "Who is the unique strongest/source?": exactly one vertex with indegree 0 (given the relation is complete enough).
- "Count/maximise routes from 1 to n" in a directed graph without cycles.
- Find the cycle of a unicyclic undirected graph: peel degree-1 vertices.

## Invariant and variants

Kahn: the queue holds exactly the vertices whose predecessors are all output. If fewer than `n` vertices are output, a cycle exists.

```cpp
queue<int> q; for (int v = 1; v <= n; ++v) if (!indeg[v]) q.push(v);
while (!q.empty()) {
    if (q.size() > 1) unique = false;        // a choice exists
    int u = q.front(); q.pop(); order.push_back(u);
    for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
}
bool acyclic = (int)order.size() == n;
```

| Variant | Idea |
| --- | --- |
| Unique order | queue size never exceeds 1 and all `n` vertices are output; then `pos[order[i]] = i + 1` is the permutation |
| Unique source only | count vertices with indegree 0; answer is that vertex if the count is 1 |
| Leaf peeling (undirected) | push all `deg == 1`, decrement neighbours, push when they drop to 1; survivors form the cycle |
| DP over DAG [variant] | `ways(u) = sum ways(v)` over `u -> v`, `ways(n) = 1`, modulo `p`; via memoized DFS or reverse topological order |

All are `O(n + m)`.

## Common mistakes

- Duplicate edges increment indegree twice; dedupe (a `set` adjacency) or decrement once per stored edge consistently.
- Checking uniqueness only at the start rather than at every pop.
- Forgetting the cycle check (`order.size() < n`).
- Memoized DAG DP with `0` as the "unset" marker when `0` is a valid answer; use `-1`.
- Recursion depth on a long DAG chain; Kahn order avoids it.
- Summing ways without reducing modulo at each addition.

## Related patterns

Built on [graph BFS/DFS](graph-bfs-dfs.md). DP along the order is [linear DP](linear-dp.md) on a graph; weighted DAG paths are a special case of [shortest paths](shortest-paths.md). Uniqueness-of-permutation questions often appear as [constructive](constructive-small-cases.md) problems. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [at whoisstrongest (cpp)](../../solutions/graphs/topological-sort/at-whoisstrongest.cpp) | graphs/topological-sort | reviewed |
| [cses gameroutes (cpp)](../../solutions/dynamic-programming/general/cses-gameroutes.cpp) | dynamic-programming/general | reviewed |
| [find permutation (cpp)](../../solutions/graphs/topological-sort/find_permutation.cpp) | graphs/topological-sort | reviewed |
| [H. Mad City (cpp)](../../solutions/graphs/traversal/H_Mad_City.cpp) | graphs/traversal | reviewed |

<!-- examples:end -->
