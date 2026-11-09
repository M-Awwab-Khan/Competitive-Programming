#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct DSU {
    vector<int> parent, sz, xr;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        xr.assign(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v)
            return v;

        int p = parent[v];
        parent[v] = find(p);
        xr[v] ^= xr[p];

        return parent[v];
    }

    // Returns false if this edge breaks bipartiteness
    bool addEdge(int u, int v) {
        int ru = find(u);
        int rv = find(v);

        // Already in the same component
        if (ru == rv) {
            return (xr[u] ^ xr[v]) == 1;
        }

        // Merge components
        if (sz[ru] < sz[rv])
            swap(ru, rv);

        xr[rv] = xr[u] ^ xr[v] ^ 1;

        parent[rv] = ru;
        sz[ru] += sz[rv];

        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        if (!dsu.addEdge(u, v)) {
            cout << i << '\n';
            return;
        }
    }

    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
