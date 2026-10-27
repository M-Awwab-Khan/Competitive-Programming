# Organization log

Repository organization events, newest first. Source code is never copied into the log.

[Guide](README.md)

## 2026-10-23T18:08:04+00:00 — REVIEW

- solutions/needs-review/x = int(input()).py → solutions/math/number-theory/x = int(input()).py: Prints YES exactly for even integers other than two using a parity test and one special case.. Category: math/number-theory; status: reviewed.

## 2026-10-23T18:08:03+00:00 — REVIEW

- solutions/dynamic-programming/general/test.py → solutions/dynamic-programming/general/test.py: Marks a state winning if any smaller state strictly above half is losing, fills states through 10000, then prints a move to a losing state.. Category: dynamic-programming/general; status: reviewed.

## 2026-10-23T18:08:02+00:00 — REVIEW

- solutions/needs-review/newtons_method.cpp → solutions/math/arithmetic/newtons_method.cpp: Performs ten Newton updates for exp(-A*t)+exp(-B*t)-1 starting at zero; no convergence or zero-derivative guard.. Category: math/arithmetic; status: reviewed.

## 2026-10-23T18:08:01+00:00 — REVIEW

- solutions/needs-review/maximum_nondecreasing.cpp → solutions/arrays-and-counting/maximum_nondecreasing.cpp: Scans adjacent comparisons, resets a run on a decrease, and tracks the longest contiguous nondecreasing run.. Category: arrays-and-counting; status: reviewed.

## 2026-10-23T18:08:00+00:00 — REVIEW

- solutions/graphs/traversal/longest_path.cpp → solutions/graphs/traversal/longest_path.cpp: Recursively explores outgoing edges from vertex one and compares path strings lexicographically; no cycle guard, and multi-digit labels break one-character backtracking and reported length.. Category: graphs/traversal; status: reviewed.

## 2026-10-23T18:07:58+00:00 — REVIEW

- solutions/math/number-theory/largest_partition.cpp → solutions/math/number-theory/largest_partition.cpp: Collects maximal nondecreasing run lengths and computes their gcd, but the gcd loop excludes the final run when multiple runs exist.. Category: math/number-theory; status: reviewed.

## 2026-10-23T18:07:57+00:00 — REVIEW

- solutions/data-structures/disjoint-set/kruskal.cpp → solutions/graphs/spanning-trees/kruskal.cpp: Forces the designated edge into a DSU first, then adds remaining edges in ascending cost order when they join components; no disconnected-graph validation.. Category: graphs/spanning-trees; status: reviewed.

## 2026-10-23T18:07:56+00:00 — REVIEW

- solutions/needs-review/horner_algo.cpp → solutions/math/arithmetic/horner_algo.cpp: Computes polynomial composition with Horner recurrence R=R*Q+P[i], using explicit coefficient convolution modulo 998244353.. Category: math/arithmetic; status: reviewed.

## 2026-10-23T18:07:55+00:00 — REVIEW

- solutions/needs-review/erase_tab_submissions.cpp → solutions/simulation/erase_tab_submissions.cpp: Uses deletion count parity to require identical strings after even operations or differing bits at every position after odd operations.. Category: simulation; status: reviewed.

## 2026-10-23T18:07:53+00:00 — REVIEW

- solutions/sorting-and-searching/bottles_and_gems.cpp → solutions/greedy/bottles_and_gems.cpp: Sorts coin/gem pairs, acquires positive-gem bottles in ascending order, then spends remaining gems on zero-gem bottles in reverse cost order.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:52+00:00 — REVIEW

- solutions/needs-review/boredom.cpp → solutions/dynamic-programming/sequences/boredom.cpp: Counts each value and uses take-or-skip recurrence b[i]=max(b[i-1],b[i-2]+frequency[i]*i).. Category: dynamic-programming/sequences; status: reviewed.

## 2026-10-23T18:07:51+00:00 — REVIEW

- solutions/sorting-and-searching/Young_Explorers.cpp → solutions/greedy/Young_Explorers.cpp: Sorts requirements and closes each group as soon as its size meets the largest requirement scanned.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:50+00:00 — REVIEW

- solutions/dynamic-programming/general/Sprinkler_Piping.cpp → solutions/dynamic-programming/bitmask/Sprinkler_Piping.cpp: dp[mask][last] stores minimum cost to visit the mask and end at last, initialized by individual startup costs and extended to unvisited nodes.. Category: dynamic-programming/bitmask; status: reviewed.

## 2026-10-23T18:07:48+00:00 — REVIEW

- solutions/arrays-and-counting/Rameez_And_The_Missing_Numbers.cpp → solutions/binary-search/Rameez_And_The_Missing_Numbers.cpp: Finds the first mid with mid-floor(mid/n) at least k using inclusive binary search; assumes n and the fixed upper bound admit a solution.. Category: binary-search; status: reviewed.

## 2026-10-23T18:07:47+00:00 — REVIEW

- solutions/dynamic-programming/general/Pegs_DP.cpp → solutions/dynamic-programming/sequences/Pegs_DP.cpp: Minimizes dp[i] over previous indices within k using Euclidean point distance; includes a redundant self transition.. Category: dynamic-programming/sequences; status: reviewed.

## 2026-10-23T18:07:46+00:00 — REVIEW

