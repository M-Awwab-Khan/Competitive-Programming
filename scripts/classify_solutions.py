"""Conservative category suggestions from local source and curated title patterns.

Shared competitive-programming boilerplate is removed before inspecting code.
Suggestions carry their evidence; they do not claim a judge verdict.
"""
import re
import ast
from pathlib import Path

CATEGORIES = {
    'arrays-and-counting': 'Arrays, frequency counting, sets, and direct scans',
    'binary-search': 'Binary search on sorted data or a monotone answer',
    'bit-manipulation': 'Bitwise operations, XOR identities, and bit counting',
    'brute-force-and-backtracking': 'Enumeration, subset search, and backtracking',
    'constructive': 'Constructing a valid array, permutation, or arrangement',
    'data-structures/disjoint-set': 'Disjoint set union and component merging',
    'data-structures/heaps': 'Priority queues and heap based selection',
    'data-structures/ordered-sets': 'Ordered sets, multisets, and order statistics',
    'data-structures/range-queries': 'Segment trees, Fenwick trees, and sparse tables',
    'data-structures/stacks-and-queues': 'Stacks, deques, and monotonic structures',
    'dynamic-programming/bitmask': 'Dynamic programming over subsets',
    'dynamic-programming/knapsack': 'Subset sum, coin change, and knapsack states',
    'dynamic-programming/sequences': 'Subsequence and string dynamic programming',
    'dynamic-programming/intervals': 'Dynamic programming over intervals',
    'dynamic-programming/general': 'Other dynamic programming recurrences',
    'games': 'Winning states, parity games, and strategy',
    'geometry': 'Coordinates, distances, intersections, and areas',
    'graphs/traversal': 'Graph search, components, grids, and reachability',
    'graphs/shortest-paths': 'Shortest path and breadth first distance problems',
    'graphs/spanning-trees': 'Minimum or maximum spanning trees',
    'graphs/topological-sort': 'Dependency ordering and DAG algorithms',
    'greedy': 'Local choices, scheduling, and exchange arguments',
    'intervals': 'Interval overlap, coverage, and endpoint constraints',
    'dynamic-programming/kadane': 'Maximum subarray sums and Kadane style recurrences',
    'math/arithmetic': 'Formulas, parity, digit arithmetic, and algebra',
    'math/combinatorics': 'Combinatorial counting, factorials, and binomial coefficients',
    'math/number-theory': 'GCD, primes, factorization, divisibility, and modular arithmetic',
    'prefix-sums': 'Prefix/suffix aggregates, differences, and prefix sum hashing',
    'recursion-and-divide-and-conquer': 'Recursive decomposition and divide and conquer',
    'simulation': 'Direct simulation of rules, grids, and processes',
    'sorting-and-searching': 'Sorting, rank queries, and sorted order reasoning',
    'strings': 'String matching, parsing, and character transformations',
    'ternary-search': 'Searching a unimodal function',
    'trees': 'Tree traversal, subtree queries, and tree properties',
    'two-pointers-and-sliding-window': 'Moving boundaries, fixed/variable windows, and merging',
    'needs-review': 'Insufficient evidence for a specific pattern',
}

