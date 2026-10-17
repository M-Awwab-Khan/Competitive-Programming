# Div. 3 speed programming: compact contest sheet

**[Full guide, assumptions, and code](div3-speed-programming.md)** · **[Copy-ready C++17 header](../../templates/cpp/sp-reference.hpp)** · **[Pattern hub](../patterns/INDEX.md)**

Preparation priorities are tailored suggestions. Follow the actual contest's scoring, reference rules, and language support. Use this as a lookup sheet; use the full guide to check assumptions.

## Before coding

Read constraints and **sum of input sizes** → identify the pattern → state the invariant → estimate cost → code → test extremes. Scan for quick wins and switch problems when an idea stalls.

Rough approach selection: `n<=20`: subsets; `n≈40`: meet in the middle; `n≈2000`: quadratic; `n≈2e5`: linear/log-linear. Constants, state dimensions, and time limits matter. `long long` array: about `8n` bytes.

## Pattern lookup

| Clue | Try |
| --- | --- |
| Static range sum/XOR | Prefix sums/XOR; `[l,r)` = `P[r]-P[l]` / `P[r]^P[l]` |
| Range additions, final values | Difference array: inclusive `[l,r]` → `D[l]+=x`, `D[r+1]-=x` |
| Target subarray sum, negatives allowed | Prefix-frequency map; count `P-k` **before** adding `P` |
| Longest target subarray | Earliest index of each prefix |
| Exactly `k` distinct | `atMost(k)-atMost(k-1)` |
| Sorted pair sum | Two pointers; compare sums in a wide type |
| Positive/nonnegative sum window | Sliding window; signs matter |
| Moving minimum/maximum | Monotonic deque of **indices** |
| Minimize maximum / maximize minimum | Binary search a **monotone** feasibility predicate |
| Minimum sum of absolute distances | Median; weighted median if weighted |
| Non-overlapping intervals, maximize count | Earliest finish first; not the weighted variant |
| Connectivity under merges | DSU |
| Minimum number of unit-cost moves | BFS; encode the full state |
| Nonnegative weighted distances | Dijkstra; discard stale heap entries |
| Repeated choices with small capacity | Knapsack / DP |
| Small sequence of take-away moves | Winning/losing-state DP, then prove any guessed pattern |

## C++ and numeric traps

- `using ll=long long; using i128=__int128_t;`; promote before multiplying: `(i128)a*b`.
- `accumulate(begin,end,0LL)`. Use integer literals such as `1'000'000'007LL`.
- Nonnegative ceiling, `a>=0,b>0`: `a/b+(a%b!=0)`. C++ signed `/` truncates toward zero.
- Normalize modulo: `a%=m; if(a<0)a+=m`, for positive `m`.
- Sorted vector: `lower_bound` = first `>=x`; `upper_bound` = first `>x`.
- Use `set.lower_bound`, not generic `lower_bound` on set iterators.
- `multiset.erase(x)` erases **all** equal values; erase an iterator to remove one.
- Comparators use strict ordering. Guard empty containers and `.end()`.
- Large DFS chains can overflow the stack. Reset per-test state.
- Use `'\n'`; flush only when needed. Remove local `freopen` before submission.

## Search, DP, and data structures

**First true:** candidates `[lo,hi)`, false→true; while `lo<hi`, use lower midpoint; true→`hi=mid`, false→`lo=mid+1`. Original `hi` is the no-answer sentinel. Derive a representable bound.

**Last true:** inclusive `[lo,hi]`, true→false, and `good(lo)` must hold. Use upper midpoint; true→`lo=mid`, false→`hi=mid-1`.

**DP:** define state/base/transition/order. Nonempty Kadane starts with `a[0]`; zero initialization permits an empty subarray. Strict LIS uses `lower_bound`; nondecreasing uses `upper_bound`.

| DP task | Loop rule |
| --- | --- |
| 0–1 knapsack/subset sum | Items outside, capacity descending |
| Unlimited item reuse | Items outside, capacity ascending |
| Count unordered coin combinations | Coins outside, sum ascending; `ways[0]=1` |
| Count ordered coin sequences | Sum outside, coins inside; `ways[0]=1` |
| Exact-weight maximum value | Unreachable states start at negative infinity |

Fenwick: point add, prefix/range sum in `O(log n)`. Segment tree: associative range operations, correct identity/merge. Standard DSU supports merges, not deletions. A heap gives repeated min/max extraction. The full guide/header supplies implementations with consistent indexing.

## Arithmetic and number theory

| Formula | Result / conditions |
| --- | --- |
| `1+...+n` | `n(n+1)/2` |
| `1^2+...+n^2` | `n(n+1)(2n+1)/6` |
| `1^3+...+n^3` | `[n(n+1)/2]^2` |
| Arithmetic progression | `n(first+last)/2` |
| Geometric progression | `a(r^n-1)/(r-1)`, `r!=1`; else `an` |
| Multiples of positive `k` in closed `[L,R]` | `floor(R/k)-floor((L-1)/k)`; use wide floor division |
| Positive-value LCM | `(a/gcd(a,b))*b`; product can still overflow |
| `n=product(p^e)` divisor count / sum | `product(e+1)` / `product(1+p+...+p^e)` |
| Exponent of prime `p` in `n!` | `sum(floor(n/p^j))` |
| Modular inverse | Exists iff `gcd(a,m)=1`; prime `p`: `a^(p-2)` only for `a%p!=0` |
| `ax+by=c` | Solvable iff `gcd(abs(a),abs(b))` divides `c`; handle `a=b=0` |
| All numbers equal modulo `k` | `k` divides every difference from a reference value |

