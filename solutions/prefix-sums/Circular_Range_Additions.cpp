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
    int n, m; cin >> n >> m;
    vector<int> a(n + 2); for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> b(n + 2);
    int l, r, x;
    while (m--) {
        cin >> l >> r >> x;
        b[l] += x;
        if (l > r) {
            b[n + 1] -= x;
            b[1] += x;
       }
        b[r + 1] -= x;
    }

    for (int i = 1; i<= n; ++i) {
        b[i] += b[i-1];
    }

    for (int i = 1; i <= n; ++i) {
        cout << a[i] + b[i] << " ";
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
