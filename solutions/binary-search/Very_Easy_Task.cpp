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
    int n, x, y; cin >> n >> x >> y;
    if (x > y) swap(x, y);

    int l = 0;
    int r = n* y;

    auto okay = [&](int time) {
        int ans = time /x;
        ans += (time - x) /y;
        return ans >= n;
    };
    int ans = -1;
    while (l <= r){
        ll mid = (l + r) /2;
        if (okay(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
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
