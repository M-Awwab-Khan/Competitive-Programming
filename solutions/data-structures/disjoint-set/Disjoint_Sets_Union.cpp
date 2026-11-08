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
        parent.resize(n + 1); sz.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
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

    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return sz[find(x)];}
};

void solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        string type; cin >> type;
        int x, y; cin >> x >> y;

        if (type == "union") dsu.unite(x, y);
        else {
            cout << ((dsu.same(x, y)) ? "YES": "NO") << endl;
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
