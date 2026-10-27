#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<vector<int>> edges(m, vector<int>(3, 0));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    if (k == 0) {cout << -1 << endl;}
    else {
        set<int> st;
        for (int i = 0; i < k; ++i) {
            int x; cin >> x;
            st.insert(x);
        }
        // for (int x: st) cout << x << "\n";

        int ans = INT_MAX;
        for (int i = 0; i < m; ++i) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            // cout << u << v << w << endl;
            if ((st.count(u) > 0 && st.count(v) == 0) || (st.count(v) > 0 && st.count(u) == 0)) {
                ans = min(ans, w);
            }
        }
        cout << ((ans == INT_MAX) ? -1 : ans) << endl;
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
