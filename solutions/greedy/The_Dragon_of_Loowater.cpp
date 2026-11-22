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
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        vector<int> d(n); for (auto &x: d) cin >> x;
        vector<int> h(m); for (auto &x: h) cin >> x;

        sort(begin(d), end(d));
        sort(begin(h), end(h));


        int ans = 0, di = 0, hi = 0;
        while (di < n) {
            while (hi < m && h[hi] < d[di]) ++hi;

            if (hi < m) {
                ans += h[hi];
            } else break;
            ++di; ++hi;
        }
        if (di < n) {
            cout << "Loowater is doomed!" << endl;
        } else {
            cout << ans << endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
