# Div. 3 speed programming: preparation and contest reference

**[Compact contest sheet](quick-reference.md)** · **[Copy-ready C++ header](../../templates/cpp/sp-reference.hpp)** · **[Pattern notes](../patterns/INDEX.md)** · **[Repository guide](../../README.md)**

Scope: a broad working reference for a contest around Codeforces Div. 3 difficulty, including later problems. The priority labels below are a preparation recommendation, not a guarantee about an unknown contest. Contest-specific time limits, scoring, language support, and reference-material rules take precedence. The code uses GNU C++17; `bits/stdc++.h` and `__int128` are GNU extensions.

Use the compact sheet during timed practice. Use this document to fill gaps, and follow the existing pattern notes for deeper explanations. Original snippets are collected into the linked header; they do not certify the correctness of historical solutions linked as examples.

## Contents

- [Contest flow and complexity](#contest-flow)
- [Recognizing the pattern](#recognition)
- [C++ survival kit](#cpp)
- [Arrays, sorting, greedy, and constructions](#arrays)
- [Prefix sums and differences](#prefix)
- [Two pointers and sliding windows](#windows)
- [Binary search on the answer](#binary-search)
- [Strings and brackets](#strings)
- [Bit manipulation](#bits)
- [Arithmetic and number theory](#number-theory)
- [Combinatorics and probability](#counting)
- [Geometry formulas and predicates](#geometry)
- [Graphs, grids, and trees](#graphs)
- [Dynamic programming](#dp)
- [Data structures](#structures)
- [Enumeration, games, and cycles](#extras)
- [Failure checklist](#debugging)
- [Preparation route using this repo](#practice)
- [External references](#references)

<a id="contest-flow"></a>
## Contest flow and complexity

**First priority:** arithmetic, implementation, strings, counting, sorting, greedy, prefix sums, two pointers, binary search, and basic graph search. **Next:** elementary DP, GCD/factorization, bit operations, geometry predicates, DSU, heaps, Fenwick trees. **Later-problem backup:** segment trees, Dijkstra, topological order, LIS, subset enumeration, meet in the middle, and interval DP.

At the start, scan statements for quick wins; read input/output and constraints before coding. For each problem, write the invariant or formula, estimate complexity across **all test cases**, and then implement. If stuck, try a tiny example, a brute force, the complement, or sorting. Switching to another solvable problem is often better than repeatedly rewriting an unsupported idea.

These are rough C++ feasibility guides, not timing promises:

| Input scale | Candidate approach to consider |
| --- | --- |
| `n <= 9` | Permutations or deep brute force; still count states |
| `n <= 20` | `O(2^n)` or `O(n * 2^n)` |
| `n` around 40 | Meet in the middle, roughly `2^(n/2)` states per half |
| `n <= 400` | `O(n^3)` may fit, depending on constants/time limit |
| `n <= 2,000` | `O(n^2)` |
| `n <= 200,000` | Usually `O(n log n)` or `O(n)` |
| `n` around one million | Aim for linear or very efficient near-linear work |
| Values up to `10^18` | Formulas, logarithmic search, bit reasoning; avoid value-sized arrays |

`sum(n) <= 2e5` differs from `n <= 2e5` for each of many tests. Estimate the **sum of costs**, not just the largest single cost. A `long long[n]` array uses approximately `8n` bytes, excluding container overhead. A `2000 x 2000` table of `long long` is about 32 MB. A million graph vectors have substantial overhead even before storing edges.

<a id="recognition"></a>
## Recognizing the pattern

| Wording or structure | First thing to try | Required condition / warning |
| --- | --- | --- |
| Static interval sums or XOR | Prefix aggregates | Sum/XOR can be inverted; arbitrary interval minima cannot |
| Many additions to intervals, final array only | Difference array | Mark both boundaries, then take a prefix sum |
| Count subarrays with sum `k`, including negatives | Prefix state frequency map | Query previous states before inserting current state |
| Count subarrays with exactly `k` distinct values | `atMost(k) - atMost(k-1)` | Maintain a valid window and frequencies |
| Sorted pair sum or triangle count | Opposite-end pointers | Prove how changing each pointer changes the condition |
| Longest/shortest feasible contiguous range | Sliding window | Feasibility must support monotone movement of boundaries |
| Minimize maximum / maximize minimum | Binary search + feasibility check | Candidate feasibility must be monotone |
| Minimize sum of absolute deviations | Median; weighted median if weighted | No extra constraints on the chosen center |
| Choose many non-overlapping activities | Sort by finishing time | The unweighted interval scheduling problem |
| K best values or repeated minimum extraction | Heap | Keep the correct heap direction |
| Range maximum/minimum over moving window | Monotonic deque | Indices expire; compare values for domination |
| Point updates + prefix/range sum | Fenwick tree | Standard sum version does not directly do arbitrary min queries |
| Dynamic range min/sum/custom associative operation | Segment tree | Correct identity and merge; updates may require lazy propagation |
| Minimum edges/moves in an unweighted state graph | BFS | A state must contain everything affecting future moves |
| Edge weights only `0/1` | 0–1 BFS | Relax distances; ordinary visited-on-insert BFS is insufficient |
| Nonnegative weighted shortest path | Dijkstra | Negative edges invalidate the algorithm |
| Connectivity under merges or threshold | DSU, perhaps inside binary search | DSU alone does not recover paths or support deletions |
| Choose/take/skip with a small capacity | Knapsack DP | State count matters; capacity direction controls reuse |
| Repeated overlapping subproblems | DP/memoization | Define state meaning, base case, and transition order |
| Construct a permutation/arrangement | Small examples, parity, extremes, reverse, rotate | Verify the entire condition, not only the sample |
| Repeated operations on huge integers | Invariants, periodicity, functional graph cycle | Small-case patterns need a proof before extrapolation |

The monotone pointer and search requirements are useful reading checkpoints. See [USACO's two-pointers module](https://usaco.guide/silver/two-pointers) and [binary-search module](https://usaco.guide/silver/binary-search).

<a id="cpp"></a>
## C++ survival kit

### Starter and numeric types

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

void solve() {
    // Read this problem's input and solve one case.
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;                 // REMOVE if there is no test-case count.
    while (t--) solve();
}
```

Marked snippets below assume those includes, `using namespace std`, `ll`, and `i128`. In the companion header they live in `namespace sp`, for example `sp::DSU` or `sp::power_mod`. For an online judge, paste the needed routines with their dependencies; the judge will not have this repository header. Regenerate the header after editing marked snippets with `python3 scripts/build_sp_reference.py`; use `--check` to verify synchronization.

- `int` is usually 32-bit; signed `long long` reaches about `9.22e18`. Signed overflow is undefined behavior.
- Promote **before** multiplying: `1LL * n * (n-1) / 2`; use `(i128)a*b` if the product can exceed 64 bits.
- `accumulate(a.begin(), a.end(), 0LL)` avoids an `int` accumulator.
- Write integer constants as `1'000'000'007LL`; `1e18` is a floating literal.
- Choose `INF` from the problem's bounds; `LLONG_MAX/4` is convenient only if all finite answers are smaller. Guard additions involving unreachable states.
- Prefer `long double` for accumulated geometry; use `acosl(-1.0L)` for pi. Clamp an `acos` input into `[-1,1]`.
- `'\n'` avoids an unnecessary flush; interactive protocols require deliberate flushing.
- Avoid `#define int long long` and macros named `sort`, `min`, or `max`; they obscure types and overloads.

### STL reminders

| Need | C++ |
| --- | --- |
| Sort ascending / descending | `sort(a.begin(),a.end())` / `sort(a.rbegin(),a.rend())` |
| First value `>= x` / `> x` in sorted vector | `lower_bound(...)` / `upper_bound(...)` |
| Number of values equal to `x` | `upper_bound(...) - lower_bound(...)` |
| Largest value `<= x` in a set | `auto it=s.upper_bound(x);` then check `it!=s.begin()` before `--it` |
| Remove one occurrence from multiset | `auto it=s.find(x); if(it!=s.end()) s.erase(it);` |
| Remove all occurrences | `s.erase(x)` |
| Deduplicate after sorting | `a.erase(unique(a.begin(),a.end()),a.end());` |
| Largest element first | `priority_queue<ll>` |
| Smallest element first | `priority_queue<ll,vector<ll>,greater<ll>>` |
| Reverse | `reverse(a.begin(),a.end())` |
| Parse a full line after `cin >>` | `getline(cin >> ws,s)` **only if leading whitespace/empty lines are irrelevant** |
| Next permutation | Sort first, then `do {...} while(next_permutation(...));` |

Use container member bounds on `set`/`map`: `s.lower_bound(x)` is logarithmic; the generic iterator algorithm can require linear iterator movement. `map` is ordered with logarithmic operations; `unordered_map` has expected constant-time operations, no sorted order, and potentially bad collision behavior. Inserting `mp[key]` creates a default value if absent. Do not dereference `.end()`, `.front()`, or `.back()` without a valid element. A comparator must be strict: `a < b`, never `a <= b` for equal values.

### Exact division and square root

For `a >= 0, b > 0`, `ceil(a/b) = a/b + (a%b != 0)` avoids overflow in `a+b-1`. C++ signed division truncates toward zero, not toward negative infinity.

<!-- snippet:integer-helpers -->
```cpp
inline ll ceil_nonnegative(ll a, ll b) { // a >= 0, b > 0
    return a / b + (a % b != 0);
}
inline i128 floor_div(i128 a, i128 b) { // b != 0; signed 64-bit inputs are safe
    i128 q = a / b, r = a % b;
    return q - (r != 0 && ((r < 0) != (b < 0)));
}
inline i128 ceil_div(i128 a, i128 b) {
    i128 q = a / b, r = a % b;
    return q + (r != 0 && ((r < 0) == (b < 0)));
}
inline ll integer_sqrt(ll x) { // x >= 0, returns floor(sqrt(x))
    ll r = (ll)sqrtl((long double)x);
    while ((i128)r * r > x) --r;
    while ((i128)(r + 1) * (r + 1) <= x) ++r;
    return r;
}
```

Do not extend the division helpers to signed 128-bit minimum divided by `-1`; that result is unrepresentable. Check a perfect square with `(i128)r*r == x`, not floating-point equality.

<a id="arrays"></a>
## Arrays, sorting, greedy, and constructions

### High-yield transformations

- Count frequencies when the exact order is irrelevant. For equal-value pairs, sum `c*(c-1)/2` over frequencies `c`.
- Sort to expose adjacent gaps, group equal values, pair small with large, or make feasibility monotone. Preserve original indices when the output needs them.
- Coordinate compression: sort distinct values; replace a value by its rank via `lower_bound`. This preserves order/equality, **not physical distances or numeric differences**.
- Replace values by differences if operations act on adjacent elements or range increments.
- Minimize the final answer by counting all possibilities minus forbidden ones when the complement is simpler.
- For a fixed number of chosen elements with additive scores, sort or keep a heap; interactions between selected elements may invalidate that shortcut.
- Minimum adjacent swaps to sort a permutation equals its inversion count; minimum unrestricted swaps equals `n - number_of_cycles`. Duplicates require care with the intended matching.
- To make all integers equal using transfers that preserve their sum, divisibility of the total by `n` is necessary. Whether it is sufficient depends on the allowed transfers.
- To make all numbers congruent modulo some positive `k`, `k` must divide every difference from one reference value. The largest such `k` is the GCD of those absolute differences; all equal values mean there is no finite largest modulus.
- `min_x sum(abs(a[i]-x))` is attained at a median; `min_x sum((a[i]-x)^2)` at the mean. For an integer `x` in the latter, compare floor/ceiling of the mean.

### Greedy checkpoints

| Task | Greedy choice | Why you should verify the model |
| --- | --- | --- |
| Maximize number of non-overlapping intervals | Earliest finishing interval next | Weighted rewards require a different method |
| Pair people with capacity, at most two per group | Heaviest remaining + lightest if they fit | The “two per group” restriction matters |
| Cover sorted points by minimum fixed-length intervals | Start at leftmost uncovered point | Assumes intervals can be freely placed |
| Minimum total waiting/completion time for jobs available now | Shortest processing time first | Release times/weights change the rule |
| Repeatedly merge two piles at cost equal to their sum | Merge the two smallest with a min-heap | Applies when any two piles can merge; adjacency constraints lead to interval DP |

An exchange argument or maintained invariant is better than “sorting worked on the samples.” For construction tasks, test `n=1`, `n=2`, odd/even cases, impossible parity, duplicate values, and endpoint constraints. Common constructions include alternating extremes, reversed blocks, cyclic shifts, pairs of equal values, and powers of two.

### MEX

The MEX is the smallest missing **nonnegative** integer. For an array of length `n`, its MEX lies in `[0,n]`.

<!-- snippet:mex -->
```cpp
inline int mex(const vector<ll>& a) {
    vector<char> seen(a.size() + 1, false);
    for (ll x : a) if (0 <= x && x <= (ll)a.size()) seen[(size_t)x] = true;
    int answer = 0;
    while (answer < (int)seen.size() && seen[answer]) ++answer;
    return answer;
}
```

<a id="prefix"></a>
## Prefix sums and differences

Use half-open ranges `[l,r)` consistently: `pref[0]=0`, `pref[i+1]=pref[i]+a[i]`, and `sum(l,r)=pref[r]-pref[l]`. Replace addition/subtraction by XOR/XOR for range XOR. Prefix minima alone cannot recover an arbitrary interval minimum.

For a rectangle `[r1,r2) x [c1,c2)` in a grid, with a leading zero row and column:

```text
P[r+1][c+1] = grid[r][c] + P[r][c+1] + P[r+1][c] - P[r][c]
rectangle = P[r2][c2] - P[r1][c2] - P[r2][c1] + P[r1][c1]
```

For adding `v` to inclusive `[l,r]`: allocate `diff[n+1]`, do `diff[l]+=v`, `diff[r+1]-=v`, then prefix-sum the differences. A 2D rectangle update uses four signed corner changes, followed by a 2D prefix sum. These are offline updates unless combined with an appropriate dynamic structure.

For target-sum counting, use `P[r]-P[l]=k`. For divisibility, equal normalized prefix remainders identify divisible subarrays. For digit subarrays where sum equals length, store `prefix_sum - prefix_length`. More derivation and the longest-subarray variant: [canonical prefix-map note](../patterns/prefix-sum-frequency-map.md). Static prefix query background: [USACO Guide](https://usaco.guide/silver/prefix-sums).

<!-- snippet:count-subarrays -->
```cpp
inline ll count_sum_k(const vector<ll>& a, ll k) { // prefix sums and prefix-k must fit ll
    map<ll, ll> frequency; // deterministic O(n log n); unordered_map is expected O(n)
    frequency[0] = 1;
    ll prefix = 0, answer = 0;
    for (ll value : a) {
        prefix += value;
        auto it = frequency.find(prefix - k);
        if (it != frequency.end()) answer += it->second;
        ++frequency[prefix];
    }
    return answer;
}
```

<a id="windows"></a>
## Two pointers and sliding windows

The key is that each pointer moves forward at most `n` times. Nested loops are still linear if the total pointer movement is linear.

For **nonnegative** elements, sums only increase when extending a window; this supports many sum-bound windows. With negative elements, shrinking after exceeding a threshold can skip valid answers. Use prefix maps or another structure instead. A fixed-length running sum works with either sign.

For sorted `a`, to count pairs `i<j` with `a[i]+a[j] <= X`: if the smallest and largest fit, the smallest fits with every index through the largest; otherwise reduce the largest endpoint. To count sums in `[L,R]`, subtract counts `<= R` and `< L`; avoid `L-1` when `L` is the minimum representable integer.

<!-- snippet:pair-count -->
```cpp
inline ll count_pairs_leq(vector<ll> a, ll limit) {
    sort(a.begin(), a.end());
    int l = 0, r = (int)a.size() - 1;
    ll answer = 0;
    while (l < r) {
        if ((i128)a[l] + a[r] <= limit) {
            answer += r - l;
            ++l;
        } else --r;
    }
    return answer;
}
```

For distinct-value windows, the condition “at most `k` distinct” is maintained by frequency counts, independently of numeric signs. Every suffix of a valid window ending at `r` is valid, so add `r-l+1`.

<!-- snippet:distinct-window -->
```cpp
inline ll at_most_distinct(const vector<ll>& a, int k) {
    if (k < 0) return 0;
    map<ll, int> frequency;
    ll answer = 0;
    int l = 0;
    for (int r = 0; r < (int)a.size(); ++r) {
        ++frequency[a[r]];
        while ((int)frequency.size() > k) {
            auto it = frequency.find(a[l++]);
            if (--it->second == 0) frequency.erase(it);
        }
        answer += r - l + 1;
    }
    return answer;
}
```

Exactly `k` distinct = `at_most_distinct(a,k)-at_most_distinct(a,k-1)`. This implementation is `O(n log n)` due to its map; a frequency array after compression or a suitable hash table reduces that overhead.

For a moving extremum, retain indices in a monotonic deque. The [canonical deque note](../patterns/monotonic-deque.md) explains domination and expiry.

<!-- snippet:window-maximum -->
```cpp
inline vector<ll> window_maximum(const vector<ll>& a, int k) {
    if (k <= 0 || k > (int)a.size()) return {};
    deque<int> q;
    vector<ll> result;
    for (int r = 0; r < (int)a.size(); ++r) {
        while (!q.empty() && q.front() <= r - k) q.pop_front();
        while (!q.empty() && a[q.back()] <= a[r]) q.pop_back();
        q.push_back(r);
        if (r + 1 >= k) result.push_back(a[q.front()]);
    }
    return result;
}
```

<a id="binary-search"></a>
## Binary search on the answer

Write the feasibility predicate in words first. “Can finish within time `x`” usually becomes easier as `x` grows; “can maintain a minimum gap `x`” usually becomes harder. Never binary-search a nonmonotone predicate. Derive bounds and the cost of one predicate evaluation. See the [canonical answer-search note](../patterns/binary-search-on-answer.md).

<!-- snippet:binary-search -->
```cpp
template<class Predicate>
ll first_true(ll lo, ll hi, Predicate good) {
    // Candidates [lo, hi), false -> true. Returns original hi if none.
    // Require 0 <= lo <= hi <= LLONG_MAX.
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (good(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
template<class Predicate>
ll last_true(ll lo, ll hi, Predicate good) {
    // Inclusive [lo, hi], true -> false. REQUIRE good(lo).
    // Require 0 <= lo <= hi <= LLONG_MAX.
    while (lo < hi) {
        ll gap = hi - lo;
        ll mid = lo + gap / 2 + gap % 2;
        if (good(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
```

To search integer values `0..U` with `first_true`, use `hi=U+1` if representable, then detect the sentinel. Avoid computing a gigantic total in `good`: stop once enough production is reached, or subtract each required resource from a remaining budget. Use `i128` for products such as `rate * time`.

For a continuous monotone threshold, repeat binary search for a fixed sufficient number of iterations and bound the final absolute error by initial width divided by `2^iterations`. For a **unimodal** objective, ternary search is an alternative; monotonicity and unimodality are different assumptions. Direct median/mean formulas can eliminate a search entirely.

<a id="strings"></a>
## Strings and brackets

- Frequency arrays of size 26 work only for the stated alphabet. Binary strings often reduce to counts, runs, transitions, or inversion-like pairs.
- A subsequence can skip positions; a substring is contiguous. Check a candidate subsequence with one pointer advancing through the target.
- A palindrome has matching symmetric positions. A multiset of characters can be permuted into a palindrome iff at most one frequency is odd.
- Minimum deletions to turn a string into a palindrome can require DP; it is not generally half the mismatched pairs.
- `s` can be split into repeated copies of a shorter string of length `p` iff `p` divides `n` and the repetition actually matches. For a prefix-function candidate, use `p=n-pi[n-1]` and check `n%p==0`.
- `string::find` returns `string::npos` on failure, not a guaranteed small signed `-1`. Repeated `erase` from the middle can make a solution quadratic.
- For matching or borders in linear time, know the prefix function; use KMP or Z when repeated searching becomes too expensive. Hash equality is probabilistic unless independently verified.

<!-- snippet:prefix-function -->
```cpp
inline vector<int> prefix_function(const string& s) {
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}
```

For `(` and `)`, set balance `+1/-1`. A regular bracket sequence has no negative prefix balance and finishes at zero. For multiple bracket types, use a stack. In a sequence containing `?`, assigning a valid balance needs more than checking that total length is even. For counting pairs of opposite binary values across positions, scan and maintain the number of earlier zeros or ones.

<a id="bits"></a>
## Bit manipulation

Use unsigned operands for masks where possible. For a 64-bit operand, shift counts must be in `[0,63]`; `1 << 40` is invalid for an ordinary 32-bit `int`. Use `1ULL << bit`. GCC `__builtin_clzll(0)` and `__builtin_ctzll(0)` are undefined: guard zero first. This is specified by the [GCC builtin reference](https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html).

| Operation / identity | Expression / result |
| --- | --- |
| Read / set / clear / toggle bit `b` | `(x>>b)&1`, `x\|(1ULL<<b)`, `x&~(1ULL<<b)`, `x^(1ULL<<b)` |
| Positive power of two | `x != 0 && (x & (x-1)) == 0` |
| Remove lowest set bit | `x &= x-1` |
| Isolate lowest set bit, for unsigned `x` | `x & (0ULL-x)` |
| Count set bits | `__builtin_popcountll(x)` |
| Highest set bit, `x>0` | `63 - __builtin_clzll(x)` |
| XOR cancellation | `a^a=0`, `a^0=a`; order does not matter |
| Addition decomposition | `a+b = (a^b) + 2*(a&b)` for nonnegative integers, ignoring machine overflow |
| XOR of `0..n`, by `n%4` | `n`, `1`, `n+1`, `0` |
| XOR inclusive `[l,r]` | `xor0(r) ^ xor0(l-1)`; handle `l=0` |
| AND bit contributes to a pair | Both numbers have it set |
| OR bit contributes to a pair | At least one number has it set |
| XOR bit contributes to a pair | Exactly one number has it set |

If bit `b` is set in `c` of `n` numbers, its contribution to the sum of XORs over **unordered distinct-index pairs** is `c*(n-c)*2^b`. For AND, it is `C(c,2)*2^b`; for OR, `[C(n,2)-C(n-c,2)]*2^b`. Use wide arithmetic or modular multiplication.

Enumerate all submasks of a mask, including zero:

```cpp
for (unsigned sub = mask; ; sub = (sub - 1) & mask) {
    // Process sub.
    if (sub == 0) break;
}
```

For `n` independent bits, all masks cost `2^n`; all `(mask,submask)` pairs cost `3^n` in total. Bitwise NOT flips every bit of the operand's type, so mask afterward if you intend only the lowest `b` bits.

<a id="number-theory"></a>
## Arithmetic and number theory

### Everyday formulas

| Quantity | Formula / condition |
| --- | --- |
| `1+...+n` | `n*(n+1)/2` |
| Sum of squares `1^2+...+n^2` | `n*(n+1)*(2n+1)/6` |
| Sum of cubes | `[n*(n+1)/2]^2` |
| Arithmetic progression, `n` terms | `n*(first+last)/2`; term `i` (zero-based) is `a+i*d` |
| Geometric progression, `n` terms | `a*(r^n-1)/(r-1)` for `r!=1`; otherwise `a*n` |
| Number of integers in closed `[L,R]` | `max(0,R-L+1)` when the expression fits |
| Multiples of positive `k` in `[L,R]` | `floor(R/k)-floor((L-1)/k)`; use mathematical floor and wide `L-1` |
| Next nonnegative increment making `a` a multiple of positive `k` | `(k - normalized_remainder(a,k)) % k` |
| Sum of decimal digits modulo 3 or 9 | Same remainder as the original nonnegative integer |
| Relative-motion meeting time | Distance / relative speed; decide integer strictness separately |
| Work done | Rate × time, provided the rate really is constant |

For exact rational comparisons with positive denominators, compare `a*d` with `c*b` in a sufficiently wide type. Percent increase by `p%` multiplies by `(100+p)/100`; consecutive percentage changes multiply and generally do not cancel. Exact fractional/integer algebra often avoids floating point.

Divisibility: by 2, last digit even; by 4 or 8, last two or three digits; by 5, last digit 0/5; by 3 or 9, digit sum; by 11, alternating digit sum is divisible by 11. Leading zeros do not change the integer, but may matter for string constructions.

### GCD, LCM, divisors, and primes

- `gcd(0,x)=abs(x)` and `gcd(0,0)=0`. Normal positive-value GCD is Euclid in logarithmic time.
- For positive `a,b`, `lcm(a,b)=(a/gcd(a,b))*b`; division first reduces, but does not eliminate, overflow. Cast to `i128` before the product. If either argument is zero, LCM is zero.
- For nonzero `n`, divisors occur in pairs `d` and `n/d`. Test `d <= n/d`, not an overflowing `d*d <= n`.
- `0` and `1` are not primes. Trial division is `O(sqrt(n))` and is unsuitable for many large inputs near `10^18`.
- If `n = product(p_i^e_i)`, divisor count is `product(e_i+1)`. Divisor sum is `product(1+p_i+...+p_i^e_i)`. A perfect square has an odd number of positive divisors.
- Euler's totient: `phi(n)=n*product(1-1/p)` over distinct prime divisors, for `n>=1`.
- Exponent of prime `p` in `n!`: `floor(n/p)+floor(n/p^2)+...`. Count factors by repeatedly dividing a quotient to avoid overflowing prime powers. Decimal trailing zeros in `n!` come from `p=5`.

The prime-factor formulas are checked against the focused [divisor reference](https://cp-algorithms.com/algebra/divisors.html).

<!-- snippet:factorization -->
```cpp
inline vector<pair<ll,int>> factorize(ll n) { // n >= 1, trial division
    vector<pair<ll,int>> result;
    for (ll p = 2; p <= n / p; ++p) {
        if (n % p != 0) continue;
        int exponent = 0;
        do { n /= p; ++exponent; } while (n % p == 0);
        result.push_back({p, exponent});
    }
    if (n > 1) result.push_back({n, 1});
    return result;
}
inline vector<int> smallest_prime_factors(int n) { // n >= 0
    vector<int> spf(n + 1);
    if (n >= 1) spf[1] = 1;
    for (int p = 2; p <= n; ++p) {
        if (spf[p] != 0) continue;
        spf[p] = p;
        if (1LL * p * p > n) continue;
        for (ll x = 1LL * p * p; x <= n; x += p)
            if (spf[(size_t)x] == 0) spf[(size_t)x] = p;
    }
    return spf;
}
```

This SPF sieve uses `O(n)` memory and `O(n log log n)` time. Once built, repeatedly divide by `spf[x]` to factor `x <= n` in at most `O(log x)` divisions. If only prime flags are needed, a boolean sieve uses less memory.

### Modular arithmetic

Normalize with `a%=m; if(a<0)a+=m` for positive `m`. Addition, subtraction, and multiplication respect congruences; ordinary division does not. `a` has an inverse modulo `m>1` iff `gcd(a,m)=1`. For **prime** `p`, a nonzero residue has inverse `a^(p-2) mod p`; do not use that formula for arbitrary composite moduli or `a%p==0`. See the [modular inverse reference](https://cp-algorithms.com/algebra/module-inverse.html).

<!-- snippet:modular-power -->
```cpp
inline ll power_mod(ll a, ll exponent, ll mod) { // exponent >= 0, mod >= 1
    a %= mod;
    if (a < 0) a += mod;
    ll result = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1) result = (ll)((i128)result * a % mod);
        a = (ll)((i128)a * a % mod);
        exponent >>= 1;
    }
    return result;
}
```

The geometric-sum closed form needs an invertible denominator when used modulo `m`. If `r-1` is not invertible, use another recurrence or a divide-and-conquer power/sum pair. Do not reduce an exponent modulo `p-1` without the appropriate nonzero/coprime assumptions.

### Equations and congruences

For integers `a,b,c`, `a*x+b*y=c` has integer solutions iff `gcd(abs(a),abs(b))` divides `c`, except handle `a=b=0` separately. Given one solution `(x0,y0)` and nonzero `g`, all solutions are `x=x0+(b/g)*t`, `y=y0-(a/g)*t`. Nonnegative/bounded solutions require additional bounds on `t`; signed floor/ceiling division matters. Focused reference: [linear Diophantine equations](https://cp-algorithms.com/algebra/linear-diophantine-equation.html).

A linear congruence `a*x ≡ b (mod m)` is solvable iff `gcd(a,m)` divides `b`. Two congruences `x≡a (mod m)`, `x≡b (mod n)` are compatible iff `a≡b (mod gcd(m,n))`; compatible solutions repeat modulo `lcm(m,n)`. For a quadratic `a*x^2+b*x+c=0`, check `a=0` first, then discriminant `b^2-4ac`; integer roots require an exact square and divisibility by `2a`. Use sufficiently wide intermediates.

<a id="counting"></a>
## Combinatorics and probability

| Object being counted | Formula / assumptions |
| --- | --- |
| Ordered arrangements of `n` distinct objects | `n!` |
| Choose `k` distinct objects without order | `C(n,k)=n!/[k!(n-k)!]`, zero if `k<0` or `k>n` |
| Ordered choice of `k` without repetition | `n!/(n-k)!` |
| Strings of length `k` from `q` symbols | `q^k` |
| Distinct permutations with repeated counts `c_i` | `n!/product(c_i!)` |
| All subsets / nonempty subsets | `2^n` / `2^n-1` |
| Unordered pairs of distinct indices | `n*(n-1)/2` |
| Contiguous nonempty subarrays | `n*(n+1)/2` |
| Sum over all subarray sums | `sum(a[i]*(i+1)*(n-i))` for zero-based `i` |
| Rectangles in an `r x c` cell grid | `C(r+1,2)*C(c+1,2)` |
| Axis-aligned squares in that grid | `sum((r-k+1)*(c-k+1))`, `k=1..min(r,c)` |
| Lattice paths with `r` right and `d` down steps, no obstacles | `C(r+d,r)` |
| Distribute `n` identical objects into `k>=1` labeled boxes, zeros allowed | `C(n+k-1,k-1)` |
| Same, each box positive | `C(n-1,k-1)`, provided `n>=k` |
| Circular arrangements of `n>=1` distinct objects, rotations identified | `(n-1)!`; reflections are a different equivalence |
| Correct bracket strings of length `2n` | Catalan `C(2n,n)/(n+1)` |

The labeled-box assumptions in [stars and bars](https://cp-algorithms.com/combinatorics/stars_and_bars.html) are essential. For lower bounds `x_i>=a_i`, subtract them first. Upper bounds need additional counting, often inclusion–exclusion. For two sets, `size(A∪B)=size(A)+size(B)-size(A∩B)`; for three, alternate signs over singles, pairs, and triple intersection.

Pascal recurrence `C(n,k)=C(n-1,k-1)+C(n-1,k)` avoids modular division and works with any positive modulus. Factorial/inverse-factorial preprocessing gives constant-time queries under the prime and size assumptions below.

<!-- snippet:combinations -->
```cpp
struct Combinations {
    ll prime;
    vector<ll> fact, inverse_fact;
    Combinations(int n, ll p) : prime(p), fact(n + 1, 1), inverse_fact(n + 1, 1) {
        // REQUIRE: p is prime, 0 <= n < p.
        for (int i = 1; i <= n; ++i) fact[i] = (ll)((i128)fact[i-1] * i % p);
        inverse_fact[n] = power_mod(fact[n], p - 2, p);
        for (int i = n; i >= 1; --i)
            inverse_fact[i-1] = (ll)((i128)inverse_fact[i] * i % p);
    }
    ll choose(int n, int k) const { // REQUIRE n <= precomputed limit
        if (n < 0 || k < 0 || k > n) return 0;
        return (ll)((i128)fact[n] * inverse_fact[k] % prime * inverse_fact[n-k] % prime);
    }
};
```

Probability for equally likely outcomes is favorable/total. `P(A∩B)=P(A)*P(B|A)`; multiply marginal probabilities only under independence. `P(A∪B)=P(A)+P(B)-P(A∩B)`. Linearity gives `E[sum X_i]=sum E[X_i]` even when variables are dependent. With independent trials of success probability `p>0`, expected trials through the first success are `1/p`. A modular probability is a residue using an inverse, not a decimal probability.

<a id="geometry"></a>
## Geometry formulas and predicates

### Coordinate tools

Let vectors `u=(ux,uy)`, `v=(vx,vy)`, and `cross(u,v)=ux*vy-uy*vx`.

| Need | Formula / test |
| --- | --- |
| Euclidean distance squared | `(x2-x1)^2+(y2-y1)^2`; compare squared distances when possible |
| Manhattan distance | `abs(dx)+abs(dy)` |
| Chebyshev distance / king moves on an unobstructed grid | `max(abs(dx),abs(dy))` |
| Midpoint | `((x1+x2)/2,(y1+y2)/2)`; promote before integer addition |
| Dot product | `ux*vx+uy*vy` |
| Perpendicular / parallel nonzero directions | `dot(u,v)=0` / `cross(u,v)=0` |
| Angle between nonzero vectors | `acos(clamp(dot(u,v)/(length(u)*length(v)),-1,1))` |
| Orientation of `A,B,C` | Sign of `cross(B-A,C-A)`; positive is counterclockwise in ordinary Cartesian coordinates |
| Triangle area | `abs(cross(B-A,C-A))/2` |
| Rotate by 90° counterclockwise | `(x,y) -> (-y,x)` about the origin |
| Rotate by angle `theta` | `(x*cosθ-y*sinθ, x*sinθ+y*cosθ)` |
| Line through `(x1,y1),(x2,y2)` | `a*x+b*y+c=0`, with `a=y1-y2`, `b=x2-x1`, `c=x1*y2-x2*y1` |
| Distance from `(x,y)` to nondegenerate line | `abs(a*x+b*y+c)/sqrt(a*a+b*b)` |
| Point reflection about center `C` | `2*C-P` |
| Point reflection about line | `2*projection(P)-P` |

Vector conventions can be cross-checked in [basic geometry](https://cp-algorithms.com/geometry/basic-geometry.html). Image/grid row coordinates often grow downward, reversing the visual meaning of clockwise versus counterclockwise.

For the nearest point on segment `AB`: if `A=B`, use `A`; otherwise let `t=dot(P-A,B-A)/dot(B-A,B-A)`, clamp `t` to `[0,1]`, and use `A+t*(B-A)`. For infinite lines `A+t*u` and `B+s*v`, if `cross(u,v)!=0`, `t=cross(B-A,v)/cross(u,v)`; otherwise the lines are parallel or coincident.

Normalize an integer direction by dividing `(dx,dy)` by `gcd(abs(dx),abs(dy))`. A zero vector has no direction. For **undirected** slopes, choose a canonical sign; for directed rays, opposite signs represent different rays. This avoids slope division and vertical-line special cases.

### Exact segment predicates

The code below counts endpoint touches and collinear overlap as intersection, including zero-length segments. Products are `i128`, and differences are promoted before subtracting. Coordinates of magnitude up to `10^18` keep these individual cross products within signed 128-bit range; unrestricted full-range signed 64-bit coordinates need a larger arithmetic bound. The predicate convention is checked against the [segment-intersection reference](https://cp-algorithms.com/geometry/check-segments-intersection.html).

<!-- snippet:geometry -->
```cpp
struct Point { ll x, y; };
inline i128 cross(Point a, Point b, Point c) {
    i128 ux = (i128)b.x - a.x, uy = (i128)b.y - a.y;
    i128 vx = (i128)c.x - a.x, vy = (i128)c.y - a.y;
    return ux * vy - uy * vx;
}
inline int sign(i128 x) { return (x > 0) - (x < 0); }
inline bool on_segment(Point a, Point b, Point p) {
    return cross(a,b,p) == 0 && min(a.x,b.x) <= p.x && p.x <= max(a.x,b.x)
        && min(a.y,b.y) <= p.y && p.y <= max(a.y,b.y);
}
inline bool segments_intersect(Point a, Point b, Point c, Point d) {
    i128 x = cross(a,b,c), y = cross(a,b,d);
    i128 z = cross(c,d,a), w = cross(c,d,b);
    if (x == 0 && on_segment(a,b,c)) return true;
    if (y == 0 && on_segment(a,b,d)) return true;
    if (z == 0 && on_segment(c,d,a)) return true;
    if (w == 0 && on_segment(c,d,b)) return true;
    return sign(x) * sign(y) < 0 && sign(z) * sign(w) < 0;
}
```

### Triangles, polygons, and lattice points

| Shape / quantity | Formula / assumptions |
| --- | --- |
| Nondegenerate triangle sides `a<=b<=c` | `a>0` and `a+b>c` |
| Right / acute / obtuse triangle | Compare `a*a+b*b` with `c*c`: equal / greater / smaller |
| Heron area | `sqrt(s*(s-a)*(s-b)*(s-c))`, `s=(a+b+c)/2`; valid triangle required |
| Area using two sides and included angle | `a*b*sin(C)/2` |
| Cosine rule | `c*c=a*a+b*b-2*a*b*cos(C)` |
| Sine rule | `a/sin(A)=b/sin(B)=c/sin(C)=2*R` |
| Inradius / circumradius | `r=area/s`, `R=a*b*c/(4*area)`; nonzero area |
| Equilateral triangle, side `a` | Height `sqrt(3)*a/2`, area `sqrt(3)*a*a/4` |
| Parallelogram / trapezoid | `base*height` / `(parallel_side1+parallel_side2)*height/2` |
| Simple polygon, cyclically ordered vertices | Shoelace: `2*area=abs(sum(x_i*y_(i+1)-y_i*x_(i+1)))` |
| Interior angle sum of simple `n`-gon | `(n-2)*180°` |
| Diagonals of convex `n`-gon | `n*(n-3)/2` |
| Regular `n`-gon, side `a` | Area `n*a*a/(4*tan(pi/n))` |
| Regular `n`-gon circumradius / apothem | `a/(2*sin(pi/n))` / `a/(2*tan(pi/n))` |
| Lattice points on segment, endpoints included | `gcd(abs(dx),abs(dy))+1` for distinct integer endpoints |
| Boundary lattice points of nondegenerate lattice polygon | Sum `gcd(abs(dx),abs(dy))` over its edges |
| Interior lattice points of a simple lattice polygon, no holes | `I=area-B/2+1=(2*area-B+2)/2` |

The last identity is [Pick's theorem](https://cp-algorithms.com/geometry/picks-theorem.html). Its assumptions exclude self-intersections and holes in this form. Shoelace needs boundary order, not arbitrary sorted vertices. Keep doubled area integral to avoid losing `.5`, and bound the **sum** of products as well as individual products.

For axis-aligned rectangles `[x1,x2] x [y1,y2]` and `[u1,u2] x [v1,v2]`, overlap lengths are `max(0,min(x2,u2)-max(x1,u1))` and similarly for `y`; multiply for area. There is no `+1` for geometric lengths. Counting integer grid points in inclusive intervals is a different question. For unions of many rectangles, pairwise subtraction alone misses higher-order overlaps.

For a point in a nondegenerate triangle, matching orientation signs including zeros detects boundary-inclusive containment when the triangle orientation is handled consistently. For a general simple polygon, ray casting or winding number is needed; check boundary membership separately.

### Circles, angles, and solid geometry

Angles in C++ trigonometry are in **radians**: `radians=degrees*pi/180`.

| Quantity | Formula |
| --- | --- |
| Circle circumference / area | `2*pi*r` / `pi*r*r` |
| Arc length / sector area for angle `theta` radians | `r*theta` / `r*r*theta/2` |
| Chord length subtending `theta`, `0<=theta<=2*pi` | `2*r*sin(theta/2)` |
| Circular segment area for arc angle `theta`, `0<=theta<=2*pi` | `r*r*(theta-sin(theta))/2` |
| Tangent length from external point at center distance `d>=r` | `sqrt(d*d-r*r)` |
| Annulus area, `R>=r` | `pi*(R*R-r*r)` |
| Cuboid volume / surface area | `a*b*c` / `2*(a*b+b*c+c*a)` |
| Cylinder volume / total surface area | `pi*r*r*h` / `2*pi*r*(r+h)` |
| Cone slant height / volume / total surface | `sqrt(r*r+h*h)` / `pi*r*r*h/3` / `pi*r*(r+slant)` |
| Sphere volume / surface area | `4*pi*r^3/3` / `4*pi*r*r` |
| Cone frustum volume | `pi*h*(R*R+R*r+r*r)/3` |

For two circles of nonnegative radii `r,R` and center distance `d`: separate if `d>r+R`; externally tangent at equality; one strictly inside the other without touching if `d<abs(R-r)`; internally tangent at equality when the radii differ. Equal centers and equal radii are coincident circles, not one tangency point. Use squared distances where practical, or a scale-aware tolerance for floating measurements.

If an overlap-area problem appears: return `0` for `d>=r+R`, and `pi*min(r,R)^2` for `d<=abs(r-R)`. Otherwise, with clamped `acos` arguments:

```text
alpha = acos((d*d + r*r - R*R)/(2*d*r))
beta  = acos((d*d + R*R - r*r)/(2*d*R))
overlap = r*r*alpha + R*R*beta
          - 0.5*sqrt(max(0,(-d+r+R)*(d+r-R)*(d-r+R)*(d+r+R)))
```

The containment/separation branches handle zero radii and `d=0` before these divisions. Preserve enough intermediate precision. The lens expression matches [Wolfram MathWorld’s circle-intersection formula](https://mathworld.wolfram.com/Circle-CircleIntersection.html).

<a id="graphs"></a>
## Graphs, grids, and trees

For `n` vertices and `m` edges, adjacency lists use `O(n+m)` space. Add both directions for an undirected edge. Convert indexing exactly once. A grid is a graph: define four/eight neighbors, obstacles, and any extra state such as remaining breaks or direction.

| Need | Method | Cost / restriction |
| --- | --- | --- |
| Reachability or connected components | DFS/BFS from every unvisited component | `O(n+m)` |
| Shortest path with unit edge cost | BFS | `O(n+m)` |
| Shortest path with weights 0/1 | Deque-based distance relaxation | `O(n+m)` |
| Nonnegative weighted shortest path | Dijkstra with stale-heap-entry checks | Heap-based near `O((n+m) log(n+m))` |
| Unweighted bipartiteness | Two-color each component by BFS/DFS | Every edge must join opposite colors |
| Dependency order in directed graph | Kahn's queue of zero indegree vertices | Fewer than `n` removed means a directed cycle |
| Connectivity while adding edges | DSU | Amortized near-constant operation cost |
| Minimum spanning tree | Sort edges, union different components | `O(m log m)`; fewer than `n-1` chosen edges means disconnected |

Mark BFS states when enqueueing to avoid duplicates. Recursive DFS on a long chain can exhaust the stack; use an iterative traversal where necessary. In an undirected multigraph, cycle detection must track the parent **edge**, not skip every neighbor equal to the parent vertex.

<!-- snippet:bfs -->
```cpp
inline vector<int> bfs(const vector<vector<int>>& graph, int source) {
    vector<int> distance(graph.size(), -1);
    queue<int> q;
    distance[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) if (distance[v] == -1) {
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }
    return distance;
}
```

For path reconstruction, store `parent[v]=u` when first discovering `v`, then follow parents from target to source and reverse. Multi-source BFS initializes all starting vertices at distance zero before processing.

<!-- snippet:dijkstra -->
```cpp
inline vector<ll> dijkstra(const vector<vector<pair<int,ll>>>& graph, int source) {
    // REQUIRE nonnegative weights and all finite distances < INF.
    const ll INF = LLONG_MAX / 4;
    vector<ll> distance(graph.size(), INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
    distance[source] = 0;
    q.push({0, source});
    while (!q.empty()) {
        auto [du, u] = q.top(); q.pop();
        if (du != distance[u]) continue;
        for (auto [v, weight] : graph[u]) {
            if (weight > INF - du) continue;
            ll candidate = du + weight;
            if (candidate < distance[v]) {
                distance[v] = candidate;
                q.push({candidate, v});
            }
        }
    }
    return distance;
}
```

Trees: a connected undirected graph with `n-1` edges has one simple path between any two vertices. Sum of degrees is `2m` in every undirected graph, counting a self-loop twice. For subtree sizes, `size[u]=1+sum(size[child])`; for subtree sums, replace `1` by `value[u]`. An Euler traversal makes each rooted subtree a contiguous interval, enabling prefix/Fenwick queries. In an unweighted tree, BFS from any vertex to a farthest vertex, then BFS again, gives a diameter. One vertex has diameter zero. Do not apply this two-BFS diameter rule to arbitrary graphs.

<a id="dp"></a>
## Dynamic programming

Before coding: state meaning → base cases → transition → processing order → answer location. Estimate the product of state dimensions and work per transition. Memoization must distinguish “uncomputed” from valid values such as `-1`, and recursive state graphs must terminate.

| Pattern | State / recurrence | Typical cost |
| --- | --- | --- |
| Frog with one/two-step jumps | `dp[i]=min(dp[i-1]+cost1,dp[i-2]+cost2)` | `O(n)` |
| Grid paths with right/down moves | `dp[r][c]=dp[r-1][c]+dp[r][c-1]`, zero at blocked cells | `O(rows*cols)` |
| Nonempty maximum subarray | `end=max(a[i],end+a[i])`, `best=max(best,end)` | `O(n)` |
| Longest common subsequence | Equal chars: diagonal+1; otherwise max of skip-left/skip-right | `O(n*m)` |
| Edit distance | Min of insertion, deletion, substitution with defined costs | `O(n*m)` |
| Strict LIS length | Maintain minimum tails with `lower_bound` | `O(n log n)` |
| Merge/take from ends of interval | `dp[l][r]` from smaller intervals | Often `O(n^2)` or `O(n^3)` |
| Subset state | `dp[mask]` from removing/adding one element | Often `O(n*2^n)` |

For nonempty Kadane, initialize `end=best=a[0]`, not zero; empty arrays need a separate policy. If empty subarrays are allowed, zero can be a valid answer. Read the [interval-DP note](../patterns/interval-dp.md) for endpoint recurrences instead of treating every 2D table as interval DP.

<!-- snippet:lis -->
```cpp
inline int lis_length(const vector<ll>& a) {
    vector<ll> tails;
    for (ll value : a) {
        auto it = lower_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return (int)tails.size();
}
```

For a longest **nondecreasing** subsequence, replace `lower_bound` by `upper_bound`. Tails are not necessarily one actual subsequence; reconstruction needs predecessor tracking.

### Knapsack and coin loop order

<!-- snippet:knapsack -->
```cpp
inline ll knapsack01(const vector<int>& weight, const vector<ll>& value, int capacity) {
    // REQUIRE equal vector sizes, positive weights, and capacity >= 0.
    // dp[c] means best value using total weight AT MOST c; choosing nothing is allowed.
    vector<ll> dp(capacity + 1, 0);
    for (int i = 0; i < (int)weight.size(); ++i)
        for (int c = capacity; c >= weight[i]; --c)
            dp[c] = max(dp[c], dp[c - weight[i]] + value[i]);
    return dp[capacity];
}
```

| Problem | Loop order / initialization |
| --- | --- |
| Each item at most once | Items outside, capacity **descending** |
| Unlimited reuse of item/coin | Items outside, capacity **ascending** |
| Count unordered combinations of unlimited coin denominations | Coins outside, sum ascending; `ways[0]=1` |
| Count ordered coin sequences | Sum outside, coins inside; `ways[0]=1` |
| Minimum coins for exact sum | `dp[0]=0`, all others `INF`; relax from reachable states |
| Reachability of exact subset sum | `possible[0]=true`, sums descending for each item |

For **exact** weight maximum value, initialize other states to negative infinity and guard transitions; zero initialization would invent reachable states. Coin counts assume positive denominations; deduplicate denominations if equal-valued coins are not intended to represent different choices. Knapsack direction is checked against [the dedicated recurrence explanation](https://cp-algorithms.com/dynamic_programming/knapsack.html).

<a id="structures"></a>
## Data structures

Use the simplest structure matching the operations. Sorted vectors are excellent for static data; a `set` does not expose rank or k-th element in standard C++. A monotonic stack gives nearest smaller/greater positions by popping dominated elements; strictness (`<` versus `<=`) determines how duplicates are handled.

### DSU: indices `0..n-1`

<!-- snippet:dsu -->
```cpp
struct DSU {
    vector<int> parent, size;
    explicit DSU(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a,b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};
```

Query component size via `size[find(x)]`, not an old non-root index. This DSU supports merges; rollback/deletions need a different design.

### Fenwick tree: zero-based public interface

`add(i,delta)` adds to position `i`; `prefix(r)` sums `[0,r)`; `range(l,r)` sums `[l,r)`. All indices must be within the constructed size. Each operation costs `O(log n)`; memory is `O(n)`. To assign a value, add `new_value-old_value`.

<!-- snippet:fenwick -->
```cpp
struct Fenwick {
    int n;
    vector<ll> bit;
    explicit Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int index, ll delta) { // 0 <= index < n
        for (++index; index <= n; index += index & -index) bit[index] += delta;
    }
    ll prefix(int r) const { // 0 <= r <= n
        ll result = 0;
        for (; r > 0; r -= r & -r) result += bit[r];
        return result;
    }
    ll range(int l, int r) const { return prefix(r) - prefix(l); }
};
```

### Segment tree: point assignment, range sum

This is a compact backup for dynamic range queries. It uses `O(n)` space and `O(log n)` per operation. For range minimum, change the merge to `min` **and** the neutral value to positive infinity; for XOR use XOR and zero. Range updates require an adapted design, often lazy propagation.

<!-- snippet:segment-tree -->
```cpp
struct SumSegTree {
    int n = 1;
    vector<ll> tree;
    explicit SumSegTree(const vector<ll>& a) {
        while (n < (int)a.size()) n *= 2;
        tree.assign(2*n, 0);
        for (int i = 0; i < (int)a.size(); ++i) tree[n+i] = a[i];
        for (int i = n-1; i >= 1; --i) tree[i] = tree[2*i] + tree[2*i+1];
    }
    void set_value(int index, ll value) { // index is an actual array position
        int p = index + n;
        tree[p] = value;
        for (p /= 2; p >= 1; p /= 2) tree[p] = tree[2*p] + tree[2*p+1];
    }
    ll range(int l, int r) const { // half-open [l,r)
        ll left = 0, right = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) left += tree[l++];
            if (r & 1) right = tree[--r] + right;
        }
        return left + right;
    }
};
```

<a id="extras"></a>
## Enumeration, games, and cycles

- For small `n`, enumerate subsets or permutations and optimize only after counting operations. Prune a search only when a partial state cannot lead to a valid/better complete answer.
- For around 40 elements, enumerate sums in each half, sort one list, and use binary-search bounds to count or locate compatible pairs. Memory also scales as `2^(n/2)`.
- In a functional graph (one outgoing edge per vertex), a walk eventually repeats. Store the first visit time of each state; then separate the initial path and the cycle before reducing a huge step count modulo the cycle length.
- For a deterministic recurrence with a tiny state space, record the **whole state**, not just one component, before claiming periodicity.
- In a finite impartial normal-play game, a state is winning if some legal move reaches a losing state; terminal states are losing. Compute small states to discover a conjecture, then prove it.
- In normal-play Nim, where one move removes any positive number from one pile, XOR zero is losing and XOR nonzero is winning. This rule does not apply to arbitrary take-away games. See the [Nim reference](https://cp-algorithms.com/game_theory/sprague-grundy-nim.html).
- For take `1..k` from a single pile under normal play, multiples of `k+1` are losing. A different allowed-move set or last-move-loses rule changes the result.
- In misère Nim, if every nonempty pile has size one, an odd number of such piles is losing; otherwise use the usual XOR criterion.

Pigeonhole principle: more objects than boxes implies a repeated box. For example, among `n+1` prefix remainders modulo positive `n`, some pair repeats, yielding a nonempty divisible subarray. Invariants such as parity, sum modulo a number, or permutation sign can establish impossibility without constructing a sequence of operations.

<a id="debugging"></a>
## Failure checklist

**Before submitting:**

1. Test-count present or absent? Multiple answers per line? Case labels? Required precision?
2. Is the range inclusive or half-open? Are indices converted once? Does `r+1` have allocated space?
3. Empty choice allowed? Nonempty subarray required? Strict `<` or non-strict `<=`?
4. Handle smallest input, all equal, sorted/reversed, all negative, zeros, duplicates, impossible answer, and large values.
5. Did an `int` product overflow before assignment to `long long`? Can a prefix sum, pair count, or squared distance exceed 64 bits?
6. Does a comparator violate strict ordering? Did a map insertion or vector reallocation invalidate an assumption?
7. Does a binary search predicate really remain monotone? Is its sentinel distinct from a valid answer?
8. Did a DP loop accidentally reuse the same item? Is “uncomputed” distinguishable from a valid answer?
9. Are graph components, isolated vertices, `n=1`, repeated edges, and parent edges handled?
10. Are arrays/state reset between tests? Is complexity over all tests acceptable?
11. Remove local `freopen`, debug output, and development-only file dependencies before submission.

For WA, shrink the first failing example and trace the state. For TLE, count loops and data-structure costs before micro-optimizing. For a new greedy/search idea, compare against a simple brute force on random tiny inputs during preparation. A useful local GNU build is:

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -Wshadow -Wconversion \
  -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o main
```

Use the judge's supported release settings for actual submission. Sanitizers change runtime and memory costs. A crash-free run is not a proof of algorithmic correctness.

<a id="practice"></a>
## Preparation route using this repository

These are a flexible sequence, not an inferred schedule. If time is short, prioritize the first three passes.

1. **Speed and implementation:** timed arithmetic, counting, strings, sorting, greedy. After each run, record whether the delay was recognizing the pattern, deriving the formula, coding, or debugging.
2. **Contiguous ranges:** prefix/difference arrays, prefix maps, positive-only sum windows, distinct-value windows, and sorted pair counting.
3. **Search and math:** answer feasibility, GCD/divisibility, modular powers, basic combinatorics, integer rounding, coordinate geometry.
4. **Graph and DP basics:** BFS grids, components, trees, Kadane, knapsack, coin order, LIS.
5. **Mixed timed sets:** choose unfamiliar problems at your target difficulty, then upsolve the first missed problem without immediately reading the entire editorial.

| Pattern to rehearse | Local example to read |
| --- | --- |
| Maximum adjacent gap / return segment | [Line Trip](../../solutions/greedy/A_Line_Trip.cpp) |
| Prefix map counting | [Subarray sum equals k](../../algorithms/prefix-sums/subarray_sum_equals_k.cpp) |
| Earliest prefix occurrence | [Longest subarray with sum k](../../algorithms/prefix-sums/longest_subarray_with_sum_k.cpp) |
| Sorted greedy feasibility + search | [Aggressive cows](../../solutions/binary-search/Aggressive_cows.cpp) |
| Production-time binary search | [Factory machines](../../solutions/binary-search/factory_machines.cpp) |
| Monotonic deque | [Sliding window extrema](../../algorithms/two-pointers-and-sliding-window/sliding_window_max.cpp) |
| 0–1 knapsack | [Book shop](../../solutions/dynamic-programming/knapsack/cses-bookshop.cpp) |
| LCS reconstruction | [LCS](../../solutions/dynamic-programming/sequences/LCS.cpp) |
| Interval merging DP | [Slimes](../../solutions/dynamic-programming/intervals/N_Slimes.cpp) |

Local examples preserve historical attempts and are not labeled accepted by this sheet. Use the pattern notes and independently check implementations when practicing. Search more examples with `python3 scripts/search.py --category CATEGORY` or `--pattern PATTERN_ID`.

<a id="references"></a>
## External references

Sources consulted on 2026-10-17. The organization/priorities and original snippets here are tailored to this archive; this is not an official contest syllabus.

- [Competitive Programmer's Handbook — author/book page](https://cses.fi/book/index.php): broad preparation reference and free book access.
- [USACO Guide: prefix sums](https://usaco.guide/silver/prefix-sums), [two pointers](https://usaco.guide/silver/two-pointers), [binary search](https://usaco.guide/silver/binary-search): pattern prerequisites and examples.
- [CP-Algorithms: divisor formulas](https://cp-algorithms.com/algebra/divisors.html), [modular inverses](https://cp-algorithms.com/algebra/module-inverse.html), [linear Diophantine equations](https://cp-algorithms.com/algebra/linear-diophantine-equation.html): number-theory conditions.
- [CP-Algorithms: stars and bars](https://cp-algorithms.com/combinatorics/stars_and_bars.html), [knapsack](https://cp-algorithms.com/dynamic_programming/knapsack.html), [Nim](https://cp-algorithms.com/game_theory/sprague-grundy-nim.html): counting and recurrence assumptions.
- [CP-Algorithms: basic geometry](https://cp-algorithms.com/geometry/basic-geometry.html), [segment intersection](https://cp-algorithms.com/geometry/check-segments-intersection.html), [Pick's theorem](https://cp-algorithms.com/geometry/picks-theorem.html): predicate conventions and lattice geometry.

- [GCC: bit-operation builtins](https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html): zero-input restrictions for leading/trailing-zero counts.
- [Wolfram MathWorld: circle-circle intersection](https://mathworld.wolfram.com/Circle-CircleIntersection.html): circle lens area and limiting cases.
