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
    int n, w; cin >> n >> w;
    vector<pair<int, int>> ab(n); for (int i = 0; i < n;++i) cin >> ab[i].first >> ab[i].second;

    sort(ab.rbegin(), ab.rend());

    int ans = 0;
    for (auto [a, b]: ab) {
        int x = min(w, b);
        ans += a*x;
        w -= x;
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
