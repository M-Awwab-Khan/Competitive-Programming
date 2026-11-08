# Geometry predicates

Answer geometric questions with exact integer primitives: cross product for orientation, dot product for angles, squared distances for comparisons, and per-axis `max(0, min - max)` overlaps for rectangles. Reach for floating point only when the output itself is real-valued.

## Recognition clues

- "Is the point left, right, or on the line?", "do the segments intersect?", "are these points collinear?"
- Areas of polygons, triangles, or rectangle unions and intersections.
- Axis-aligned rectangles: overlap, coverage, visible area.
- Comparing distances or checking orthogonality with integer coordinates.
- Angular sweeps around an origin: sort points by polar angle and binary search ranges.
- "Smallest circle containing all points".

## Invariant and variants

```cpp
long long cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }
// > 0: b is left of o->a (counter-clockwise), < 0: right, == 0: collinear
```

| Primitive | Formula | Repo illustration |
| --- | --- | --- |
| Orientation | sign of `cross(p1, p2, p3)` | `A_Point_Location_Test.cpp` |
| Collinear grouping | `cross == 0` with the shared origin | `B_Han_Solo_and_Lazer_Gun.cpp` |
| Segment intersection | `o1 != o2 && o3 != o4`, or a collinear endpoint inside the other segment's bounding box | `B_Line_Segment_Intersection.cpp` |
| Polygon area | shoelace `sum x_i y_{i+1} - x_{i+1} y_i`, absolute value is twice the area | `D_Polygon_Area.cpp` |
| Rectangle overlap | `max(0, min(r1, r2) - max(l1, l2))` per axis, multiply | `Problem_1_Blocked_Billboard.cpp`, `C_White_Sheet.cpp` |
| Orthogonality | dot product equals zero | `E_Orthogonality.cpp` |
| Distance comparisons | compare squared distances in integers | `A_Maximum_Distance.cpp` |
| Reflection trick | path touching a line equals the straight distance to the mirrored point | `D_Min_Path.cpp` |
| Angular sweep | sort `atan2` angles, count with `lower_bound`/`upper_bound`, split on wraparound | `E_Laser_Takahashi.cpp`, `coverdrive.py` |

### Minimum enclosing circle

Shuffle the points, then grow the circle incrementally: if point `i` is outside, rebuild with `i` on the boundary; if `j` is also outside, rebuild with `i` and `j`; if `k` is outside, use the circumcircle of `i, j, k`. Expected `O(n)` after the random shuffle (`E_The_Circle.cpp`, Welzl-style). Compare with a small epsilon, because every circle is computed in floating point.

Predicates are `O(1)`; area and sweeps are `O(n)` or `O(n log n)`.

## Common mistakes

- Using floating point for orientation tests on integer input. `B_Line_Segment_Intersection.cpp` uses `long double` with `1e-9`; integer `long long` arithmetic is exact (switch to `__int128` once coordinates exceed about `1e9`).
- Overflow: cross products with coordinates up to `1e9` reach about `4e18`, close to the `long long` limit.
- Floating `atan2` angles making collinear points compare unequal (`E_Laser_Takahashi`); compare by half-plane plus cross product for exact angular order.
- Floating `sqrt`/`ceil` when counting lattice points near a circle boundary (`D_Circle_Lattice_Points.py`).
- Forgetting the collinear-overlap case in segment intersection, or the wraparound range in angular sweeps.
- A greedy nearest-neighbour pairing is not a minimum-total matching (`quiz_forming_teams.py`).

## Related patterns

Many axis-aligned problems are really [closed-form arithmetic](closed-form-arithmetic.md). Angular and interval sweeps use [interval scheduling and sweep](interval-scheduling-and-sweep.md) and [sorted lookup](sorted-lookup.md). Real-valued radius searches use [binary search on the answer](binary-search-on-answer.md) or [ternary search](ternary-search.md). Direction normalisation by gcd is in [gcd and lcm](gcd-lcm.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A - Point Location Test (cpp)](../../solutions/geometry/A_Point_Location_Test.cpp) | geometry | reviewed |
| [A. Maximum Distance (cpp)](../../solutions/geometry/A_Maximum_Distance.cpp) | geometry | reviewed |
| [B - Line Segment Intersection (cpp)](../../solutions/geometry/B_Line_Segment_Intersection.cpp) | geometry | reviewed |
| [B Amr and Pins (cpp)](../../solutions/geometry/B_Amr_and_Pins.cpp) | geometry | reviewed |
| [B Han Solo and Lazer Gun (cpp)](../../solutions/geometry/B_Han_Solo_and_Lazer_Gun.cpp) | geometry | reviewed |
| [B. Fear of the Dark (cpp)](../../solutions/binary-search/B_Fear_of_the_Dark.cpp) | binary-search | reviewed |
| [Blocked Billboard II (cpp)](../../solutions/geometry/Blocked_Billboard_II.cpp) | geometry | reviewed |
| [C. White Sheet (cpp)](../../solutions/geometry/C_White_Sheet.cpp) | geometry | reviewed |
| [coverdrive (python)](../../solutions/geometry/coverdrive.py) | geometry | reviewed |
| [coverdrive2 (python)](../../solutions/geometry/coverdrive2.py) | geometry | reviewed |
| [D - Polygon Area (cpp)](../../solutions/geometry/D_Polygon_Area.cpp) | geometry | reviewed |
| [D. Min Path (cpp)](../../solutions/geometry/D_Min_Path.cpp) | geometry | reviewed |
| [D. Rudolph and Christmas Tree (cpp)](../../solutions/geometry/D_Rudolph_and_Christmas_Tree.cpp) | geometry | reviewed |
| [E - Laser Takahashi (cpp)](../../solutions/geometry/E_Laser_Takahashi.cpp) | geometry | reviewed |
| [E - Laser Takahashi (python)](../../solutions/geometry/E_Laser_Takahashi.py) | geometry | reviewed |
| [E - The Circle (cpp)](../../solutions/geometry/E_The_Circle.cpp) | geometry | reviewed |
| [E Orthogonality (cpp)](../../solutions/geometry/E_Orthogonality.cpp) | geometry | reviewed |
| [Problem 1. Blocked Billboard (cpp)](../../solutions/geometry/Problem_1_Blocked_Billboard.cpp) | geometry | reviewed |
| [quiz forming teams (python)](../../solutions/greedy/quiz_forming_teams.py) | greedy | reviewed |

<!-- examples:end -->
