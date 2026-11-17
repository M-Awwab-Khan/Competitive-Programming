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
    int d, l, n; cin >> d >> l >> n;
    vector<int> p(n + 2); for (int i = 1; i <= n; ++i) cin>> p[i];
    p[0] = 0;
    p[n + 1] = d;

    int tank = l;

    int ans = 0;
    for (int i = 0; i < p.size() -1; ++i) {
        // from i to i + 1 without refilling
        if (tank >= (p[i+1] - p[i])) tank -= (p[i + 1] - p[i]);
        // from i to i + 1 with refilling
        else {
            tank = l; ++ans;
            if (tank >= (p[i + 1] - p[i])) tank -= (p[i + 1] - p[i]);
            else {
                cout << -1 << endl;
                return;
            }
        }
        // else -1
    }
    cout << ans << endl;

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
