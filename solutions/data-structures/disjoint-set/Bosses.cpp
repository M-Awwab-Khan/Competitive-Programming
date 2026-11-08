#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct DSU {
    vector<int> parent, sz, dist;

    DSU(int n) {
        parent.resize(n + 1);
        dist.assign(n + 1, 0);
        sz.assign(n + 1, 1);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (v == parent[v])
            return v;

        int p = parent[v];
        parent[v] = find(p);
        dist[v] += dist[p];

        return parent[v];
    }


    void unite(int a, int b) {
        parent[a] = b;
        dist[a] = 1;
        sz[b] += sz[a];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int v) {
        return sz[find(v)];
    }

    int getDepth(int v) {
        find(v);
        return dist[v];
    }
};

void solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        int type; cin >> type;
        if (type == 1) {
            int a, b; cin >> a >> b;
            dsu.unite(a, b);
        } else {
            int c; cin >> c;
            cout << dsu.getDepth(c) << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
