#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct DSU {
    vector<int> parent, sz, mn, mx;

    DSU(int n) {
        parent.resize(n + 1); sz.assign(n + 1, 1);
        mn.resize(n + 1); mx.resize(n + 1);

        iota(parent.begin(), parent.end(), 0);
        iota(mn.begin(), mn.end(), 0);
        iota(mx.begin(), mx.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    int min(int x) {return mn[find(x)];}
    int max(int x) {return mx[find(x)];}

    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);

        parent[y] = x;
        mn[x] = std::min(mn[x], mn[y]);
        mx[x] = std::max(mx[x], mx[y]);
        sz[x] += sz[y];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return sz[find(x)];
    }
};

void solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n);

    while (m--) {
        string type; cin >> type;
        if (type == "union") {
            int x, y; cin >> x >> y;
            dsu.unite(x, y);
        }
        else {
            int x; cin >> x;
            cout << dsu.min(x) << " " << dsu.max(x) << " " << dsu.size(x) << endl;
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
