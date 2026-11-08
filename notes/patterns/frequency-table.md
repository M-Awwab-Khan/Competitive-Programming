# Frequency tables and distinct-value counting

Replace positions with multiplicities: count each value (or a derived key) once, then answer the question from the count table instead of from pairwise comparisons.

## Recognition clues

- The answer depends only on *how many times* each value appears, not on order: modes, "can the letters be rearranged into…", pairs of equal values, distinct counts.
- A pair condition `f(i, j)` separates into `key(i) == key'(j)`: `a_j - a_i = j - i` becomes `a_i - i == a_j - j`; "sum to `x`" becomes "is `x - a_i` already present"; `a_i & a_j >= a_i ^ a_j` becomes "same most significant bit".
- Values are small (letters, residues mod `m`, values `<= 10^6`), so an array of counters fits.
- "Multiset A can supply multiset B", "minimum changes so all equal", "remove duplicates", "first to reach the maximum".

## Invariant and variants

After a prefix scan, `cnt[k]` equals the number of processed items with key `k`. Counting *before* inserting the current item gives exactly the pairs `(i, j)` with `i < j`:

```text
for j in 0..n-1:
    answer += cnt[key(j)]      // earlier partners only
    cnt[key(j)] += 1
```

| Variant | Derived quantity | Repo illustration |
| --- | --- | --- |
| Equal-key pairs | `sum C(c, 2)` or the online loop above | `same-differences.py` (key `a_i - i`), `W_Rock_and_Lever.cpp` (key = msb) |
| Complement lookup | seen-map `value -> index`, test `target - a_i` | `sum_of_two_values.cpp` |
| Multiset containment | `need[c] <= have[c]` for every key; `sum min(have, need)` | `B_Letter.cpp`, `B_Garland.cpp`, `F_Mastering_Mastermind.cpp` |
| Mode / change-to-equal | `n - max cnt`; arrangeable iff `max cnt <= (n + 1) / 2` | `A_Penchick_and_Modern_Monument.cpp`, `A_Yaroslav_and_Permutations.cpp` |
| Residue buckets | pair class `r` with `m - r`; `0` and `m/2` are self-paired | `B_M_Arrays.cpp`, `B_Merge_it.cpp`, `F_3_SUM.cpp` |
| Palindrome by parity of counts | at most one odd count | `palindrome_reorder.cpp`, `A_k_String.cpp` (divisible by `k`) |
| Distinct count | `set` / `unordered_set` size; suffix distinct via right-to-left set | `cses-distinctnumbers.cpp`, `B_Sereja_and_Suffixes.cpp` |
| Counts over multiples | `sum cnt[kd]` for every `d` in `O(M log M)` | `cses-commondivisors.cpp`, `cf-wewerebothchildren.cpp` |
| Live count of "bad" keys | maintain how many keys have `cnt >= 2` while updating | `atcoder-pigeonhole-query.cpp` |

Complexity: `O(n)` with an array of size `M` (plus `O(M)` memory) or expected `O(n)` with a hash map; `O(n log n)` with `map`/`set`. When the window of counted items slides, this becomes a [two-pointer window](two-pointer-window.md) with a count map.

## Common mistakes

- Indexing a fixed array by an unbounded value: `kattis-jollyjumpers.cpp` marks `b[|a_i - a_{i+1}|]` in an array of size `n`, which overflows when a difference is `>= n`. Bound-check or use a map.
- Counting a pair twice (or an item with itself) when the key relation is symmetric: `USACO_Cities_and_States.py` halves the total and skips keys where city prefix equals state.
- Equal-key pair counts overflow `int` (`C(2*10^5, 2)` is about `2*10^10`).
- Ties for the mode: "first to reach the maximum" needs a second pass over the original order (`A_Voting_for_Photos.cpp`, `cf-A_Winner.cpp`).
- `unordered_map` with adversarial keys can degrade; use `map` or a custom hash on hacked platforms.
- Rebuilding a frequency map per query (`cta.cpp`) is `O(n)` per query; precompute or use offline techniques when queries are many.

## Related patterns

When the key is a prefix state rather than a single element, use [prefix sums with a frequency map](prefix-sum-frequency-map.md). Counting pairs under a complement or inequality constraint is covered by [pair counting with inclusion-exclusion](pair-counting-inclusion-exclusion.md) and [binomial counting](binomial-counting.md). Residue buckets connect to [modular arithmetic](modular-arithmetic.md), sorted counts to [sort-then-greedy](sort-then-greedy.md), and multiple-sums to [divisor enumeration](divisor-enumeration.md). Return to the [pattern hub](INDEX.md).

<!-- examples:start -->