# Deliberately specific fragments; a problem title alone does not imply acceptance.
TITLE_RULES = [
 ('dynamic-programming/bitmask', ['elevator-rides', 'g-matching']),
 ('dynamic-programming/intervals', ['n-slimes', 'l-deque', 'removalgame', 'rectanglecutting', 'c-mixtures']),
 ('dynamic-programming/knapsack', ['knapsack-1', 'knapsack-2', 'the-knapsack-problem', 'subset-sum-dp', 'bookshop', 'coincombinations', 'minimizingcoins', 'moneysums', 'modulo-sum', 'cut-ribbon', 'crested-ibis', 'k-subset-sums']),
 ('dynamic-programming/sequences', ['lcs', 'longest-common-subsequence', 'cses-lis', 'increasing-subsequence', 'make-them-equal']),
 ('dynamic-programming/general', ['frog-1', 'frog-2', 'grid-1', 'c-vacation', 'coins', 'm-candies', 'k-stones', 'dicecombinations', 'removingdigits', 'flight-planner', 'walking-on-the-safe-side', 'typical-stairs', 'dice-roll-sequence', 'tribonacci', 'recursion-fibonacci']),
 ('graphs/spanning-trees', ['max-spanning-tree']),
 ('graphs/topological-sort', ['cses-gameroutes', 'chokutter-addiction']),
 ('graphs/shortest-paths', ['two-buttons', 'e-labyrinth', 'd-min-path']),
 ('graphs/traversal', ['counting-rooms', 'count-simple-paths', 'i-maze', 'bipartize', 'graphcycles', 'graph-subchain', 'milk-factory', 'great-revegetation', 'mad-city', 'adjacency-matrix']),
 ('trees', ['subtreequeries', 'subordinates', 'kefa-and-park', 'arboris-contractio', 'decorating-christmas-tree', 'destruction-of-the-dandelion', 'danil-and-a-part-time', 'tree']),
 ('data-structures/disjoint-set', ['knight-tournament', 'districts-connection', 'roads-not-only-in-berland', 'dzy-loves-chemistry', 'join-states']),
 ('data-structures/range-queries', ['xenia-and-bit-operations', 'distinct-characters-queries', 'swap-and-range-sum', 'ant-colony', 'sparse-range']),
 ('two-pointers-and-sliding-window', ['sliding-window', 'slidingwindow', 'good-sets', 'kefa-and-company', 'they-are-everywhere', 'vasya-and-string', 'subarray-distinct', 'cses-playlist', 'smallest-subarray', 'diamond-collector', 'subarray-sum-x', 'k-distinct-subarrays', 'three-parts-of-the-array', 'money-trees', 'black-and-white-stripe', 'the-sound-of-silence', 'very-different-array', 'merging-sorted-list', 'cf-books', 'cf-eatingcandies', 'maximum-sum-subarray-size']),
 ('prefix-sums', ['prefix', 'range-xor', 'static-range-sum', 'subarray-divisibility', 'subarray-sum-equals', 'longest-subarray-with-sum', 'utpc-3-11-g', 'odd-queries', 'kuriyama', 'ilya-and-queries', 'breed-counting', 'counting-haybales', 'haybale-stacking', 'deforestation', 'cses-forestqueries', 'hits-different', 'data-structures-fan', 'sereja-and-suffixes', 'dividing-candies', 'subsequences-summing-to-seven', 'sequence-pair-weight']),
 ('ternary-search', ['meeting-on-the-line', 'building-reconstruction']),
 ('binary-search', ['aggressive-cows', 'burning-midnight-oil', 'interesting-drink', 'drink-accordingly', 'maximum-median', 'maximum-median', 'magic-powder', 'the-wave', 'magic-ship', 'building-an-aquarium', 'cardboard-for-pictures', 'brightness-begins', 'eating-queries', 'queries-about-less', 'the-meeting-place', 'guess-the-k-th-zero', 'counting-points', 'array-division', 'factory-machines', 'poinsnoned-dagger', 'utpc-3-11-a', 'utpc-3-11-e', 'k-th-root', 'limited-repainting', 'cf-cellularnetwork', 'worm', 'klee-s-super', 'eko']),
 ('geometry', ['point-location', 'line-segment-intersection', 'polygon-area', 'circle-lattice', 'closest-pair', 'counting-rectangles', 'white-sheet', 'blocked-billboard', 'square-pasture', 'field-reduction', 'perpendicular-segments', 'fear-of-the-dark', 'amr-and-pins', 'han-solo', 'valuable-resources', 'rudolph-and-christmas-tree', 'two-tables', 'orthogonality', 'integer-moves', 'my-first-geometry', 'lowest-triangle']),
 ('math/combinatorics', ['ncr-with-mod', 'random-teams', 'pashmak-and-flowers', 'and-sequences', 'and-0-sum-big', 'how-many-strings', 'satyam-and-counting', 'two-knights', 'countmultiples']),
 ('math/number-theory', ['gcd', 'divisor', 'prime', 'factorization', 'divide-and-equalize', 'soldier-and-number-game', 'cf-taxes', 'd-taxes', 'diophantine', 'chinese-remainder', 'easy-number-challenge', 'sumofdivisors', 'sum-of-divisors', 'perfect-root', 'sieve-of-erato', 'different-divisors']),
 ('bit-manipulation', ['xor', 'bitwise', 'check-bit', 'flipping-bits', 'and-sorting', 'max-and', 'and-it-s-non-zero', 'powers-of-two', 'red-scarf', 'johnny-and-his-hobbies', 'rock-and-lever', 'and-then-there-were-k', 'sum-vs-xor', 'cat-fox-and-the-lonely-array', 'fedor-and-new-game', 'playing-with-or']),
 ('data-structures/stacks-and-queues', ['nearestsmallervalues', 'globalraining', 'wahban-and-brackets', 'two-brackets']),
 ('data-structures/ordered-sets', ['cses-trafficlights', 'cses-towers', 'cses-josephus2', 'concert-tickets', 'associative-array']),
 ('brute-force-and-backtracking', ['preparing-olympiad', 'petr-and-a-combination', 'meet-in-the-middle', 'maximum-subsequence', 'apple-division', 'creating-strings', 'back-and-forth', 'shower-line', 'three-logos', 'mastermind', 'quiz-forming-teams', 'usaco-air-cownditioning-ii']),
 ('recursion-and-divide-and-conquer', ['tower-of-hanoi', 'gold-rush', 'recursive-digit-sum', 'truckloads']),
 ('games', ['little-girl-and-game', 'simple-game', 'subtractonacci', 'gameofdivision']),
 ('constructive', ['array-divisibility', 'farmer-john-s-challenge', 'find-k-distinct', 'increasing-and-decreasing', 'diverse-game', 'beautiful-array', 'superultra', 'val(i|i)-and-permutation', 'sakurako-and-kosuke', 'permutation-minimization', 'permutations', 'permutation', 'yasoslav', 'yaroslav-and-permutations', 'differential-sorting', 'disappearing-permutation', 'vicious-labyrinth', 'sasha-and-the-drawing', 'ear(n|ning)-on-bets', 'creating-keys-for', 'minimize-equal-sum-subarrays', 'two-sets']),
 ('greedy', ['hit-the-lottery', 'dragons', 'business-trip', 'woodcutters', 'save-the-magazines', 'strange-birthday-party', 'a-knapsack', 'movie-festival', 'moviefestival', 'tasksanddeadline', 'roomallocation', 'cses-readingbooks', 'cses-sticks', 'cses-boxers', 'e-boxers', 'wooden-ladder', 'missing-coin-sum', 'complete-the-projects', 'buying-lemonade', 'boxes-and-candies', 'soldier-and-badges', 'phoenix-and-socks', 'friends-and-the-restaurant', 'apartment', 'ferris-wheel', 'exams', 'vaccination', 'more-cowbell', 'collecting-game', 'c-qu(e|e)sts', 'negatives-and-positives', 'sereja-and-dima', 'bookshelf']),
 ('sorting-and-searching', ['sort', 'rank-list', 'closest-numbers', 'countingpairs', 'counting-pairs', 'sum-of-two-values', 'sumoftwovalues', 'sumofthreevalues', 'sumoffourvalues', 'sum-of-four-values', 'puzzles', 'stable-groups', 'contrast-value', 'playing-in-a-casino', 'bigsorting']),
 ('strings', ['string', 'palindrome', 'cryptogram', 'cryptogram', 'kmp', 'vowels', 'password', 'letter', 'chatroom', 'translation', 'keyboard', 'skibidusnohio', 'way-too-long-words', 'polycarp-and-the-day-of-pi', 'unreadable', 'spelling-check', 'language-detection', 'hate-between', 'where-am-i', 'secret-message', 'unary']),
 ('simulation', ['minesweeper', 'chess', 'robot', 'snap', 'snakesandladders', 'shell-game', 'mixing-milk', 'cow-tipping', 'speeding-ticket', 'cow-signal', 'milking-order', 'swapity-swap', 'gift-exchange', 'bender', 'whatisthecard', 'pigeonhole-query', 'stuck-in-a-timeloop', 'weird-algo', 'cardsexchange', 'matrix-rotations', 'rotate-mat']),
]
TITLE_RULES = [
 ('dynamic-programming/kadane', ['flipping-game', 'just-eat-it', 'maximumsubarraysum', 'maximum-subarray-sum', 'yarik-and-array']),
 ('dynamic-programming/sequences', ['k-flowers', 'vera-and-lcs', 'lcs']),
 ('dynamic-programming/general', ['hoof-paper-scissors']),
 ('recursion-and-divide-and-conquer', ['recursion-fibonacci']),
 ('two-pointers-and-sliding-window', ['a-a', 'approximating-a-constant-range', 'binary-deque', 'cf-skibidifanumtax', 'atcoder-enougharray']),
 ('prefix-sums', ['move-to-the-end', 'flip-the-bits', 'good-subarrays', 'same-differences', 'cities-and-states', 'd-sum-neq']),
 ('binary-search', ['getting-points', 'leftover-recipes']),
 ('data-structures/stacks-and-queues', ['uva-armybuddies']),
 ('math/combinatorics', ['help-goblins-deceive', 'pythagorean-triples', 'abcd-quadruplets']),
 ('math/number-theory', ['cifera', 'divide-it', 'multiply-by-2', 'hungry-sequence', 'non-square-equation', 'dima-and-lisa']),
 ('geometry', ['draw-a-square', 'isosceles', 'maximum-distance', 'equal-rectangles', 'load-balancing', 'pentagon']),
 ('brute-force-and-backtracking', ['iq-test', 'bear-and-three-musketeers', 'strictly-superior', 'pleasant-pairs', 'lucky-numbers-easy', 'sum-of-cubes', 'd-753', 'bovine-genomics', 'counting-liars', 'cow-gymnastics', 'daisy-chains', 'milk-pails', 'cow-evolution']),
 ('constructive', ['giveaway-problem', 'boys-and-girls', 'little-elephant-and-function', 'or-in-matrix', 'minimise-oneness', 'sequence-game', 'unnatural-conditions', 'dreamoon-and-wifi', 'perfect-square', 'cf-perfecto', 'gray-code', 'c-1-skibidus']),
 ('greedy', ['cinema-line', 'guest-from-the-past', 'chewba', 'kitahara', 'line-breaks', 'line-trip', 'little-elephant-and-bits', 'insert-digit', 'before-an-exam', 'b-crafting', 'fancy-coins', 'merge-it', 'm-arrays', 'minimise-sum', 'pasha-maximizes', 'b-sail', 'vika-and-the-bridge', 'assembly-via-minimums', 'omkar-and-waterslide', 'preparing-for-the-exam', 'c-quests', 'raspberries', 'd-cancel-the-array', 'ania-and-minimizing', 'e-generosity', 'h-two-screens', 'out-of-place', 'sleeping-in-class', 'watching-mooloo', 'even-more-odd-photos', 'air-cownditioning', 'cf-clockwork', 'cf-newmenewarray', 'cf-goodoldtimes', 'increasing-array', 'greedilyincreasing', 'troc-runningforpresident', 'troc-thereisabear', 'validsplit']),
 ('math/arithmetic', ['major-oak', 'adjacent-digit-sums', 'between-a-and-b', 'dima-and-friends', 'distanced-coloring', 'divisibility-problem', 'domino', 'even-odds', 'final-verdict', 'k-divisible-sum', 'keep-the-apples', 'kevin-and-combination', 'mex-table', 'math-problem', 'repdigit', 'santa-claus', 'shape-perimeter', 'shohag-loves-mod', 'soft-drinking', 'soldier-and-bananas', 'sublime-sequence', 'system-of-equations', 'the-number-of-positions', 'to-zero', 'transfusion', 'two-bags-of-potatoes', 'two-frogs', 'vasya-and-the-bus', 'zhan-s-blender', 'b-lasers', 'laura-and-operations', 'increase-and-decrease', 'paint-a-strip', 'sum-of-digits-sequence', 'be-together', 'combination-lock', 'fib-last-digit', 'increase-and-copy', 'max-non-attacking-knights', 'pythagoreanii', 'uninteresting-number', 'cubic-equation', 'divide-by-100', 'the-circle', 'f-digits', 'f-magic-3', 'maximize-sum-of-digits', 'domino-piling', 'round-down', 'floor-number', 'square-counting', 'profitable-interest', 'automatic-answer', 'cf-1-3-5', 'adding-digits', 'cf-again25', 'fizzbuzzremixed', 'kthnondivisible', 'squareyear', 'coin-piles', 'etruscan-warriors', 'helpaphd', 'oddities', 'onechickenperperson', 'only-plusses', 'provinces-and-gold', 'qaly', 'relational-operator', 'searching-for-nessy', 'summing-digits', 'time-travelling-temperatures', 'trailing-zeros', 'uva-knights', 'uva-luckythief', 'watermelon']),
 ('arrays-and-counting', ['elections', 'free-cash', 'guess-the-maximum', 'halloumi-boxes', 'hello-recursion', 'a-lever', 'maximum-of-n-integers', 'milya-and-two-arrays', 'nutrients', 'penchick-and-modern', 'sakurako-s-exam', 'shooshuns-and-sequence', 'submission-bait', 'a-team', 'a-twice', 'zerorush', 'football-kit', 'b-garland', 'b-perfect', 'the-great-dying', 'valerii-against', 'c-lose-it', 'made-up', 'mex-min', 'h-man-of-the-match', 'e-man-of-the-match', 'stamina', 'h-shadow-sum', 'i-remove-it', 'food-for-animals', 'block-game', 'why-did-the-cow-cross', 'cf-a-young-physicist', 'cf-youngphysicist', 'cses-collectingnumbers', 'cses-distinctnumbers', 'distinct-colors', 'emoogle-balance', 'horror-dash', 'kattis-batterup', 'kattis-pet', 'kattis-pokerhand', 'missing-number', 'registration-system', 'statistics', 'trace-of-matrix', 'yellowandredcard', 'repetitions']),
 ('strings', ['abc-ac', 'only-one-digit', 'good-number', 'locked-rooms', 'c-lucky-numbers', 'b-digit-sum', 'cf-skibidus', 'hissingmicrophone', 'kattis-filip', 'uNrEaDaBlE'.lower(), 'subsequence', 'character-recognition', 'hangmanjudge']),
 ('simulation', ['let-s-play-magic', 'circle-of-students', 'crazy-computer', 'sushi-for-two', 'anton-and-currency', 'b-sail', 'b-setsubun', 'soldier-and-cards', 'home-garden', 'b-pacer', 'c-pacer', 'digit-machine', 'arrival-of-the-general', 'mad-scientist', 'usaco-race', 'atcoder-luckydirection', 'beautiful-matrix', 'queue-at-the-school', 'cses-josephus1', 'fizzbuzz', 'jumping-mario', 'kattis-acm', 'kattis-bela', 'kattis-gamerank', 'kattis-hangingout', 'kattis-memorymatch', 'kattis-shuffling', 'magnets', 'tarifa', 'uva-correctmove', 'uva-score', 'uva-tariffplan', 'uva-tennisrounds']),
] + TITLE_RULES
TITLE_RULES = [
 ('dynamic-programming/kadane', ['chaiwalay']),
 ('dynamic-programming/general', ['car-wash', 'softwarehouse', 'abdul-ahad-heights', 'tribonacci-numbers']),
 ('graphs/traversal', ['a-two-friends']),
 ('ternary-search', ['is-this-jee']),
 ('two-pointers-and-sliding-window', ['b-equalize', 'b-deck-of-cards', 'challenging-valley']),
 ('prefix-sums', ['two-squares', 'g-pivot', 'kousuke-assignment', 'hoof-paper-scissors', 'icpcworldfinals']),
 ('data-structures/stacks-and-queues', ['m-notebook', 'chat-order']),
 ('trees', ['heapify-1']),
 ('math/combinatorics', ['peer-review', 'biodiversity-scan', 'all-pairs-segments']),
 ('math/number-theory', ['b-coins', 'divisble-pairs']),
 ('math/arithmetic', ['scary-fee', 'the-play-never-ends', 'core-programmer', 'divergent-series', 'b-drinks', 'a-and-b-and-team-training', 'c-sums', 'grouping-odds', 'sahla-bas', 'interesting-function', 'vasya-and-coins', 't-savings', 'atcoder-ratinggoal', 'back-to-school', 'cf-iambored', 'firework-festival', 'judging-moose', 'averageshard', 'q8', 'tlx-tilinggame', 'troc-lithairstyle']),
 ('arrays-and-counting', ['the-rizzler', 'voting-for-photos', 'big-segment', 'fatima-s-collection', 'd-mix-plate', 'play-snuke', 'score-high', 'lurak-gya', 'amalgamated-artichokes', 'arrays', 'at-removeminedges', 'bookingaroom', 'sereja-and-bottles', 'cf-a-winner', 'cta', 'open-credit-system', 'fastfoodprizes', 'jollyjumpers', 'lostlineup', 'kattis-vote', 'licensetolaunch', 'google-is-feeling-lucky', 'spoj-intest']),
 ('brute-force-and-backtracking', ['economy-game', 'new-year-s-number', 'f-3-sum', 'i-how-many', 'trilobyte', 'bubbletea', 'uva-eventplanning']),
 ('constructive', ['vera-and-lcs', 'harder-problem', 'everyone-loves-tres', 'almost-ternary-matrix']),
 ('greedy', ['regular-bracket-sequence', 'expensive-number', 'coin-collector', 'pawn-line', 'job-fair', 'b-equalize', 'at-resale', 'baloni', 'ezzat', 'flipping-the-matrix', 'bitsequalizer']),
 ('geometry', ['fence-painting', 'd-thefool']),
 ('strings', ['b-0-f', 'f-no', 'alternating', 'ashar']),
 ('sorting-and-searching', ['whatisthemedian']),
 ('simulation', ['chris-and-magic-square', 'vasya-and-wrestling', 'bridge-renovation', 'dice-roll-sequence', 'lock-all-doors', 'outofmemoryerror', 'a-new-technique', 'mirror-grid', 'library-fine', 'into-blocks', 'flip-the-matrix', 'ilove1543', 'isithalloween', 'bossbattle', 'kattis-digits', 'eligibility', 'emagehthtiwempleh', 'imageprocessing', 'left-beehind', 'mia', 'packingforholiday', 'lasersculpture']),
 ('recursion-and-divide-and-conquer', ['atcoder-christmas']),
] + TITLE_RULES
# Match literal title fragments rather than loose regex against source text.
TITLE_RULES = [(c, [p for p in pats if '(' not in p]) for c,pats in TITLE_RULES]