- solutions/needs-review/Little_Fairy_Painting.cpp → solutions/simulation/Little_Fairy_Painting.cpp: Maintains distinct values in a set, repeatedly inserts its current size, and stops when that size already exists.. Category: simulation; status: reviewed.

## 2026-10-23T18:07:45+00:00 — REVIEW

- solutions/strings/K_Equal_subsequence.py → solutions/arrays-and-counting/K_Equal_subsequence.py: Compresses equal-value runs and compares even single-run lengths with twice the minimum adjacent run length.. Category: arrays-and-counting; status: reviewed.

## 2026-10-23T18:07:43+00:00 — REVIEW

- solutions/strings/K_Equal_subsequence__5fbda7ad.cpp → solutions/arrays-and-counting/K_Equal_subsequence__5fbda7ad.cpp: Compresses consecutive equal values into run lengths and maximizes even single-run length or twice the shorter adjacent run; final singleton may be appended twice.. Category: arrays-and-counting; status: reviewed.

## 2026-10-23T18:07:42+00:00 — REVIEW

- solutions/math/number-theory/Journey_For_Grapes.cpp → solutions/math/number-theory/Journey_For_Grapes.cpp: Prints lcm(n,s)/s directly.. Category: math/number-theory; status: reviewed.

## 2026-10-23T18:07:41+00:00 — REVIEW

- solutions/needs-review/J_Apple_s_Farm.cpp → solutions/meet-in-the-middle/J_Apple_s_Farm.cpp: Enumerates grid path halves from opposite corners, stores remainder frequencies at meeting cells, and joins complementary sums while subtracting the shared cell once; C++ negative remainder normalization is incomplete.. Category: meet-in-the-middle; status: reviewed.

## 2026-10-23T18:07:40+00:00 — REVIEW

- solutions/needs-review/H_Make_Equal.py → solutions/math/arithmetic/H_Make_Equal.py: Solves the linear equation using (p*x-q*y)/(q-p), checking divisibility and nonnegativity and handling equal coefficients separately.. Category: math/arithmetic; status: reviewed.

## 2026-10-23T18:07:38+00:00 — REVIEW

- solutions/bit-manipulation/Grid_Sums_Backtracking.cpp → solutions/brute-force-and-backtracking/Grid_Sums_Backtracking.cpp: Enumerates row masks with the required popcount, subtracts column demands, prunes outside remaining-row capacity, and restores demands on backtracking.. Category: brute-force-and-backtracking; status: reviewed.

## 2026-10-23T18:07:37+00:00 — REVIEW

- solutions/dynamic-programming/general/G_Subway_Surfers.cpp → solutions/dynamic-programming/general/G_Subway_Surfers.cpp: Bottom-up row/lane DP takes the best reachable neighboring lane below and adds coin value; obstacles retain a negative sentinel.. Category: dynamic-programming/general; status: reviewed.

## 2026-10-23T18:07:36+00:00 — REVIEW

- solutions/needs-review/Faking_Data.cpp → solutions/greedy/Faking_Data.cpp: Runs two local-decrement passes for opposite alternating inequality orientations and returns the cheaper accumulated adjustment.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:35+00:00 — REVIEW

- solutions/sorting-and-searching/E_khba_loves_to_sleep.cpp → solutions/greedy/E_khba_loves_to_sleep.cpp: Adds endpoints zero and x, sorts positions, ranks gaps in descending order, and emits the first k midpoints; no feasibility search is implemented.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:33+00:00 — REVIEW

- solutions/needs-review/E_Romantic_Glasses.cpp → solutions/prefix-sums/E_Romantic_Glasses.cpp: Alternates input signs, seeds prefix zero, and detects a repeated signed prefix using an ordered frequency map.. Category: prefix-sums; status: reviewed.

## 2026-10-23T18:07:32+00:00 — REVIEW

- solutions/sorting-and-searching/E_Make_Empty.cpp → solutions/greedy/E_Make_Empty.cpp: Sorts values, greedily pairs adjacent values whose difference is at most two, and counts unpaired values separately.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:31+00:00 — REVIEW

- solutions/sorting-and-searching/E_Burns_Road.cpp → solutions/sorting-and-searching/E_Burns_Road.cpp: Sorts intervals independently by right and left endpoints, sweeps coordinate tables, and answers queries with minR[x] < maxL[y]; sweeps do not check both endpoints for coverage.. Category: sorting-and-searching; status: reviewed.

## 2026-10-23T18:07:30+00:00 — REVIEW

- solutions/math/number-theory/E_Again_Divisors.cpp → solutions/math/number-theory/E_Again_Divisors.cpp: Enumerates nonempty divisor subsets, bounds their LCM using 128-bit arithmetic, and adds or subtracts interval multiple counts by subset parity.. Category: math/number-theory; status: reviewed.

## 2026-10-23T18:07:29+00:00 — REVIEW

- solutions/bit-manipulation/Digits_Duel.cpp → solutions/needs-review/Digits_Duel.cpp: Unfinished simulation repeatedly subtracts ceil(n/2) and toggles turn inside while(true), with no exit or output; reaches zero and loops forever.. Category: needs-review; status: needs-review.

## 2026-10-23T18:07:27+00:00 — REVIEW

