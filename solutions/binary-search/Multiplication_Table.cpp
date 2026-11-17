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
    int n, k; cin >> n >> k;

    auto check = [&](int x) {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (x <= i) continue;
            else if (x > i*n) ans += n;
            else ans += (x-1)/i;
        }
        return ans < k;
    };

    int lo = 1, hi = n*n;
    int ans = lo;
    while(lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid; lo = mid + 1;
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
