#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

struct Edge {
    int u, v, w;
};

void solve() {
    int n, m, d; cin >> n >> m >>d;
    map<int, vector<Edge>> adj;

    int u, v, w;
    for(int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        adj[u].push_back({u, v, w});
    }

    auto bfs = [&](int x, vector<int> &dist, vector<int> &parent) {
        dist[1] = 0;

        queue<int> q;
        q.push(1);

        while(!q.empty()) {
            int i = q.front(); q.pop();

            for(Edge e: adj[i]){
                if (e.w <= x && dist[e.v] == -1) {
                    q.push(e.v);
                    parent[e.v] = e.u;
                    dist[e.v] = dist[e.u] + 1;
                }
            }
        }
    };

    auto can = [&](int x) {
        vector<int> dist(n + 1, -1);
        vector<int> parent(n + 1, -1);
        bfs(x, dist, parent);
        return (dist[n] == -1) ? false : (dist[n] <= d);
    };

    int lo = 0, hi = 1e9;
    int ans = -1;
    while(lo <= hi) {
        int mid = lo + (hi - lo) /2;
        if (can(mid)) {
            ans = mid;
            hi = mid - 1;
        } else lo = mid + 1;
    }

    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, -1);
    bfs(ans, dist, parent);

    if (dist[n] == -1) {
        cout << -1 << endl;
    } else {
        cout << dist[n] << endl;
        int curr = n;
        vector<int> path;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (auto &y: path) cout << y << " ";
        cout << endl;
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