- solutions/needs-review/D_Max_Product.py → solutions/greedy/D_Max_Product.py: Splits digit sum into floor/ceiling halves and greedily fills leading digits with nines, then multiplies Python integers modulo 998244353. Classification does not validate optimality.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:26+00:00 — REVIEW

- solutions/strings/D_Max_Product.cpp → solutions/greedy/D_Max_Product.cpp: Splits digit sum into floor/ceiling halves and fills leading digits with up to nine; custom Bigint computes the modular product. Classification does not validate optimality.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:25+00:00 — REVIEW

- solutions/data-structures/ordered-sets/D_Matryoshkas.cpp → solutions/greedy/D_Matryoshkas.cpp: Repeatedly removes the smallest remaining value and extends a consecutive chain by erasing one copy of each successor.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:24+00:00 — REVIEW

- solutions/dynamic-programming/general/Coin_Change_2.cpp → solutions/dynamic-programming/sequences/Coin_Change_2.cpp: Sum-outer recurrence adds dp[sum-1] and dp[sum-2] modulo 2026, counting ordered step sequences.. Category: dynamic-programming/sequences; status: reviewed.

## 2026-10-23T18:07:23+00:00 — REVIEW

- solutions/dynamic-programming/general/Coin_Change_1.cpp → solutions/dynamic-programming/knapsack/Coin_Change_1.cpp: Coin-outer and ascending-sum loops update dp[sum] from dp[sum-coin], counting unbounded combinations rather than ordered sequences.. Category: dynamic-programming/knapsack; status: reviewed.

## 2026-10-23T18:07:21+00:00 — REVIEW

- solutions/needs-review/C_Removing_Smallest_Multiples.cpp → solutions/math/number-theory/C_Removing_Smallest_Multiples.cpp: Visits multiples of each divisor, stopping at a protected one; descending divisor passes overwrite deletion costs with smaller feasible divisors.. Category: math/number-theory; status: reviewed.

## 2026-10-23T18:07:20+00:00 — REVIEW

- solutions/binary-search/C_Rearrange.cpp → solutions/greedy/C_Rearrange.cpp: For each original a value, removes the smallest remaining b at least that value using multiset lower_bound; adds decreasing rewards on successful matches.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:19+00:00 — REVIEW

- solutions/sorting-and-searching/Balatro.cpp → solutions/greedy/Balatro.cpp: Sorts both arrays and sums absolute differences between corresponding ranks.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:18+00:00 — REVIEW

- solutions/prefix-sums/B_Short_and_Hard.cpp → solutions/prefix-sums/B_Short_and_Hard.cpp: Builds prefix logarithms and enumerates all subarrays to minimize their average log, then exponentiates; assumes positive values after a zero check.. Category: prefix-sums; status: reviewed.

## 2026-10-23T18:07:16+00:00 — REVIEW

- solutions/arrays-and-counting/B_M_Arrays__0a29afd8.cpp → solutions/greedy/B_M_Arrays__0a29afd8.cpp: Consumes a multiset of remainders by alternating complementary residues and starts a new chain when the complement is absent.. Category: greedy; status: reviewed.

## 2026-10-23T18:07:07+00:00 — REVIEW

- solutions/needs-review/B_7485_Unlimited_Easy_version.cpp → solutions/two-pointers-and-sliding-window/B_7485_Unlimited_Easy_version.cpp: Shrinks a window when length minus its ordered-digit subsequence DP exceeds k; two aggregate stacks compose 4-by-4 DP tables.. Category: two-pointers-and-sliding-window; status: reviewed.

## 2026-10-23T18:07:06+00:00 — REVIEW

- solutions/needs-review/A_Game_of_chocolates.py → solutions/games/A_Game_of_chocolates.py: Chooses the winner solely from whether n is divisible by three.. Category: games; status: reviewed.

## 2026-10-23T18:07:04+00:00 — REVIEW

- solutions/needs-review/A_AND_Pairs.cpp → solutions/math/arithmetic/A_AND_Pairs.cpp: Evaluates (n+1)(n+2)/2 modulo 998244353 using a 128-bit intermediate; no bitwise pair enumeration.. Category: math/arithmetic; status: reviewed.

## 2026-10-23T18:05:53+00:00 — INGEST

