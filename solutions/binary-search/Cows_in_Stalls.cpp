#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n); for (auto &x: a) cin >> x;

    auto can = [&](int x) {
        int c = 1;
        int prev = a[0];
        for (int i =1; i < n; ++i) {
            if (a[i] - prev >= x) {
                ++c;
                prev = a[i];
            }
        }
        return c >= k;
    };

    int lo = 0, hi = a[n-1] - a[0];
    int ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
