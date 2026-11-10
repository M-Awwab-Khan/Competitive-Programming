#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define endl "\n"

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

struct Query {
    int l, r, id;
};

void solve() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> edges(m + 1);
    for (int i = 1; i <= m; ++i) cin >> edges[i].first >> edges[i].second;

    int q; cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i + 1;
    }

    int B = sqrt(m) + 1;

    // pay attention to how we sorted;
    sort(queries.begin(), queries.end(), [&](Query a, Query b) {
        int blockA = (a.l - 1) / B;
        int blockB = (b.l - 1) / B;

        if (blockA != blockB)
            return blockA < blockB;

        return a.r < b.r;
    });

    RollbackDSU dsu(n);
    vector<int> ans(q + 1);

    int i = 0;
    while (i < q) {

        int block = (queries[i].l - 1) / B; // find the block of this query (using l)
        int R = min(m, (block + 1) * B);  // find the right end point of the block or end of edges reached.

        // process all queries of this block
        int j = i;
        while (j < q && (queries[j].l - 1) / B == block) ++j;

        // process queries completely inside the block.
        // these need a fresh DSU for each query.
        for (int k = i; k < j; k++) {
            if (queries[k].r > R) break;

            dsu.init(n);

            for (int e = queries[k].l; e <= queries[k].r; ++e) dsu.unite(edges[e].first, edges[e].second);

            ans[queries[k].id] = dsu.components;
        }

        dsu.init(n);
        int curR = R;

        for (int k = i; k < j; ++k) {
            int l = queries[k].l;
            int r = queries[k].r;

            if (r <= R) continue;
            while (curR < r) {
                curR++;

                dsu.unite(edges[curR].first, edges[curR].second);
            }

            int snapshot = dsu.history.size();

            for (int e = R; e >= l; --e) {
                dsu.unite(edges[e].first, edges[e].second);
            }

            ans[queries[k].id] = dsu.components;

            dsu.rollbackTo(snapshot);
        }

        i = j;

    }

    for (int i = 1; i <= q; ++i) cout << ans[i] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