- A_AND_Pairs.cpp → solutions/needs-review/A_AND_Pairs.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- A_Game_of_chocolates.py → solutions/needs-review/A_Game_of_chocolates.py: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_7485_Unlimited_Easy_version.cpp → solutions/needs-review/B_7485_Unlimited_Easy_version.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_M_Arrays.cpp → solutions/arrays-and-counting/B_M_Arrays__0a29afd8.cpp: Filed new source; classification remains a suggestion. Category: arrays-and-counting; status: suggested.
- B_Short_and_Hard.cpp → solutions/prefix-sums/B_Short_and_Hard.cpp: Filed new source; classification remains a suggestion. Category: prefix-sums; status: suggested.
- Balatro.cpp → solutions/sorting-and-searching/Balatro.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- boredom.cpp → solutions/needs-review/boredom.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- bottles_and_gems.cpp → solutions/sorting-and-searching/bottles_and_gems.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- C_Rearrange.cpp → solutions/binary-search/C_Rearrange.cpp: Filed new source; classification remains a suggestion. Category: binary-search; status: suggested.
- C_Removing_Smallest_Multiples.cpp → solutions/needs-review/C_Removing_Smallest_Multiples.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- Coin_Change_1.cpp → solutions/dynamic-programming/general/Coin_Change_1.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- Coin_Change_2.cpp → solutions/dynamic-programming/general/Coin_Change_2.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- D_Matryoshkas.cpp → solutions/data-structures/ordered-sets/D_Matryoshkas.cpp: Filed new source; classification remains a suggestion. Category: data-structures/ordered-sets; status: suggested.
- D_Max_Product.cpp → solutions/strings/D_Max_Product.cpp: Filed new source; classification remains a suggestion. Category: strings; status: suggested.
- D_Max_Product.py → solutions/needs-review/D_Max_Product.py: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- Digits_Duel.cpp → solutions/bit-manipulation/Digits_Duel.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- E_Again_Divisors.cpp → solutions/math/number-theory/E_Again_Divisors.cpp: Filed new source; classification remains a suggestion. Category: math/number-theory; status: suggested.
- E_Burns_Road.cpp → solutions/sorting-and-searching/E_Burns_Road.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- E_khba_loves_to_sleep.cpp → solutions/sorting-and-searching/E_khba_loves_to_sleep.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- E_Make_Empty.cpp → solutions/sorting-and-searching/E_Make_Empty.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- E_Romantic_Glasses.cpp → solutions/needs-review/E_Romantic_Glasses.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- erase_tab_submissions.cpp → solutions/needs-review/erase_tab_submissions.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- Faking_Data.cpp → solutions/needs-review/Faking_Data.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- G_Subway_Surfers.cpp → solutions/dynamic-programming/general/G_Subway_Surfers.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- Grid_Sums_Backtracking.cpp → solutions/bit-manipulation/Grid_Sums_Backtracking.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- H_Make_Equal.py → solutions/needs-review/H_Make_Equal.py: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- horner_algo.cpp → solutions/needs-review/horner_algo.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- J_Apple_s_Farm.cpp → solutions/needs-review/J_Apple_s_Farm.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- Journey_For_Grapes.cpp → solutions/math/number-theory/Journey_For_Grapes.cpp: Filed new source; classification remains a suggestion. Category: math/number-theory; status: suggested.
- K_Equal_subsequence.cpp → solutions/strings/K_Equal_subsequence__5fbda7ad.cpp: Filed new source; classification remains a suggestion. Category: strings; status: suggested.
- K_Equal_subsequence.py → solutions/strings/K_Equal_subsequence.py: Filed new source; classification remains a suggestion. Category: strings; status: suggested.
- kruskal.cpp → solutions/data-structures/disjoint-set/kruskal.cpp: Filed new source; classification remains a suggestion. Category: data-structures/disjoint-set; status: suggested.
- largest_partition.cpp → solutions/math/number-theory/largest_partition.cpp: Filed new source; classification remains a suggestion. Category: math/number-theory; status: suggested.
- Little_Fairy_Painting.cpp → solutions/needs-review/Little_Fairy_Painting.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- longest_path.cpp → solutions/graphs/traversal/longest_path.cpp: Filed new source; classification remains a suggestion. Category: graphs/traversal; status: suggested.
- maximum_nondecreasing.cpp → solutions/needs-review/maximum_nondecreasing.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- newtons_method.cpp → solutions/needs-review/newtons_method.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- Pegs_DP.cpp → solutions/dynamic-programming/general/Pegs_DP.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- Rameez_And_The_Missing_Numbers.cpp → solutions/arrays-and-counting/Rameez_And_The_Missing_Numbers.cpp: Filed new source; classification remains a suggestion. Category: arrays-and-counting; status: suggested.
- Sprinkler_Piping.cpp → solutions/dynamic-programming/general/Sprinkler_Piping.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- test.py → solutions/dynamic-programming/general/test.py: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- x = int(input()).py → solutions/needs-review/x = int(input()).py: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- Young_Explorers.cpp → solutions/sorting-and-searching/Young_Explorers.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.

## 2026-10-27T13:35:22+00:00 — REVIEW

- solutions/sorting-and-searching/test2.cpp → solutions/math/number-theory/test2.cpp: Trial-divides M into prime factors, sorts factors by ascending decimal length then descending value, and accumulates M times factor digit length while dividing M. The comparator narrows long long factors to int; zero input would not terminate.. Category: math/number-theory; status: reviewed.

## 2026-10-27T13:35:19+00:00 — REVIEW

- solutions/needs-review/test.py → solutions/math/number-theory/test.py: Multiplies the input integers while reducing the running product modulo 1000000007; n is read but not used to validate the number of values.. Category: math/number-theory; status: reviewed.

## 2026-10-27T13:35:17+00:00 — REVIEW

- solutions/bit-manipulation/test.cpp → solutions/data-structures/stacks-and-queues/test.cpp: A monotonic stack finds each previous greater-or-equal index; a 19-level binary-lifting table counts predecessor-chain links inside query bounds. Debug level tables remain in output; fixed N and level count bound supported sizes.. Category: data-structures/stacks-and-queues; status: reviewed.

## 2026-10-27T13:35:15+00:00 — REVIEW

- solutions/needs-review/cf-wewerebothchildren.cpp → solutions/math/number-theory/cf-wewerebothchildren.cpp: Counts input values, adds each frequency to all multiples up to n, and takes the maximum accumulated count; ignores values outside 1..n.. Category: math/number-theory; status: reviewed.