def normalized(text):
    return re.sub(r'[^a-z0-9]+', '-', text.lower()).strip('-')

def body(text, suffix):
    if suffix == '.py':
        try:
            nodes = ast.parse(text).body
            lines = text.splitlines()
            excluded = {'FastIO', 'IOWrapper', 'print'}
            for node in reversed(nodes):
                if isinstance(node, (ast.ClassDef, ast.FunctionDef)) and node.name in excluded:
                    del lines[node.lineno - 1:node.end_lineno]
            text = '\n'.join(lines)
        except SyntaxError:
            pass
        return re.sub(r'(?m)#.*$', '', text)
    # Remove comments first, keeping string literals (including paths) intact.
    text = re.sub(r'("(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')|/\*.*?\*/|//[^\n]*', lambda m: m[1] or '', text, flags=re.S)
    lines = [line for line in text.splitlines() if not line.lstrip().startswith(('#', 'typedef ', 'using '))]
    text = '\n'.join(lines)
    # Omit standard helper function definitions from the shared submission template.
    helper = re.compile(r'(?m)^[^\n{};]*\b(?:max|min|gcd|lcm|prime|modexp|binpow|to_upper|to_lower|yes|no|print|prints|print_v|printInt128|Case|fastio|debug_out)\s*\([^\n;]*?\)\s*\{')
    while True:
        m = helper.search(text)
        if not m:
            break
        depth, i = 1, m.end()
        while depth and i < len(text):
            depth += (text[i] == '{') - (text[i] == '}')
            i += 1
        text = text[:m.start()] + text[i:]
    return text

