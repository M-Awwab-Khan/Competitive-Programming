#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

#define int long long

void solve() {
    int n; cin >> n;
    vector<int> b(n);
    int x;
    int y = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        y += x;
        b[i-1] = 2*i - x;
    }

    int curr = b[0];
    int ans = curr;

    for (int i = 1; i < n; ++i) {
        curr = max(curr + b[i], b[i]);
        ans = max(ans, curr);
    }

    cout << ans + y << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
