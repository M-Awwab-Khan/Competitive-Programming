#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
struct RollbackDSU {
    vector<int> parent, sz;
    stack<pair<int, int>> history;
    // stack<int> checkpoints;
    int components;

    RollbackDSU(int n) {
        init(n);
    }

    void init(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        iota(parent.begin(), parent.end(), 0);

        components = n;

        while(!history.empty()) history.pop();
        // while(!checkpoints.empty()) checkpoints.pop();

    }

    int find(int x) {
        if (parent[x] == x) return x;
        return find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;

        if (sz[x] < sz[y]) swap(x, y);

        history.push({y, sz[x]});
        parent[y] = x;
        sz[x] += sz[y];

        components--;
    }

    void undo() {

        auto [y, _size] = history.top();
        history.pop();

        int x = parent[y];
        parent[y] = y;
        sz[x] = _size;
        components++;
    }

    // void persist() {
    //     checkpoints.push(history.size());
    // }

    void rollbackTo(int target) {
        // int target = checkpoints.top();
        // checkpoints.pop();

        while (history.size() > target) {
            undo();
        }
    }
};


using Edge = pair<int, int>;

struct Query {
    char type = '?';
};

int n, m;
vector<Query> q;
vector<vector<Edge>> seg;
RollbackDSU dsu(0);

Edge makeEdge(int u, int v) {
    if (u > v) swap(u, v);
    return {u, v};
}

void add(int node, int l, int r, int ql, int qr, Edge e) {
    if (ql > r || qr < l) return;

    if (ql <= l && r <= qr) {
        seg[node].push_back(e); return;
    }

    int mid = (l + r) /2;

    add(node*2, l, mid, ql, qr, e);
    add(node*2 + 1, mid+1, r, ql, qr, e);
}

void dfs(int node, int l, int r) {
    int snapshot = dsu.history.size();

    for (auto [u, v]: seg[node]) {
        dsu.unite(u, v);
    }

    if (l == r) {
        if (q[l].type == '?') cout << dsu.components << '\n';
    }

    else {
        int mid = (l + r) /2;

        dfs(node*2, l ,mid);
        dfs(node*2 + 1, mid + 1, r);
    }

    dsu.rollbackTo(snapshot);
}

void solve() {
    cin >> n >> m;
    q.assign(m + 1, {});
    seg.assign(4 * m + 4, {});
    dsu.init(n);

    map<Edge, int> start;

    for (int i = 1; i <= m; ++i) {
        cin >> q[i].type;
        if (q[i].type == '+') {
            int u, v;
            cin >> u >> v;
            start[makeEdge(u, v)] = i;
        } else if (q[i].type == '-') {
            int u, v;
            cin >> u >> v;
            Edge e = makeEdge(u, v);
            int l = start[e];
            add(1, 1, m, l, i - 1, e);
            start.erase(start.find(e));
        }
    }

    for (const auto& [edge, l] : start) {
        add(1, 1, m, l, m, edge);
    }

    if (m > 0) dfs(1, 1, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