## 2026-10-27T13:35:13+00:00 — REVIEW

- solutions/needs-review/cf-fun.cpp → solutions/brute-force-and-backtracking/cf-fun.cpp: Enumerates positive a and b under feasibility bounds, then counts valid positive c with min((n-a*b)/(a+b), x-a-b). Accumulator and products use int, so overflow depends on input bounds.. Category: brute-force-and-backtracking; status: reviewed.

## 2026-10-27T13:35:11+00:00 — REVIEW

- solutions/needs-review/cf-bakery.cpp → solutions/arrays-and-counting/cf-bakery.cpp: Stores selected vertices in a set and scans every edge, minimizing weight exactly when one endpoint belongs to the selected set; no graph traversal or shortest-path computation.. Category: arrays-and-counting; status: reviewed.

## 2026-10-27T13:34:52+00:00 — INGEST

- practice/inbox/cf-bakery/cf-bakery.cpp → solutions/needs-review/cf-bakery.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- practice/inbox/cf-fun/cf-fun.cpp → solutions/needs-review/cf-fun.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- practice/inbox/cf-wewerebothchildren/cf-wewerebothchildren.cpp → solutions/needs-review/cf-wewerebothchildren.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- test.cpp → solutions/bit-manipulation/test.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- test.py → solutions/needs-review/test.py: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- test2.cpp → solutions/sorting-and-searching/test2.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.

## 2026-10-19T07:27:23+00:00 — REVIEW

- solutions/needs-review/cf-cheaptravel.cpp → solutions/brute-force-and-backtracking/cf-cheaptravel.cpp: Enumerates every single-ticket count xx from 0 through n, computes the remaining bundle count with ceiling division (n-xx+m-1)/m, and minimizes xx*a plus bundle_count*b. This is O(n) enumeration with O(1) extra space; assumes m is positive and integer cost arithmetic fits int.. Category: brute-force-and-backtracking; status: reviewed.

## 2026-10-19T07:27:22+00:00 — INGEST

- practice/inbox/cf-cheaptravel/cf-cheaptravel.cpp → solutions/needs-review/cf-cheaptravel.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.

## 2026-10-19T06:45:03+00:00 — REVIEW

- solutions/strings/cf-stringtask.cpp → solutions/strings/cf-stringtask.cpp: Erases vowels in both cases, inserts a dot before remaining characters while advancing past each insertion, then converts ASCII uppercase letters to lowercase. Repeated middle insertions can take quadratic time.. Category: strings; status: reviewed.

## 2026-10-19T06:45:02+00:00 — REVIEW

- solutions/graphs/traversal/cf-iceskating.cpp → solutions/graphs/traversal/cf-iceskating.cpp: Compares every pair of points, adds undirected edges for equal x or y coordinates, recursively visits each component with DFS, and prints component count minus one; explicit map/set adjacency has quadratic possible storage and insertion costs.. Category: graphs/traversal; status: reviewed.

## 2026-10-19T06:45:01+00:00 — REVIEW

- solutions/needs-review/cf-fancyfence.cpp → solutions/math/arithmetic/cf-fancyfence.cpp: Checks divisibility of 360 by the exterior angle 180-n to determine whether an integer number of equal turns closes a regular polygon; assumes the input angle is strictly between 0 and 180 degrees.. Category: math/arithmetic; status: reviewed.

## 2026-10-19T06:45:00+00:00 — INGEST

- practice/inbox/cf-fancyfence/cf-fancyfence.cpp → solutions/needs-review/cf-fancyfence.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- practice/inbox/cf-iceskating/cf-iceskating.cpp → solutions/graphs/traversal/cf-iceskating.cpp: Filed new source; classification remains a suggestion. Category: graphs/traversal; status: suggested.
- practice/inbox/cf-stringtask/cf-stringtask.cpp → solutions/strings/cf-stringtask.cpp: Filed new source; classification remains a suggestion. Category: strings; status: suggested.

## 2026-10-18T15:24:09+00:00 — REVIEW

- solutions/math/combinatorics/cf-expectedmedian.cpp → solutions/math/combinatorics/cf-expectedmedian.cpp: Precomputes factorials and inverse factorials modulo 1000000007 using binary exponentiation, then sums C(count1,i)*C(count0,k-i) for i from (k+1)/2 to min(k,count1); interprets the median threshold for odd k and binary input, with factorial indices bounded by 200001.. Category: math/combinatorics; status: reviewed.

## 2026-10-18T15:24:07+00:00 — REVIEW

- solutions/needs-review/cf-ballinberland.cpp → solutions/arrays-and-counting/cf-ballinberland.cpp: Builds endpoint frequency arrays, sums k - boysfreq[u] - girlsfreq[v] + 1 for each paired item, and divides by two; inclusion-exclusion assumes distinct endpoint pairs.. Category: arrays-and-counting; status: reviewed.

## 2026-10-18T15:24:05+00:00 — INGEST

- practice/inbox/cf-ballinberland/cf-ballinberland.cpp → solutions/needs-review/cf-ballinberland.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- practice/inbox/cf-expectedmedian/cf-expectedmedian.cpp → solutions/math/combinatorics/cf-expectedmedian.cpp: Filed new source; classification remains a suggestion. Category: math/combinatorics; status: suggested.

