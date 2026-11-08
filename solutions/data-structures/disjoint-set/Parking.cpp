#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct DSU {
    int _n;
    vector<int> parent, sz, mx;

    DSU(int n) {
        _n = n;
        parent.resize(n + 1); iota(parent.begin(), parent.end(), 0);
        mx.resize(n + 1); iota(mx.begin(), mx.end(), 0);
        sz.assign(n + 1, 1);
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
    int n; cin >> n;
    DSU dsu(2*n);

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int spot = dsu.find(x);
        if (spot == n + 1) spot = dsu.find(1);

        cout << spot << " ";
        dsu.parent[spot] = dsu.find(spot + 1);
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