def classify(filename, text):
    code = body(text, Path(filename).suffix)
    title = normalized(Path(filename).stem)
    candidates = []
    for cat, patterns in TITLE_RULES:
        for pattern in patterns:
            if pattern in {'tree', 'a-a', 'lcs', 'coins'} and title != pattern:
                continue
            if pattern in title:
                candidates.append((cat, 'title pattern: ' + pattern, 'medium'))
                break
    signals = [
        ('dynamic-programming/general', r'\b(?:dp\w*|memo\w*)\s*\[', 'DP or memo table accessed'),
        ('data-structures/range-queries', r'\b(?:SegTree|SegmentTree|segtree|segment_tree|Fenwick|fenwick|BIT)\b', 'range query structure'),
        ('data-structures/disjoint-set', r'\b(?:findp|find_set|unite|RollbackUF|DSU|dsu)\s*[<(]', 'disjoint set operations'),
        ('graphs/traversal', r'\b(?:dfs|bfs|floodfill|flood_fill)\s*\(', 'graph or grid traversal'),
        ('graphs/shortest-paths', r'\b(?:dijkstra|bellman_ford|floyd_warshall)\b', 'shortest path algorithm'),
        ('binary-search', r'\b(?:lower_bound|upper_bound|bisect_left|bisect_right)\s*\(|\bmid\s*=\s*\(?\s*(?:l|lo|low|left)\b[^;\n]*(?:r|hi|high|right)', 'binary search or sorted bound query'),
        ('ternary-search', r'\bmid1\b[\s\S]*\bmid2\b', 'two ternary search probes'),
        ('prefix-sums', r'\b(?:pref|prefix|psum|prefixSum|prefix_sum|prefixsum|preSum)\s*\[', 'prefix aggregates'),
        ('bit-manipulation', r'\^=|\b__builtin_(?:popcount|clz|ctz)|\b1(?:LL|ll)?\s*<<\s*(?!endl\b|[\"\x27])[\w(]|\s\^\s', 'bitwise operations in implementation'),
        ('data-structures/heaps', r'\bpriority_queue\s*<|\bheapq\.', 'heap operations'),
        ('data-structures/stacks-and-queues', r'\bstack\s*<|\.pop_front\(|\.popleft\(', 'stack or deque operations'),
        ('data-structures/ordered-sets', r'\b(?:ordered_set|multiset)\s*[<(]|\.order_of_key\(|\.find_by_order\(', 'ordered set operations'),
        ('math/number-theory', r'\b(?:gcd|lcm|__gcd|modexp|binpow|isprime|isPrime|sieve)\s*\(|\bspf\s*\[', 'number theory operations'),
        ('math/combinatorics', r'\b(?:fact|invfact|factorial|invFact|nCr)\s*[\[(]', 'factorial or binomial counting'),
        ('sorting-and-searching', r'\b(?:sort|sorted)\s*\(|\.sort\(', 'explicit sorting'),
        ('strings', r'\b(?:tolower|toupper|getline|isalpha|isdigit|substr)\s*\(|\.substr\(|\bre\.(?:finditer|search|match)', 'character processing or parsing'),
    ]
    hits = [(cat, 'source: ' + evidence, 'medium') for cat, pattern, evidence in signals if re.search(pattern, code)]
    # Title rules select the more specific family; source signals provide secondary tags.
    if candidates:
        primary, reason, confidence = candidates[0]
        # The title "Coins" can also refer to an elementary arithmetic problem.
        if primary.startswith('dynamic-programming') and not any(c.startswith('dynamic-programming') for c,_,_ in hits):
            if primary in {'dynamic-programming/general', 'dynamic-programming/sequences'}:
                candidates = candidates[1:]
                primary, reason, confidence = candidates[0] if candidates else (hits[0] if hits else ('needs-review', 'Title suggests DP but no DP evidence found', 'low'))
    elif hits:
        primary, reason, confidence = hits[0]
    else:
        primary, reason, confidence = 'needs-review', 'No sufficiently specific title or implementation signal', 'low'
    tags = sorted({c for c,_,_ in candidates + hits} - {'needs-review'})
    if primary not in tags and primary != 'needs-review':
        tags.append(primary)
    return dict(category=primary, tags=tags, classification_confidence=confidence,
                classification_evidence=reason,
                classification_status='suggested' if primary != 'needs-review' else 'needs-review')


