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
    int n, m, k; cin >> n >> m >> k;

    vector<int> a(n); for (auto &x: a) cin >> x;
    vector<int> b(m); for (auto &x: b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0;

    int ans = 0;
    while (i < n && j < m) {
        int req = a[i];
        // [req-k, req+k] is acceptable

        if (b[j] < req - k) {
            ++j; // too small
        } else if (b[j] > req + k) {
            ++i; // too large
        } else {
            ++ans;
            ++i;
            ++j;
        }

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