`0,1` are not primes. Trial division tests `d<=n/d`; avoid overflowing `d*d`. Use SPF for many small factorizations. Do not divide modulo a number without an inverse. Exact square tests correct a square-root estimate with integer arithmetic.

## Counting

- Unordered pairs: `n(n-1)/2`. Nonempty subarrays: `n(n+1)/2`.
- Equal-value pairs for frequency `c`: `c(c-1)/2`.
- Choose: `C(n,k)=n!/[k!(n-k)!]`. Mod-prime factorial inverses need precomputed `n<p`.
- Strings: `q^k`. Subsets: `2^n`. Multiset permutations: `n!/product(c_i!)`.
- `n` identical objects, `k>=1` labeled boxes: `C(n+k-1,k-1)` allowing zero; `C(n-1,k-1)` requiring positive counts and `n>=k`.
- Grid paths with `r` right and `d` down steps, no obstacles: `C(r+d,r)`.
- Rectangles in an `r x c` cell grid: `C(r+1,2)*C(c+1,2)`.
- Sum of all subarray sums: `sum(a[i]*(i+1)*(n-i))`.
- `E[sum X_i]=sum E[X_i]` without independence. Probabilities multiply directly only when independent.

## Bits and strings

Use `1ULL<<b`, `0<=b<64`. Guard zero before GCC `clz/ctz`.

- Positive power of two: `x && !(x&(x-1))`. Remove lowest set bit: `x&=x-1`.
- XOR cancels pairs. XOR `0..n`, by `n%4`: `n,1,n+1,0`.
- Bit `b` set in `c` of `n` values: XOR unordered-pair contribution `c(n-c)2^b`.
- MEX of `n` values is in `[0,n]`; it starts at zero.
- A multiset can form a palindrome iff at most one character count is odd.
- Regular `()` sequence: no negative prefix balance, final balance zero.
- Subsequence skips elements; substring is contiguous. Use KMP/Z if naive repeated matching is too slow.

## Geometry: coordinate essentials

Let `u=B-A`, `v=C-A`. Promote differences and products before evaluating.

| Quantity | Formula |
| --- | --- |
| Distance squared / Manhattan / king distance | `dx^2+dy^2` / `abs(dx)+abs(dy)` / `max(abs(dx),abs(dy))` |
| Dot / cross | `ux*vx+uy*vy` / `ux*vy-uy*vx` |
| Orientation | Sign of cross; positive = counterclockwise in Cartesian coordinates |
| Triangle area | `abs(cross)/2` |
| Simple polygon area | `abs(sum(x_i*y_(i+1)-y_i*x_(i+1)))/2`, vertices in boundary order |
| Point-line distance | `abs(a*x+b*y+c)/sqrt(a^2+b^2)`, nondegenerate line |
| Nearest point on segment `AB` | Clamp `dot(P-A,B-A)/dot(B-A,B-A)` to `[0,1]`; handle `A=B` |
| Segment intersection | Orientation tests **plus** endpoint/collinear bounding-box cases |
| Lattice points on a distinct-endpoint segment | `gcd(abs(dx),abs(dy))+1` |
| Simple lattice polygon, no holes | `I=area-B/2+1`; boundary `B=sum(gcd(abs(dx),abs(dy)))` |
| Rectangle overlap width | `max(0,min(rights)-max(lefts))`; multiply by overlap height |

Geometric lengths have no `+1`; inclusive integer-point counts may. Grid rows often grow downward, reversing visual orientation. Keep doubled areas exact. For floating geometry use radians, clamp `acos`, and choose tolerances for the scale.

## Geometry: shapes

| Shape / quantity | Formula / condition |
| --- | --- |
| Triangle sides `a<=b<=c` | Valid iff `a>0` and `a+b>c`; right iff `a^2+b^2=c^2` |
| Heron | `s=(a+b+c)/2`; area `sqrt(s(s-a)(s-b)(s-c))` |
| Triangle area with included angle | `ab*sin(C)/2` |
| Triangle inradius / circumradius | `area/s` / `abc/(4*area)` |
| Equilateral height / area | `sqrt(3)*a/2` / `sqrt(3)*a^2/4` |
| Circle circumference / area | `2*pi*r` / `pi*r^2` |
| Arc length / sector area | `r*theta` / `r^2*theta/2`, radians |
| Chord | `2r*sin(theta/2)` |
| Trapezoid area | `(a+b)*height/2` for parallel sides `a,b` |
| Regular `n`-gon area | `n*a^2/(4*tan(pi/n))` |
| Cuboid volume / surface | `abc` / `2(ab+bc+ca)` |
| Cylinder volume / total surface | `pi*r^2*h` / `2*pi*r*(r+h)` |
| Cone volume / total surface | `pi*r^2*h/3` / `pi*r*(r+sqrt(r^2+h^2))` |
| Sphere volume / surface | `4*pi*r^3/3` / `4*pi*r^2` |

Two circles: compare center distance `d` with `r+R` and `abs(r-R)`; equal centers/equal radii mean coincident circles. Full guide includes overlap area and degeneracies.

## Last 30 seconds before submit

Test `n=1`, equality boundaries, all equal, all negative, zeros, duplicates, impossible answers, and large products. Recheck test-count, indexing, output format, overflow, loop direction, reset state, and total complexity. A sample match is not a correctness proof.
