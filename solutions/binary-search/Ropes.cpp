#include "bits/stdc++.h"
#include <iomanip>
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

    double l = 0;
    double r = *max_element(a.begin(), a.end());

    auto okay = [&](double len) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += (a[i] / len);
        }
        return ans >= k;
    };

    double ans = 0;
    double eps = 1e-6;
    while (r - l >= eps) {
        double mid = l + (r - l) /2;
        if (okay(mid)) {
            ans = mid;
            l = mid;
        } else r = mid;
    }
    cout << fixed << setprecision(6) << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
