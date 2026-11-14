# Graph traversal with BFS and DFS

Visit every vertex reachable from a source exactly once by marking it when it is first discovered. BFS from a source gives unweighted shortest distances; DFS gives reachability, components, and a natural post-order.

## Recognition clues

- "Who can be reached from X", "how many groups/components", "is there a path", "minimum number of moves" with all moves costing the same.
- Relations given as pairs (friends, prerequisites, same row/column) that you can turn into edges, even when the statement never says "graph".
- Each component contributes independently to the answer, e.g. a factor of 2 per merge gives `2^(n - components)`.
- A graph with exactly `n` edges on `n` vertices (one cycle): peel degree-1 vertices with a queue until only the cycle remains, then BFS from the interesting vertices.
- Small `n` with "count all simple paths": backtracking DFS that unmarks a vertex on return.

## Invariant and variants

Mark on push, not on pop: once a vertex is marked, it is never enqueued again, so each vertex and edge is processed once. In BFS, vertices leave the queue in non-decreasing distance, so `dist[v] = dist[u] + 1` at first discovery is final.

```cpp
vector<int> dist(n + 1, -1);
queue<int> q; dist[s] = 0; q.push(s);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) if (dist[v] == -1) {
        dist[v] = dist[u] + 1; par[v] = u; q.push(v);
    }
}
```

| Variant | Repo idiom |
| --- | --- |
| Component count | loop over vertices, start a DFS/BFS from each unvisited one; answer often `components - 1` edges to add |
| Multi-source reachability | push every "free" start (zero prerequisites) first, then traverse |
| Path reconstruction | store `par[v]`, walk back from the target, reverse |
| Unicyclic graph | queue-based leaf peeling marks non-cycle vertices; compare two BFS distance arrays on cycle vertices |
| Simple-path enumeration | `visited[v] = true; recurse; visited[v] = false`, cap the count early |
| State-space search | BFS over `(vertex, extra state)` pairs with a set of visited states |

Complexity is `O(n + m)` with adjacency lists; `map`/`set` adjacency adds a log factor, and building edges from all pairs of points is `O(n^2)` before the traversal even starts.

## Common mistakes

- Marking visited when popping instead of when pushing: vertices are enqueued many times.
- Using a plain FIFO queue when some transitions cost 0 and others cost 1 (staying on a route vs. switching): this is no longer plain BFS; use 0-1 BFS with a deque (see [shortest paths](shortest-paths.md)).
- Recursive DFS on `2e5`-deep paths can overflow the stack; use an explicit stack or BFS for reachability.
- Exhaustive path DFS without a visited guard loops forever on cycles.
- Comparing paths as strings of one character per vertex breaks for multi-digit labels.
- Forgetting the case `source == target` or a target never reached (print `-1`).
- Directed vs. undirected: adding only `u -> v` when the relation is symmetric, or both when it is not.

## Related patterns

[Grid traversal](grid-traversal.md) is the same search with implicit neighbours. [Shortest paths](shortest-paths.md) generalises BFS to weights. [DSU variants](dsu-variants.md) answer static connectivity without traversal. [Topological sort](topological-sort.md) and [tree DFS](tree-dfs.md) specialise traversal to DAGs and trees; exhaustive path search is [backtracking](backtracking-recursion.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [B DZY Loves Chemistry (cpp)](../../solutions/graphs/traversal/B_DZY_Loves_Chemistry.cpp) | graphs/traversal | reviewed |
| [C - New Skill Acquired (cpp)](../../solutions/graphs/traversal/C_New_Skill_Acquired.cpp) | graphs/traversal | reviewed |
| [C. Group Movie Night (cpp)](../../solutions/graphs/traversal/C_Group_Movie_Night.cpp) | graphs/traversal | reviewed |
| [cf iceskating (cpp)](../../solutions/graphs/traversal/cf-iceskating.cpp) | graphs/traversal | reviewed |
| [graph subchain (python)](../../solutions/graphs/traversal/graph-subchain.py) | graphs/traversal | reviewed |
| [H. Mad City (cpp)](../../solutions/graphs/traversal/H_Mad_City.cpp) | graphs/traversal | reviewed |
| [I Count Simple Paths (cpp)](../../solutions/graphs/traversal/I_Count_Simple_Paths.cpp) | graphs/traversal | reviewed |
| [longest path (cpp)](../../solutions/graphs/traversal/longest_path.cpp) | graphs/traversal | reviewed |
| [Minimum maximum on the Path (cpp)](../../solutions/binary-search/Minimum_maximum_on_the_Path.cpp) | binary-search | reviewed |
| [q6 (cpp)](../../solutions/graphs/shortest-paths/q6.cpp) | graphs/shortest-paths | reviewed |
| [q6 (python)](../../solutions/graphs/shortest-paths/q6.py) | graphs/shortest-paths | reviewed |

<!-- examples:end -->