# Individual implementations read during the migration; these supersede title guesses.
REVIEWED = {
    'A_Guess_a_number.cpp': ('intervals', 'Intersect integer bounds for each inequality'),
    'LCS.cpp': ('dynamic-programming/sequences', '2D LCS recurrence and reconstruction'),
    'C_Make_Them_Equal.cpp': ('greedy', 'Find a valid operation index or use two final indices'),
    'chinese_remainder_theorem.cpp': ('math/number-theory', 'Computes a*b/gcd(a,b), not CRT'),
    'kmp.py': ('strings', 'Regular expression matching; KMP implementation is commented out'),
    'B_B.cpp': ('brute-force-and-backtracking', 'Enumerates all nonempty masks'),
    'B_Fibonaccharsis.cpp': ('brute-force-and-backtracking', 'Enumerates previous Fibonacci sequence terms'),
    'B_Variety_is_Discouraged.cpp': ('two-pointers-and-sliding-window', 'Finds longest run of globally unique elements'),
    'C_Dora_and_Search.cpp': ('two-pointers-and-sliding-window', 'Removes endpoints while maintaining an ordered set'),
    'D_A_Linear_Problem.cpp': ('geometry', 'Normalizes direction vectors using gcd'),
    'D_Good_Sets.cpp': ('two-pointers-and-sliding-window', 'Monotonic deques bound the window range'),
    'building_reconstruction.cpp': ('ternary-search', 'Searches a weighted absolute-distance cost with two probes'),
    'A_Walking_on_the_Safe_Side.cpp': ('dynamic-programming/general', 'Grid path count recurrence'),
    'B_Flight_Planner.cpp': ('dynamic-programming/general', 'Altitude by segment minimum fuel DP'),
    'B_Max_Spanning_Tree.cpp': ('graphs/spanning-trees', 'Descending Kruskal with union find'),
    'sp/longest_subarray_with_sum_k.cpp': ('prefix-sums', 'Maps prefix sums to their first occurrence'),
    'sp/subarray_sum_equals_k.cpp': ('prefix-sums', 'Counts previous prefix sums'),
    'B_Chaiwalay.cpp': ('dynamic-programming/kadane', 'Kadane recurrence on profit minus cost'),
    'hoof_paper_scissors.cpp': ('prefix-sums', 'Prefix move counts and enumeration of switch point'),
    'M_Notebook.cpp': ('data-structures/stacks-and-queues', 'Persistent stack represented by parent indices'),
    'O_Chat_Order.cpp': ('data-structures/stacks-and-queues', 'Move-to-front linked list with iterator map'),
    'O_Is_This_JEE.cpp': ('ternary-search', 'Two probes on a continuous objective'),
    'D_Divisble_Pairs.cpp': ('math/number-theory', 'Counts matching pairs of modular residues'),
    'number_spiral.cpp': ('math/arithmetic', 'Parity-based coordinate formula'),
    'kattis-pascal.cpp': ('math/number-theory', 'Finds the smallest factor'),
    'model-solutions/traffic-lights.cpp': ('math/arithmetic', 'Adds twice the ceiling of cars divided by lanes'),
    'q6.cpp': ('graphs/shortest-paths', 'Queue traversal over node and route states'),
    'q6.py': ('graphs/shortest-paths', 'Queue traversal over node and route states'),
}
REVIEWED.update({
    'B_Amr_and_The_Large_Array.cpp': ('arrays-and-counting', 'Counts frequency and tracks first/last positions'),
    'B_An_Operational_Problem.cpp': ('math/number-theory', 'Counts factors of two and frequency parity'),
    'C_Gormint_Skool.cpp': ('constructive', 'Places numbers to realize a requested inversion count'),
    'C_Grandma_Capa_Knits_A_Scarf.cpp': ('two-pointers-and-sliding-window', 'Scans inward for each allowed deletion character'),
    'C_Penchick_and_BBQ_Buns.cpp': ('constructive', 'Prints equal adjacent pairs'),
    'D_Find_the_Different_Ones.cpp': ('prefix-sums', 'Precomputes previous position with a different value'),
    'D_Unbalanced.cpp': ('two-pointers-and-sliding-window', 'Checks a moving three-character window'),
    'E_Magikarp_Far_From_Home.cpp': ('graphs/shortest-paths', 'Dijkstra on reversed edges with an ordered frontier'),
    'F_El_mask_mesh_hena.cpp': ('bit-manipulation', 'Bitwise AND of all array values'),
    'G_G.cpp': ('math/arithmetic', 'Compares unit and bundle prices'),
    'at-whoisstrongest.cpp': ('graphs/topological-sort', 'Finds the unique zero-indegree vertex'),
    'atcoder-seekgrid.cpp': ('brute-force-and-backtracking', 'Tries all placements of a smaller grid'),
    'cf-evenarray.cpp': ('arrays-and-counting', 'Counts parity mismatches'),
    'eww.py': ('arrays-and-counting', 'Intersects input sets'),
    'oddgnome.cpp': ('arrays-and-counting', 'Scans consecutive differences'),
    'puzzling-puzzle.cpp': ('constructive', 'Prints the pair one and n'),
    'quadrantselection.cpp': ('geometry', 'Classifies coordinates by their signs'),
    'uva-cabin-baggage.cpp': ('simulation', 'Checks dimensions and weight limits'),
    'uva-poleposition.cpp': ('simulation', 'Places cars using relative offsets'),
})
_suggest = classify

