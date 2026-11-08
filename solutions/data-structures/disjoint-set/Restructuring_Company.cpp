#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;



struct DSU {
    vector<int> parent, sz, nxt;

    DSU(int n) {
        parent.resize(n + 1);
        nxt.resize(n + 1);
        sz.assign(n + 1, 1);

        iota(parent.begin(), parent.end(), 0);
        iota(nxt.begin(), nxt.end(), 0);
    }

    int find(int v) {
        if (v == parent[v])
            return v;

        return parent[v] = find(parent[v]);
    }

    int findNext(int v) {
        if (v == nxt[v])
            return v;

        return nxt[v] = findNext(nxt[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        // Small to large
        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
    }

    void uniteRange(int l, int r) {
        int i = findNext(l);

        while (i < r) {
            unite(i, i + 1);

            nxt[i] = findNext(i + 1);
            i = nxt[i];
        }
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int v) {
        return sz[find(v)];
    }
};

void solve() {
    int n, q; cin >> n >> q;
    DSU dsu(n);

    while (q--) {
        int type, x, y; cin >> type >> x >> y;

        if (type == 1) dsu.unite(x, y);
        else if (type == 2) dsu.uniteRange(x, y);
        else {
            cout << (dsu.same(x, y) ? "YES": "NO") << endl;
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
