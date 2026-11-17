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
    int n, k; cin >> n >> k;
    vector<int> a(n); for (auto &x: a) cin >> x;
    vector<int> b(n); for (auto &x: b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto check = [&](int x) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            auto it = lower_bound(b.begin(), b.end(), x - a[i]);
            ans += it - b.begin();
        }
        return ans < k;
    };

    int lo = a[0] + b[0];
    int hi = a[n-1] + b[n-1];
    int ans = lo;

    while (lo <= hi) {
        int mid = lo + (hi - lo) /2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else hi = mid - 1;
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
