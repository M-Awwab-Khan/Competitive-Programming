# Shortest paths: BFS, 0-1 BFS, Dijkstra, Floyd-Warshall

Pick the algorithm by edge weights and query shape: BFS for unit weights, 0-1 BFS for weights in `{0, 1}`, Dijkstra for non-negative weights, Floyd-Warshall for all pairs on small `n`.

## Recognition clues

- "Minimum cost/time/number of transfers from s to t", or "distance from every vertex to n".
- All moves equal cost: BFS. Some moves free and others cost 1 (stay on the same bus route vs. change route): 0-1 BFS over expanded states.
- Non-negative weights up to `1e9` and `n, m` up to `2e5`: Dijkstra with 64-bit distances.
- `n <= 400` and you need distances between all pairs (e.g. then binary search a radius): Floyd-Warshall.
- Distance *to* a fixed target from every vertex: run one search from the target on reversed edges.

## Invariant and variants

Dijkstra: when a vertex is popped with `d == dist[u]`, that distance is final because all weights are non-negative.

```cpp
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
dist[s] = 0; pq.push({0, s});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d != dist[u]) continue;                 // stale entry
    for (auto [v, w] : adj[u]) if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
}
```

| Variant | Note |
| --- | --- |
| BFS | `O(n + m)`; reconstruct with parent links or stored move letters |
| 0-1 BFS | deque: push 0-edges to the front, 1-edges to the back; relax with `dist`, not a one-shot visited flag |
| Dijkstra | `O((n + m) log n)`; a `set<pair<ll,int>>` frontier also works |
| Reversed graph | store edge `u -> v` as `adj[v].push_back(u)` to get distances to the target |
| Floyd-Warshall | `for k, i, j: d[i][j] = min(d[i][j], d[i][k] + d[k][j])`, `O(n^3)`, `k` outermost |

## Common mistakes

- Treating a graph with 0/1 costs as plain BFS with a visited set: a cost-0 continuation discovered late is never improved, so answers can be too large.
- `INF` too small, or `dist[u] + w` overflowing when `dist[u] == INF`; use `ll` and skip unreachable vertices.
- Putting `k` in an inner loop of Floyd-Warshall.
- Forgetting to print `-1` for unreachable vertices.
- Dijkstra with negative edges.
- A greedy feasibility check inside a binary search must actually be correct; greedy max-coverage for k-centre is only a heuristic.

## Related patterns

The traversal core is [graph BFS/DFS](graph-bfs-dfs.md) and [grid traversal](grid-traversal.md). On a DAG, longest/shortest paths are DP in [topological order](topological-sort.md). A monotone distance threshold pairs with [binary search on the answer](binary-search-on-answer.md); the heap is the same tool as in [priority-queue greedy](priority-queue-greedy.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [covid (python)](../../solutions/binary-search/covid.py) | binary-search | reviewed |
| [E - Labyrinth (cpp)](../../solutions/graphs/shortest-paths/E_Labyrinth.cpp) | graphs/shortest-paths | reviewed |
| [E. Magikarp: Far From Home (cpp)](../../solutions/graphs/shortest-paths/E_Magikarp_Far_From_Home.cpp) | graphs/shortest-paths | reviewed |
| [graph subchain (python)](../../solutions/graphs/traversal/graph-subchain.py) | graphs/traversal | reviewed |
| [q6 (cpp)](../../solutions/graphs/shortest-paths/q6.cpp) | graphs/shortest-paths | reviewed |
| [q6 (python)](../../solutions/graphs/shortest-paths/q6.py) | graphs/shortest-paths | reviewed |

<!-- examples:end -->
