#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;

        if (sz[x] < sz[y]) swap(x, y);

        parent[y] = x;
        sz[x] += sz[y];
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<pair<int, int>> edges;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        edges.push_back({u, v});
    }

    vector<tuple<string, int, int>> queries;
    for (int i = 0; i < k ;++i) {
        string type; cin >>type >> u >> v;
        queries.emplace_back(type, u, v);
    }
    debug(queries);

    vector<string> ans;
    DSU dsu(n);
    for (int i = k-1; i >= 0; --i) {
        tuple<string, int, int> query = queries[i];
        if (get<0>(query) == "ask") {
            ans.push_back((dsu.find(get<1>(query)) ==  dsu.find(get<2>(query))) ? "YES" : "NO");
        } else {
            dsu.unite(get<1>(query), get<2>(query));
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto s: ans) cout << s << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
