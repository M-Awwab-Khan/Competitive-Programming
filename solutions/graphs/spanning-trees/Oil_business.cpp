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

struct Node {
    int id;
    int u, v;
    ll w;
};

#ifdef CP_DEBUG
DEBUG_STRUCT(Node, id, u, v, w)
#endif

void solve() {
    int n, m; cin >> n >> m;
    ll s; cin >> s;

    vector<Node> edges(m);
    for (int i  = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i + 1;
    }

    sort(edges.begin(), edges.end(), [](const Node &a, const Node &b) {
        return a.w > b.w;
    });

    // debug(edges);
    // make Maximum spanning tree
    DSU dsu(n);
    set<int> taken;
    int x = 0;
    for (auto edge: edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            ++x;
            dsu.unite(edge.u, edge.v);
            taken.insert(edge.id);
            if (x == n -1) break;
        }
    }


    set<int> deleted;
    ll w = 0;
    for (int i = m-1; i >= 0; --i) {
        if (taken.count(edges[i].id)) continue;
        if (w + edges[i].w <= s) {
            w += edges[i].w;
            deleted.insert(edges[i].id);
        } else break;
    }

    cout << deleted.size() << endl;
    for (auto x: deleted) cout << x << " ";
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
