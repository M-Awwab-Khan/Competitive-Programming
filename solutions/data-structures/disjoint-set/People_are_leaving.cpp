#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct DSU {
    vector<int> parent, sz, mx;
    int nn;

    DSU(int n) {
        nn = n;
        parent.resize(n + 1); sz.assign(n + 1, 1); mx.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        iota(mx.begin(), mx.end(), 0);
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
        mx[x] = max(mx[x], mx[y]);
    }

    int _mx(int x) {
        return mx[find(x)];
    }
};

void solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n + 1);

    while (m--) {
        char type; int p; cin >> type >> p;

        if (type == '-') {
            dsu.unite(p, p + 1);
        } else {
            int x = dsu._mx(p);
            cout << (x > n ? -1 : x) << endl;
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