## 2026-10-17T01:08:49+00:00 — REFERENCE

Created a Div. 3 speed-programming preparation guide and compact contest sheet, with external references, math/geometry formulas, and 19 marked GNU C++17 snippets. Added synchronized header generation and boundary/oracle checks; preserved all historical implementations.


## 2026-10-17T00:35:20+00:00 — REVIEW

- solutions/prefix-sums/I_Swap_Mohamed_Mohamed.cpp → solutions/prefix-sums/I_Swap_Mohamed_Mohamed.cpp: Reviewed implementation imported from origin/main at 5391667: Combines prefix and suffix counts and cumulative costs; retains the newer remote include change. Category: prefix-sums; status: reviewed.
- solutions/bit-manipulation/A_And_Zero.cpp → solutions/bit-manipulation/A_And_Zero.cpp: Reviewed implementation imported from origin/main at 5391667: Counts zero bits below the most significant bit and prints a power of two. Category: bit-manipulation; status: reviewed.
- solutions/sorting-and-searching/A_Cups_of_Cocoa.cpp → solutions/greedy/A_Cups_of_Cocoa.cpp: Reviewed implementation imported from origin/main at 5391667: Sorts heights and accumulates the minimum additional cooling steps. Category: greedy; status: reviewed.
- solutions/needs-review/A_Einstein_s_Calculator.py → solutions/math/arithmetic/A_Einstein_s_Calculator.py: Reviewed implementation imported from origin/main at 5391667: Builds and evaluates an arithmetic expression; preserves the existing draft without inferring correctness. Category: math/arithmetic; status: reviewed.
- solutions/needs-review/A_OR_what.cpp → solutions/arrays-and-counting/A_OR_what.cpp: Reviewed implementation imported from origin/main at 5391667: Scans all values for their minimum. Category: arrays-and-counting; status: reviewed.
- solutions/strings/A_Opening_Ceremony.cpp → solutions/geometry/A_Opening_Ceremony.cpp: Reviewed implementation imported from origin/main at 5391667: Compares coordinate distances via the two boundary columns. Category: geometry; status: reviewed.
- solutions/needs-review/A_Race.cpp → solutions/math/arithmetic/A_Race.cpp: Reviewed implementation imported from origin/main at 5391667: Computes the first catch-up step from initial positions and relative speeds. Category: math/arithmetic; status: reviewed.
- solutions/binary-search/B_Cubes_Sum.cpp → solutions/math/arithmetic/B_Cubes_Sum.cpp: Reviewed implementation imported from origin/main at 5391667: Binary searches integer cube roots and applies the sum-of-cubes formula modulo MOD. Category: math/arithmetic; status: reviewed.
- solutions/binary-search/B_Cubes_Sum.py → solutions/math/arithmetic/B_Cubes_Sum.py: Reviewed implementation imported from origin/main at 5391667: Binary searches integer cube roots and applies the sum-of-cubes formula. Category: math/arithmetic; status: reviewed.
- solutions/needs-review/B_Ski_Buddy.cpp → solutions/brute-force-and-backtracking/B_Ski_Buddy.cpp: Reviewed implementation imported from origin/main at 5391667: Enumerates starting positions and simulates travel time for each. Category: brute-force-and-backtracking; status: reviewed.
- solutions/needs-review/B_Supply_Chain.cpp → solutions/math/arithmetic/B_Supply_Chain.cpp: Reviewed implementation imported from origin/main at 5391667: Uses total demand and its maximum to calculate a quotient. Category: math/arithmetic; status: reviewed.
- solutions/needs-review/B_Tab_Closing.cpp → solutions/math/arithmetic/B_Tab_Closing.cpp: Reviewed implementation imported from origin/main at 5391667: Chooses one or two operations using capacity and width inequalities. Category: math/arithmetic; status: reviewed.
- solutions/needs-review/B_Weird_Function.cpp → solutions/constructive/B_Weird_Function.cpp: Reviewed implementation imported from origin/main at 5391667: Constructs the pair one and n minus one. Category: constructive; status: reviewed.
- solutions/bit-manipulation/B_XOR_Array.cpp → solutions/bit-manipulation/B_XOR_Array.cpp: Reviewed implementation imported from origin/main at 5391667: Updates the full-array XOR by removing and replacing the affected value. Category: bit-manipulation; status: reviewed.
- solutions/sorting-and-searching/C_Ancient_History_Easy.cpp → solutions/two-pointers-and-sliding-window/C_Ancient_History_Easy.cpp: Reviewed implementation imported from origin/main at 5391667: Sorts values and uses inward pointers to count pairs satisfying the triangle inequality. Category: two-pointers-and-sliding-window; status: reviewed.
- solutions/math/number-theory/C_Equality.cpp → solutions/math/number-theory/C_Equality.cpp: Reviewed implementation imported from origin/main at 5391667: Computes modular exponentiation of n to the nth power. Category: math/number-theory; status: reviewed.
- solutions/prefix-sums/C_Frosted_Highway.cpp → solutions/prefix-sums/C_Frosted_Highway.cpp: Reviewed implementation imported from origin/main at 5391667: Builds prefix counts of positions coprime to their values and answers interval queries. Category: prefix-sums; status: reviewed.
- solutions/bit-manipulation/C_Olympic_Haircut.cpp → solutions/brute-force-and-backtracking/C_Olympic_Haircut.cpp: Reviewed implementation imported from origin/main at 5391667: Enumerates subsets with bit masks to minimize the positive remaining budget. Category: brute-force-and-backtracking; status: reviewed.
- solutions/needs-review/C_Rare_Function.cpp → solutions/math/number-theory/C_Rare_Function.cpp: Reviewed implementation imported from origin/main at 5391667: Checks remainder constraints for divisors from two through n. Category: math/number-theory; status: reviewed.
- solutions/bit-manipulation/C_Yet_another_XOR_problem.cpp → solutions/prefix-sums/C_Yet_another_XOR_problem.cpp: Reviewed implementation imported from origin/main at 5391667: Builds prefix XOR states and answers queries using a periodic index. Category: prefix-sums; status: reviewed.
- solutions/needs-review/D_All_AND.cpp → solutions/bit-manipulation/D_All_AND.cpp: Reviewed implementation imported from origin/main at 5391667: Inserts bits of n minus one into the unset positions of x. Category: bit-manipulation; status: reviewed.
- solutions/dynamic-programming/general/D_Clock_Strikes_Twelve.cpp → solutions/dynamic-programming/knapsack/D_Clock_Strikes_Twelve.cpp: Reviewed implementation imported from origin/main at 5391667: Unbounded two-resource knapsack minimizing the number of items. Category: dynamic-programming/knapsack; status: reviewed.
- solutions/sorting-and-searching/D_Daydream.cpp → solutions/arrays-and-counting/D_Daydream.cpp: Reviewed implementation imported from origin/main at 5391667: Computes the mex and tests frequency conditions on zero and one. Category: arrays-and-counting; status: reviewed.
- solutions/math/number-theory/D_Revenge_of_the_C_K_or_e_ys.cpp → solutions/math/combinatorics/D_Revenge_of_the_C_K_or_e_ys.cpp: Reviewed implementation imported from origin/main at 5391667: Computes a ratio of binomial coefficients using factorials and modular inverses. Category: math/combinatorics; status: reviewed.
- solutions/sorting-and-searching/D_Snowball.cpp → solutions/prefix-sums/D_Snowball.cpp: Reviewed implementation imported from origin/main at 5391667: Accumulates damage contributions in forward and backward scans before choosing a split. Category: prefix-sums; status: reviewed.
- solutions/strings/D_String_Game.cpp → solutions/data-structures/stacks-and-queues/D_String_Game.cpp: Reviewed implementation imported from origin/main at 5391667: Uses a character stack to remove matching suffixes and checks removal-count parity. Category: data-structures/stacks-and-queues; status: reviewed.
- solutions/binary-search/E_Feed_the_Beast.cpp → solutions/binary-search/E_Feed_the_Beast.cpp: Reviewed implementation imported from origin/main at 5391667: Binary searches the largest quantity satisfying a monotone ceiling-cost budget check. Category: binary-search; status: reviewed.
- solutions/needs-review/E_Max_Subarray_Sum.cpp → solutions/dynamic-programming/kadane/E_Max_Subarray_Sum.cpp: Reviewed implementation imported from origin/main at 5391667: Finds the minimum subarray using a Kadane recurrence and subtracts it from the total. Category: dynamic-programming/kadane; status: reviewed.
- solutions/dynamic-programming/general/E_Minimum_Score.cpp → solutions/dynamic-programming/general/E_Minimum_Score.cpp: Reviewed implementation imported from origin/main at 5391667: Precomputes minimum scores using predecessor and multiple-based DP relaxations. Category: dynamic-programming/general; status: reviewed.
- solutions/dynamic-programming/general/E_Screenmaxxing.cpp → solutions/trees/E_Screenmaxxing.cpp: Reviewed implementation imported from origin/main at 5391667: DFS computes subtree sums and evaluates the best edge partition. Category: trees; status: reviewed.
- solutions/needs-review/E_Snowfake.cpp → solutions/geometry/E_Snowfake.cpp: Reviewed implementation imported from origin/main at 5391667: Checks multiplicities under the coordinate transformation minus y and x plus y. Category: geometry; status: reviewed.
- solutions/needs-review/E_Traffic_Light.cpp → solutions/dynamic-programming/sequences/E_Traffic_Light.cpp: Reviewed implementation imported from origin/main at 5391667: Maintains best subsequence lengths ending in each of three cyclic color states. Category: dynamic-programming/sequences; status: reviewed.
- solutions/math/number-theory/F_Divisors_Count.cpp → solutions/math/number-theory/F_Divisors_Count.cpp: Reviewed implementation imported from origin/main at 5391667: Sieves divisor counts, forms prefix maxima, and lower-bounds the required count. Category: math/number-theory; status: reviewed.
- solutions/binary-search/F_Frosted_Highway_Hard.cpp → solutions/math/number-theory/F_Frosted_Highway_Hard.cpp: Reviewed implementation imported from origin/main at 5391667: Indexes positions by divisors of gcd values and answers intervals with sorted bounds. Category: math/number-theory; status: reviewed.
- solutions/data-structures/disjoint-set/G_The_Veneto_Relay.cpp → solutions/binary-search/G_The_Veneto_Relay.cpp: Reviewed implementation imported from origin/main at 5391667: Binary searches an edge-weight threshold and uses union find to check milestone connectivity. Category: binary-search; status: reviewed.

