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
        parent.resize(n + 1); sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }


    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if ( x == y ) return;

        if (sz[x] < sz[y]) swap(x, y);

        parent[y] = x;
        sz[x] += sz[y];
    }
};


void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
    }

    sort(edges.begin(), edges.end());

    ll ans = LLONG_MAX;

    for (int l = 0; l < m; ++l) {
        ll cost = 0;
        int x = 0;
        int mn = INT_MAX;
        int mx = INT_MIN;
        DSU dsu(n);
        for (int i = l; i < m;++i) {
            auto edge = edges[i];
            if (dsu.find(edge[1]) != dsu.find(edge[2])) {
                mn = min(mn, i);
                mx = max(mx, i);
                x++;
                dsu.unite(edge[1], edge[2]);
                cost += edge[0];
                if (x == n - 1) {
                    ans = min(ans, 1LL*abs(edges[mn][0] - edges[mx][0]));
                    break;
                }
            }
        }

    }

    cout << (ans != LLONG_MAX ? "YES\n" + to_string(ans): "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
