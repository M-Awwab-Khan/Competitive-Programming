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

    int ans = INT_MIN;

    int x = 0;
    DSU dsu(n);
    for (auto edge: edges) {
        if (dsu.find(edge[1]) != dsu.find(edge[2])) {
            x++;
            dsu.unite(edge[1], edge[2]);
            ans = max(ans, edge[0]);
            if (x == n-1) break;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
