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
    stack<pair<int, int>> history;
    stack<int> checkpoints;

    int components;

    DSU (int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);

        components = n;
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
        sz[x] += y;

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

    void persist() {
        checkpoints.push(history.size());
    }

    void rollback() {
        int target = checkpoints.top();
        checkpoints.pop();

        while (history.size() > target) {
            undo();
        }
    }
};

void solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n);

    while (m--) {
        string type; cin >> type;
        if (type == "persist") dsu.persist();
        else if (type == "union") {
            int x, y; cin >>x >> y;
            dsu.unite(x, y);
            cout << dsu.components << endl;
        } else {
            dsu.rollback();
            cout << dsu.components << endl;
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
