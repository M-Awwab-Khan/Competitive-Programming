#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int long long

void solve() {
    int k, n; cin >> k >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    auto okay = [&](int x) {
        int ans = 0;
        for (auto s: a) {
            ans += min(s, x);
        }
        return ans >= x*k;
    };

    int l = 0, r = 1e13, ans = 0;
    while (l <= r) {
        int mid = l + (r - l) /2;
        if (okay(mid)) {
            ans = mid;
            l = mid + 1;
        } else r = mid - 1;
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
