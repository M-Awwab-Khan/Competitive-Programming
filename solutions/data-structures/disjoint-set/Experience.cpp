#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

#define int long long



struct DSU {
    vector<int> parent, sz, lazy, diff;

    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);

        sz.assign(n + 1, 1);
        lazy.assign(n + 1, 0);
        diff.assign(n + 1, 0);
    }

    int find(int x) {
        if (x == parent[x]) return x;

        int p = parent[x];
        parent[x] = find(parent[x]);
        diff[x] += diff[p];

        return parent[x];
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;

        if (sz[x] < sz[y]) swap(x, y);

        parent[y] = x;
        sz[x] += sz[y];

        diff[y] = lazy[y] - lazy[x];
    }

    void add(int x, int v) {
        x = find(x);
        lazy[x] += v;
    }

    int exp_(int x) {
        int root = find(x);
        return lazy[root] + diff[x];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return sz[find(x)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    while (m--) {
        string type;
        cin >> type;

        int x, y;

        if (type == "join") {
            cin >> x >> y;
            dsu.unite(x, y);
        }
        else if (type == "add") {
            cin >> x >> y;
            dsu.add(x, y);
        }
        else {
            cin >> x;
            cout << dsu.exp_(x) << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
