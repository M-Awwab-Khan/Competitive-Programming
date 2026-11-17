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
    vector<pair<int, int>> p(n); for (int i = 0; i < n;++i) cin >>  p[i].first >> p[i].second;
    // find the kth element of the unions

    auto check = [&](int x) {
        int countLess = 0;
        for (auto [l, r] : p) {
            if (x > l) {
                countLess += min(r + 1, x) - l;
            }
        }
        return countLess <= k;
    };

    int lo = p[0].first, hi = p[0].second;
    for (auto [l, r] : p) {
        lo = min(lo, l);
        hi = max(hi, r);
    }

    int ans = lo;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
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
