#include "bits/stdc++.h"
using namespace std;

using ll = long long;


void solve() {

    int n; cin >> n;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    map<int, set<int>> adj;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (x[i] == x[j] || y[i] == y[j]) {
                adj[i].insert(j);
                adj[j].insert(i);
            }
        }
    }

    vector<bool> visited(n, false);
    function <void(int)> dfs = [&](int u) {
        visited[u] = true;

        for (auto v: adj[u]) {
            if (!visited[v]) dfs(v);
        }
    };

    int cc = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            ++cc;
            dfs(i);
        }
    }
    cout << cc - 1<< endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
