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
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    auto can = [&](int x) {
        int kk = 1;
        int gp = 0;
        for (auto e: a) {
           if (gp + e <= x) {
                gp += e;
           } else {
               ++kk;
               gp = e;
               if (gp > x) return false;
           }
        }
        return kk <= k;
    };

    ll lo = 0, hi = accumulate(a.begin(), a.end(), 0LL);
    ll ans = 0;
    while(lo <= hi) {
        ll mid = lo + (hi - lo) / 2;
        if (can(mid)) {
            ans = mid;
            hi = mid - 1;
        } else lo = mid + 1;
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
