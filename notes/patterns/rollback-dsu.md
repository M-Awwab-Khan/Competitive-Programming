# Rollback DSU and offline connectivity

A DSU that can undo its most recent unions. Undo makes deletions and range restrictions manageable offline: add edges on the way down a recursion and roll them back on the way out.

## Recognition clues

- Operations "save state" / "roll back to the last save" on a union-find.
- Edges are both added and removed, and the queries can be read in advance (dynamic connectivity offline).
- Connectivity queries over a range of edges `[l, r]` ("components using only edges l..r").
- Any divide and conquer or tree walk where a child adds unions that the parent must not keep.

## Invariant

Undo works only in stack order, so record every successful union and never change the structure in any other way:

```cpp
int find(int x) { while (parent[x] != x) x = parent[x]; return x; }   // no path compression
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;                       // nothing to undo, push nothing
    if (sz[a] < sz[b]) swap(a, b);
    history.push_back({b, sz[a]});            // child root, old size of new root
    parent[b] = a; sz[a] += sz[b]; components--;
}
void rollbackTo(int snapshot) {               // snapshot = history.size() saved earlier
    while ((int)history.size() > snapshot) {
        auto [b, oldSize] = history.back(); history.pop_back();
        sz[parent[b]] = oldSize; parent[b] = b; components++;
    }
}
```

Union by size keeps depth `O(log n)`, so `find` is `O(log n)` without compression.

| Variant | Idea |
| --- | --- |
| Persist / rollback | Push `history.size()` as a checkpoint; roll back to the top checkpoint. |
| Offline dynamic connectivity | Each edge is alive on a time interval `[added, removed - 1]`. Insert it into the `O(log q)` segment-tree nodes covering that interval. DFS the tree over time: unite a node's edges, recurse, answer at leaves, roll back. `O(q log q log n)`. |
| Components on edge ranges `[l, r]` | Sort queries by the block of `l` (block size `B ≈ sqrt(m)`), then by `r`. Queries inside one block are brute forced. For the others, extend a persistent right part from the block end as `r` grows, add edges `l..blockEnd` on top, answer, and roll back that left part. `O((m + q) sqrt(m) log n)`. |

## Common mistakes

- Using path compression: it rewrites parents that the history does not record, so undo corrupts the structure.
- Pushing history for a union that merged nothing, or forgetting to push one that did; checkpoints then point to the wrong state.
- Restoring the wrong size: save the surviving root's size before adding, and restore it at `parent[child]` before resetting the child.
- Adding the wrong size (`sz[a] += b` instead of `sz[a] += sz[b]`). Answers can still be right, but union by size stops bounding the depth.
- In time-segment trees, an edge removed at time `i` is alive until `i - 1`; edges never removed stay alive until the last query.
- Re-adding an edge that is already alive overwrites its start time in a `map`; check whether the problem allows duplicates.

## Related patterns

The base structure is in [DSU variants](dsu-variants.md). The time tree is a [range query structure](range-query-structures.md) used for [divide and conquer](divide-and-conquer.md); the edge-range version sorts queries by block. Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [DSU with rollback (cpp)](../../solutions/data-structures/disjoint-set/DSU_with_rollback.cpp) | data-structures/disjoint-set | reviewed |
| [Dynamic Connectivity Offline (cpp)](../../solutions/data-structures/disjoint-set/Dynamic_Connectivity_Offline.cpp) | data-structures/disjoint-set | reviewed |
| [Number of Connected Components on Segments (cpp)](../../solutions/data-structures/disjoint-set/Number_of_Connected_Components_on_Segments.cpp) | data-structures/disjoint-set | reviewed |

<!-- examples:end -->