## Examples from this repository

Links are generated from catalog associations; classifications do not establish correctness.

| Implementation | Category | Classification |
| --- | --- | --- |
| [A Elections (cpp)](../../solutions/arrays-and-counting/A_Elections.cpp) | arrays-and-counting | reviewed |
| [A Free Cash (cpp)](../../solutions/arrays-and-counting/A_Free_Cash.cpp) | arrays-and-counting | reviewed |
| [A k String (cpp)](../../solutions/strings/A_k_String.cpp) | strings | reviewed |
| [A Milya and Two Arrays (cpp)](../../solutions/arrays-and-counting/A_Milya_and_Two_Arrays.cpp) | arrays-and-counting | reviewed |
| [A Penchick and Modern Monument (cpp)](../../solutions/arrays-and-counting/A_Penchick_and_Modern_Monument.cpp) | arrays-and-counting | reviewed |
| [A String (cpp)](../../solutions/strings/A_String.cpp) | strings | reviewed |
| [A Xenia and Divisors (cpp)](../../solutions/math/number-theory/A_Xenia_and_Divisors.cpp) | math/number-theory | reviewed |
| [A Yaroslav and Permutations (cpp)](../../solutions/arrays-and-counting/A_Yaroslav_and_Permutations.cpp) | arrays-and-counting | reviewed |
| [A. Maximum of n Integers (cpp)](../../solutions/arrays-and-counting/A_Maximum_of_n_Integers.cpp) | arrays-and-counting | reviewed |
| [A. Twice (cpp)](../../solutions/arrays-and-counting/A_Twice.cpp) | arrays-and-counting | reviewed |
| [A. Voting for Photos (cpp)](../../solutions/arrays-and-counting/A_Voting_for_Photos.cpp) | arrays-and-counting | reviewed |
| [A. Vowels (python)](../../solutions/strings/A_Vowels.py) | strings | reviewed |
| [AA - Satyam and Counting (cpp)](../../solutions/math/combinatorics/AA_Satyam_and_Counting.cpp) | math/combinatorics | reviewed |
| [at removeminedges (cpp)](../../solutions/arrays-and-counting/at-removeminedges.cpp) | arrays-and-counting | reviewed |
| [atcoder pigeonhole query (cpp)](../../solutions/arrays-and-counting/atcoder-pigeonhole-query.cpp) | arrays-and-counting | reviewed |
| [B - Perfect (cpp)](../../solutions/arrays-and-counting/B_Perfect.cpp) | arrays-and-counting | reviewed |
| [B A and B and Compilation Errors (cpp)](../../solutions/data-structures/ordered-sets/B_A_and_B_and_Compilation_Errors.cpp) | data-structures/ordered-sets | reviewed |
| [B Amr and The Large Array (cpp)](../../solutions/arrays-and-counting/B_Amr_and_The_Large_Array.cpp) | arrays-and-counting | reviewed |
| [B Football Kit (cpp)](../../solutions/arrays-and-counting/B_Football_Kit.cpp) | arrays-and-counting | reviewed |
| [B Garland (cpp)](../../solutions/arrays-and-counting/B_Garland.cpp) | arrays-and-counting | reviewed |
| [B Having Been a Treasurer in the Past I Help Goblins Deceive (cpp)](../../solutions/math/combinatorics/B_Having_Been_a_Treasurer_in_the_Past_I_Help_Goblins_Deceive.cpp) | math/combinatorics | reviewed |
| [B Jeff and Periods (cpp)](../../solutions/arrays-and-counting/B_Jeff_and_Periods.cpp) | arrays-and-counting | reviewed |
| [B Letter (cpp)](../../solutions/strings/B_Letter.cpp) | strings | reviewed |
| [B M Arrays (cpp)](../../solutions/greedy/B_M_Arrays__0a29afd8.cpp) | greedy | reviewed |
| [B M Arrays (cpp)](../../solutions/math/number-theory/B_M_Arrays.cpp) | math/number-theory | reviewed |
| [B Pashmak and Flowers (cpp)](../../solutions/math/combinatorics/B_Pashmak_and_Flowers.cpp) | math/combinatorics | reviewed |
| [B Sereja and Suffixes (cpp)](../../solutions/prefix-sums/B_Sereja_and_Suffixes.cpp) | prefix-sums | reviewed |
| [B. An Operational Problem (cpp)](../../solutions/math/number-theory/B_An_Operational_Problem.cpp) | math/number-theory | reviewed |
| [B. Intercepted Inputs (cpp)](../../solutions/arrays-and-counting/B_Intercepted_Inputs.cpp) | arrays-and-counting | reviewed |
| [B. Merge it! (cpp)](../../solutions/greedy/B_Merge_it.cpp) | greedy | reviewed |
| [B. Valerii Against Everyone (cpp)](../../solutions/arrays-and-counting/B_Valerii_Against_Everyone.cpp) | arrays-and-counting | reviewed |
| [B. Variety is Discouraged (cpp)](../../solutions/two-pointers-and-sliding-window/B_Variety_is_Discouraged.cpp) | two-pointers-and-sliding-window | reviewed |
| [B. Vera And LCS (python)](../../solutions/constructive/B_Vera_And_LCS.py) | constructive | reviewed |
| [baloni (cpp)](../../solutions/greedy/baloni.cpp) | greedy | reviewed |
| [boredom (cpp)](../../solutions/dynamic-programming/sequences/boredom.cpp) | dynamic-programming/sequences | reviewed |
| [C - AtCoder Riko (cpp)](../../solutions/math/number-theory/C_AtCoder_Riko.cpp) | math/number-theory | reviewed |
| [C - Made Up (cpp)](../../solutions/arrays-and-counting/C_Made_Up.cpp) | arrays-and-counting | reviewed |
| [C They Are Everywhere (cpp)](../../solutions/two-pointers-and-sliding-window/C_They_Are_Everywhere.cpp) | two-pointers-and-sliding-window | reviewed |
| [C. Assembly via Minimums (cpp)](../../solutions/constructive/C_Assembly_via_Minimums.cpp) | constructive | reviewed |
| [C. Preparing for the Exam (cpp)](../../solutions/arrays-and-counting/C_Preparing_for_the_Exam.cpp) | arrays-and-counting | reviewed |
| [cf A Winner (cpp)](../../solutions/arrays-and-counting/cf-A_Winner.cpp) | arrays-and-counting | reviewed |
| [cf B Appleman and Card Game (cpp)](../../solutions/greedy/cf-B_Appleman_and_Card_Game.cpp) | greedy | reviewed |
| [cf gorilla and the exam (cpp)](../../solutions/greedy/cf-gorilla-and-the-exam.cpp) | greedy | reviewed |
| [cf notquiteapalindromicstring (cpp)](../../solutions/strings/cf_notquiteapalindromicstring.cpp) | strings | reviewed |
| [cf numeric strings template  (cpp)](../../solutions/strings/cf-numeric-strings-template-.cpp) | strings | reviewed |
| [cf three problems (cpp)](../../solutions/sorting-and-searching/cf-three-problems.cpp) | sorting-and-searching | reviewed |
| [cf wewerebothchildren (cpp)](../../solutions/math/number-theory/cf-wewerebothchildren.cpp) | math/number-theory | reviewed |
| [cses commondivisors (cpp)](../../solutions/math/number-theory/cses-commondivisors.cpp) | math/number-theory | reviewed |
| [cses distinctnumbers (cpp)](../../solutions/arrays-and-counting/cses-distinctnumbers.cpp) | arrays-and-counting | reviewed |
| [cta (cpp)](../../solutions/arrays-and-counting/cta.cpp) | arrays-and-counting | reviewed |
| [D - Subarray Distinct Values (cpp)](../../solutions/two-pointers-and-sliding-window/D_Subarray_Distinct_Values.cpp) | two-pointers-and-sliding-window | reviewed |
| [D Daydream (cpp)](../../solutions/arrays-and-counting/D_Daydream.cpp) | arrays-and-counting | reviewed |
| [D Divide And Equalize (cpp)](../../solutions/math/number-theory/D_Divide_And_Equalize.cpp) | math/number-theory | reviewed |
| [D Divisble Pairs (cpp)](../../solutions/math/number-theory/D_Divisble_Pairs.cpp) | math/number-theory | reviewed |
| [D. A Linear Problem (cpp)](../../solutions/geometry/D_A_Linear_Problem.cpp) | geometry | reviewed |
| [D. Harder Problem (cpp)](../../solutions/constructive/D_Harder_Problem.cpp) | constructive | reviewed |
| [D. Palindromes Coloring (cpp)](../../solutions/strings/D_Palindromes_Coloring.cpp) | strings | reviewed |
| [dont be last (python)](../../solutions/sorting-and-searching/dont-be-last.py) | sorting-and-searching | reviewed |
| [E Indian Summer (cpp)](../../solutions/strings/E_Indian_Summer.cpp) | strings | reviewed |
| [E Snowfake (cpp)](../../solutions/geometry/E_Snowfake.cpp) | geometry | reviewed |
| [eww (python)](../../solutions/arrays-and-counting/eww.py) | arrays-and-counting | reviewed |
| [F Mastering Mastermind (cpp)](../../solutions/arrays-and-counting/F_Mastering_Mastermind.cpp) | arrays-and-counting | reviewed |
| [F. 3SUM (cpp)](../../solutions/brute-force-and-backtracking/F_3_SUM.cpp) | brute-force-and-backtracking | reviewed |
| [G. Matching (cpp)](../../solutions/greedy/G_Matching.cpp) | greedy | reviewed |
| [G1. Into Blocks (easy version) (cpp)](../../solutions/greedy/G_1_Into_Blocks_easy_version.cpp) | greedy | reviewed |
| [gameOfDivision (python)](../../solutions/games/gameOfDivision.py) | games | reviewed |
| [H - Shadow Sum (cpp)](../../solutions/arrays-and-counting/H_Shadow_Sum.cpp) | arrays-and-counting | reviewed |
| [k distinct subarrays (python)](../../solutions/two-pointers-and-sliding-window/k_distinct_subarrays.py) | two-pointers-and-sliding-window | reviewed |
| [K. Equal subsequence (cpp)](../../solutions/arrays-and-counting/K_Equal_subsequence.cpp) | arrays-and-counting | reviewed |
| [kattis acm (cpp)](../../solutions/simulation/kattis-acm.cpp) | simulation | reviewed |
| [kattis bitsequalizer (cpp)](../../solutions/greedy/kattis-bitsequalizer.cpp) | greedy | reviewed |
| [kattis jollyjumpers (cpp)](../../solutions/arrays-and-counting/kattis-jollyjumpers.cpp) | arrays-and-counting | reviewed |
| [kattis memorymatch (cpp)](../../solutions/simulation/kattis-memorymatch.cpp) | simulation | reviewed |
| [kattis pokerhand (cpp)](../../solutions/arrays-and-counting/kattis-pokerhand.cpp) | arrays-and-counting | reviewed |
| [kattis vote (cpp)](../../solutions/arrays-and-counting/kattis-vote.cpp) | arrays-and-counting | reviewed |
| [Number of Equal (cpp)](../../solutions/arrays-and-counting/Number_of_Equal.cpp) | arrays-and-counting | reviewed |
| [palindrome reorder (cpp)](../../solutions/strings/palindrome_reorder.cpp) | strings | reviewed |
| [phoenix and socks (python)](../../solutions/greedy/phoenix_and_socks.py) | greedy | reviewed |
| [registration system (python)](../../solutions/strings/registration_system.py) | strings | reviewed |
| [same differences (python)](../../solutions/arrays-and-counting/same-differences.py) | arrays-and-counting | reviewed |
| [sequence pair weight (python)](../../solutions/arrays-and-counting/sequence_pair_weight.py) | arrays-and-counting | reviewed |
| [smallest subarray (cpp)](../../solutions/two-pointers-and-sliding-window/smallest_subarray.cpp) | two-pointers-and-sliding-window | reviewed |
| [sum of two values (cpp)](../../solutions/sorting-and-searching/sum_of_two_values.cpp) | sorting-and-searching | reviewed |
| [sum of two values (python)](../../solutions/sorting-and-searching/sum_of_two_values.py) | sorting-and-searching | reviewed |
| [troc thereisabear (cpp)](../../solutions/arrays-and-counting/troc-thereisabear.cpp) | arrays-and-counting | reviewed |
| [USACO Block Game (cpp)](../../solutions/arrays-and-counting/USACO_Block_Game.cpp) | arrays-and-counting | reviewed |
| [USACO Bovine Genomics (cpp)](../../solutions/brute-force-and-backtracking/USACO_Bovine_Genomics.cpp) | brute-force-and-backtracking | reviewed |
| [USACO Cities and States (python)](../../solutions/arrays-and-counting/USACO_Cities_and_States.py) | arrays-and-counting | reviewed |
| [USACO Don t Be Last (cpp)](../../solutions/sorting-and-searching/USACO_Don_t_Be_Last.cpp) | sorting-and-searching | reviewed |
| [uva smallest subarray (python)](../../solutions/two-pointers-and-sliding-window/uva-smallest-subarray.py) | two-pointers-and-sliding-window | reviewed |
| [W - Rock and Lever (cpp)](../../solutions/bit-manipulation/W_Rock_and_Lever.cpp) | bit-manipulation | reviewed |
| [X - All Pairs Segments (cpp)](../../solutions/math/combinatorics/X_All_Pairs_Segments.cpp) | math/combinatorics | reviewed |
| [yellowandredcard (cpp)](../../solutions/arrays-and-counting/yellowandredcard.cpp) | arrays-and-counting | reviewed |

<!-- examples:end -->
