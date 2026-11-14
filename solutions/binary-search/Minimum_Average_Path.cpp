#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
using ld = long double;

const ld INF = 1e30;
void solve() {
    int n, m; cin >> n >> m;

    struct Edge {
        int u, v, w;
    };

    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    int mx = 0;
    for (auto &[u, v, w] : edges) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        indeg[v]++;
        mx = max(mx, w);
    }

    // Topological sorting
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (indeg[i] == 0)
            q.push(i);

    vector<int> topo;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topo.push_back(u);

        for (auto [v, w] : adj[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }

    auto traverse = [&](ld x, vector<ld> &dp, vector<int> &parent) {
        dp[1] = 0;

        for (int u : topo) {
            if (dp[u] == INF) continue;

            for (auto [v, w] : adj[u]) {
                if (dp[u] + w - x < dp[v]) {
                    dp[v] = dp[u] + w - x;
                    parent[v] = u;
                }
            }
        }
    };

    auto can = [&](ld x) {
        vector<ld> dp(n + 1, INF);
        vector<int> parent(n + 1, -1);
        traverse(x, dp, parent);
        return dp[n] <= 0;
    };

    // Binary search
    ld l = 0, r = mx;

    for (int i = 0; i < 100; ++i) {
        ld mid = (l + r) / 2;

        if (can(mid))
            r = mid;
        else
            l = mid;
    }

    vector<ld> dp(n + 1, INF);
    vector<int> parent(n + 1, -1);
    traverse(r, dp, parent);

    vector<int> path;
    int curr = n;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());

    cout << path.size() -1 << endl;
    for (auto &x: path) cout << x << " ";
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