def classify(filename, text):
    result = _suggest(filename, text)
    if filename in REVIEWED:
        category, evidence = REVIEWED[filename]
        result.update(category=category, classification_confidence='high',
                      classification_evidence=evidence, classification_status='reviewed')
        result['tags'] = sorted(set(result['tags']) | {category})
        # A curated correction must not keep the rejected primary category as a tag.
        if filename in {'C_Make_Them_Equal.cpp', 'number_spiral.cpp', 'kattis-pascal.cpp'}:
            result['tags'] = [category]
    return result

# Additional implementation reviews during catalog completion.
CATEGORIES["meet-in-the-middle"] = "Enumerate two halves and combine their results"
REVIEWED.update({'B_Fence.cpp': ('prefix-sums', 'Prefix sums stored in a variable named dp; queries fixed-length windows'), 'B_Subtractonacci.cpp': ('math/arithmetic', 'Uses a closed six-term periodic sequence'), 'C_Bipartize.cpp': ('brute-force-and-backtracking', 'Enumerates all vertex color masks and counts monochromatic edges'), 'C_Chokutter_Addiction.cpp': ('simulation', 'Simulates active time intervals with a 100-unit cooldown'), 'C_Mixtures.cpp': ('brute-force-and-backtracking', 'Enumerates subarrays and products; no interval DP in this implementation'), 'DMOJ_24.py': ('brute-force-and-backtracking', 'Backtracks over arithmetic combinations of four numbers'), 'D_Decorating_Christmas_Tree.cpp': ('greedy', 'Allocates resource bundles using min operations'), 'D_Destruction_of_the_Dandelion_Fields.cpp': ('greedy', 'Splits odd/even values and greedily chooses sorted odd contributions'), 'D_Swap_and_Range_Sum.cpp': ('prefix-sums', 'Maintains prefix sums with a single changed boundary per adjacent swap'), 'E_Sparse_Range.cpp': ('two-pointers-and-sliding-window', 'Moves a left boundary while querying a multiset for nearby values'), 'G_Matching.cpp': ('greedy', 'Groups by value minus index, sorts, and pairs profitable elements'), 'G_Match_Matching.cpp': ('dynamic-programming/knapsack', 'Unbounded matchstick budget DP followed by digit reconstruction'), 'K_Subset_Sums.cpp': ('meet-in-the-middle', 'Enumerates sums of two halves and combines them with sorted bounds'), 'cf-vladsumofdigits.cpp': ('prefix-sums', 'Prefix sum of digit sums stored in a variable named dp'), 'cses-twosets.cpp': ('dynamic-programming/knapsack', 'Subset sum count DP with a modular inverse for symmetric partitions'), 'fours-and-fives.cpp': ('dynamic-programming/knapsack', 'Coin change counting DP with denominations four and five'), 'cses-lis.cpp': ('dynamic-programming/sequences', 'Maintains LIS tails with lower_bound'), 'maximum_subarray_sum_ii.py': ('two-pointers-and-sliding-window', 'Maintains a monotonic deque of prefix minima within length bounds')})
