// Generated from notes/contest-prep/div3-speed-programming.md.
// Regenerate: python3 scripts/build_sp_reference.py
// GNU C++17. Read the guide for preconditions; no global using-directive.
#pragma once
#include <bits/stdc++.h>

namespace sp {
using namespace std;
using ll = long long;
using i128 = __int128_t;

// integer-helpers
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

// mex
inline int mex(const vector<ll>& a) {
    vector<char> seen(a.size() + 1, false);
    for (ll x : a) if (0 <= x && x <= (ll)a.size()) seen[(size_t)x] = true;
    int answer = 0;
    while (answer < (int)seen.size() && seen[answer]) ++answer;
    return answer;
}

// count-subarrays
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

// pair-count
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

// distinct-window
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

// window-maximum
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

// binary-search
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

// prefix-function
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

// factorization
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

// modular-power
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

// combinations
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

// geometry
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

// bfs
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

// dijkstra
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

// lis
inline int lis_length(const vector<ll>& a) {
    vector<ll> tails;
    for (ll value : a) {
        auto it = lower_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return (int)tails.size();
}

// knapsack
inline ll knapsack01(const vector<int>& weight, const vector<ll>& value, int capacity) {
    // REQUIRE equal vector sizes, positive weights, and capacity >= 0.
    // dp[c] means best value using total weight AT MOST c; choosing nothing is allowed.
    vector<ll> dp(capacity + 1, 0);
    for (int i = 0; i < (int)weight.size(); ++i)
        for (int c = capacity; c >= weight[i]; --c)
            dp[c] = max(dp[c], dp[c - weight[i]] + value[i]);
    return dp[capacity];
}

// dsu
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

// fenwick
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

// segment-tree
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

} // namespace sp