## 2026-10-17T00:35:19+00:00 — INGEST

- solutions/prefix-sums/I_Swap_Mohamed_Mohamed.cpp → solutions/prefix-sums/I_Swap_Mohamed_Mohamed.cpp: Reclassified changed source using current implementation signals. Category: prefix-sums; status: suggested.
- A_And_Zero.cpp → solutions/bit-manipulation/A_And_Zero.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- A_Cups_of_Cocoa.cpp → solutions/sorting-and-searching/A_Cups_of_Cocoa.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- A_Einstein_s_Calculator.py → solutions/needs-review/A_Einstein_s_Calculator.py: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- A_OR_what.cpp → solutions/needs-review/A_OR_what.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- A_Opening_Ceremony.cpp → solutions/strings/A_Opening_Ceremony.cpp: Filed new source; classification remains a suggestion. Category: strings; status: suggested.
- A_Race.cpp → solutions/needs-review/A_Race.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_Cubes_Sum.cpp → solutions/binary-search/B_Cubes_Sum.cpp: Filed new source; classification remains a suggestion. Category: binary-search; status: suggested.
- B_Cubes_Sum.py → solutions/binary-search/B_Cubes_Sum.py: Filed new source; classification remains a suggestion. Category: binary-search; status: suggested.
- B_Ski_Buddy.cpp → solutions/needs-review/B_Ski_Buddy.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_Supply_Chain.cpp → solutions/needs-review/B_Supply_Chain.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_Tab_Closing.cpp → solutions/needs-review/B_Tab_Closing.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_Weird_Function.cpp → solutions/needs-review/B_Weird_Function.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- B_XOR_Array.cpp → solutions/bit-manipulation/B_XOR_Array.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- C_Ancient_History_Easy.cpp → solutions/sorting-and-searching/C_Ancient_History_Easy.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- C_Equality.cpp → solutions/math/number-theory/C_Equality.cpp: Filed new source; classification remains a suggestion. Category: math/number-theory; status: suggested.
- C_Frosted_Highway.cpp → solutions/prefix-sums/C_Frosted_Highway.cpp: Filed new source; classification remains a suggestion. Category: prefix-sums; status: suggested.
- C_Olympic_Haircut.cpp → solutions/bit-manipulation/C_Olympic_Haircut.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- C_Rare_Function.cpp → solutions/needs-review/C_Rare_Function.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- C_Yet_another_XOR_problem.cpp → solutions/bit-manipulation/C_Yet_another_XOR_problem.cpp: Filed new source; classification remains a suggestion. Category: bit-manipulation; status: suggested.
- D_All_AND.cpp → solutions/needs-review/D_All_AND.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- D_Clock_Strikes_Twelve.cpp → solutions/dynamic-programming/general/D_Clock_Strikes_Twelve.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- D_Daydream.cpp → solutions/sorting-and-searching/D_Daydream.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- D_Revenge_of_the_C_K_or_e_ys.cpp → solutions/math/number-theory/D_Revenge_of_the_C_K_or_e_ys.cpp: Filed new source; classification remains a suggestion. Category: math/number-theory; status: suggested.
- D_Snowball.cpp → solutions/sorting-and-searching/D_Snowball.cpp: Filed new source; classification remains a suggestion. Category: sorting-and-searching; status: suggested.
- D_String_Game.cpp → solutions/strings/D_String_Game.cpp: Filed new source; classification remains a suggestion. Category: strings; status: suggested.
- E_Feed_the_Beast.cpp → solutions/binary-search/E_Feed_the_Beast.cpp: Filed new source; classification remains a suggestion. Category: binary-search; status: suggested.
- E_Max_Subarray_Sum.cpp → solutions/needs-review/E_Max_Subarray_Sum.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- E_Minimum_Score.cpp → solutions/dynamic-programming/general/E_Minimum_Score.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- E_Screenmaxxing.cpp → solutions/dynamic-programming/general/E_Screenmaxxing.cpp: Filed new source; classification remains a suggestion. Category: dynamic-programming/general; status: suggested.
- E_Snowfake.cpp → solutions/needs-review/E_Snowfake.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- E_Traffic_Light.cpp → solutions/needs-review/E_Traffic_Light.cpp: Filed new source; classification remains a suggestion. Category: needs-review; status: needs-review.
- F_Divisors_Count.cpp → solutions/math/number-theory/F_Divisors_Count.cpp: Filed new source; classification remains a suggestion. Category: math/number-theory; status: suggested.
- F_Frosted_Highway_Hard.cpp → solutions/binary-search/F_Frosted_Highway_Hard.cpp: Filed new source; classification remains a suggestion. Category: binary-search; status: suggested.
- G_The_Veneto_Relay.cpp → solutions/data-structures/disjoint-set/G_The_Veneto_Relay.cpp: Filed new source; classification remains a suggestion. Category: data-structures/disjoint-set; status: suggested.

## 2026-10-17T00:07:27+00:00 — SETUP

Added INGEST / QUERY / LINT workflows, preserved existing classifications, established hash tracking, and linked 13 implementations to four canonical pattern notes.

