# Grid traversal and neighbourhood scans

Treat each cell as a vertex whose neighbours come from a direction array. The same loop drives flood fill, grid BFS shortest paths, neighbour counting (minesweeper), attack rays, and ring-by-ring walks.

## Recognition clues

- Input is a character matrix with walls (`#`), floor (`.`), mines (`*`), or pieces.
- "Count rooms/islands", "shortest path from A to B and print the moves", "keep the remaining cells connected".
- Each cell's value depends on its 4 or 8 neighbours.
- Chess pieces that attack along rays until blocked.
- Spiral or layer-by-layer reading of a matrix.
- Adjacent cells must differ: colour by `(i + j) % 2`.

## Invariant and variants

Keep one `inBounds(x, y)` test and one direction table; every variant is a loop over it.

```cpp
int dx[] = {0, 1, -1, 0}, dy[] = {1, 0, 0, -1};  char dc[] = {'R','D','U','L'};
for (int k = 0; k < 4; ++k) {
    int nx = x + dx[k], ny = y + dy[k];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#' || vis[nx][ny]) continue;
    vis[nx][ny] = 1; how[nx][ny] = dc[k]; q.push({nx, ny});
}
```

| Variant | Key decision |
| --- | --- |
| Flood fill / room count | each unvisited floor cell starts a new BFS/DFS |
| BFS path with moves | store the move letter per cell; walk back from the target undoing moves, then reverse |
| Keep `s - k` cells connected | DFS from any free cell and stop after `s - k` visits; unvisited free cells can be walled since the visited set is connected |
| 8-neighbour counts | `for dx in -1..1, dy in -1..1, skip (0,0)` |
| Rays (rook/bishop/queen) | step in a direction until out of bounds or the first occupied square, inclusive |
| Checkerboard colouring | colour depends only on `(i + j)` parity, so no search is needed |
| Spiral / layer walk [variant] | shrink `top, bottom, left, right` after each ring; for a cyclic pattern search, append the first `len - 1` characters of the ring |

Complexity is `O(nm * directions)`.

## Common mistakes

- Storing the whole path string in every queue entry: `O(nm * path length)` memory/time. Store one parent move per cell instead.
- Swapping row/column deltas so that `'U'` moves down when reconstructing.
- Recursive flood fill on a `1000 x 1000` grid overflowing the stack.
- Forgetting newlines between printed rows.
- In ring walks, double-counting corners or mishandling a single remaining row/column.
- Pawn direction depends on colour; ray marking must stop at, but include, the blocking piece.

## Related patterns

This is [graph BFS/DFS](graph-bfs-dfs.md) with implicit edges. Weighted moves need [shortest paths](shortest-paths.md); counting monotone paths is [grid path DP](grid-path-dp.md). Checkerboard arguments are [parity and invariants](parity-and-invariants.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [C - Counting Rooms (cpp)](../../solutions/graphs/traversal/C_Counting_Rooms.cpp) | graphs/traversal | reviewed |
| [E - Labyrinth (cpp)](../../solutions/graphs/shortest-paths/E_Labyrinth.cpp) | graphs/shortest-paths | reviewed |
| [I Maze (cpp)](../../solutions/graphs/traversal/I_Maze.cpp) | graphs/traversal | reviewed |
| [ilove1543 (python)](../../solutions/simulation/ilove1543.py) | simulation | reviewed |
| [minesweeper (python)](../../solutions/simulation/minesweeper.py) | simulation | reviewed |
| [minesweeper 2 (python)](../../solutions/simulation/minesweeper%202.py) | simulation | reviewed |
| [uva chessboardFEN (cpp)](../../solutions/simulation/uva-chessboardFEN.cpp) | simulation | reviewed |
| [uva minesweeper (cpp)](../../solutions/simulation/uva-minesweeper.cpp) | simulation | reviewed |
| [uva minesweeper 10279 (cpp)](../../solutions/simulation/uva-minesweeper-10279.cpp) | simulation | reviewed |

<!-- examples:end -->
