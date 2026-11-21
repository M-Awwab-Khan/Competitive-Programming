#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int ll

void solve() {
    int n, m; cin >> n >> m;
    vector<int> b(n);
    vector<int> g(m);

    int mx = -1;
    int mx2 = -1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        ans += (b[i] * m);
    }

    sort(begin(b), end(b));
    mx = b[n-1];
    mx2 = b[n-2];
    int mn = 1e9;
    for (int i = 0; i < m; ++i) {
        cin >> g[i];
        mn = min(mn, g[i]);
    }

    if (mx > mn) {
        cout << -1 << endl;
        return;
    }



    sort(begin(g), end(g));

    for (int x : g) {
        ans += max(0LL, x - mx);
    }

    if (g[0] > mx) {
        ans += mx - mx2;
    }

    cout << ans << '\n';

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
