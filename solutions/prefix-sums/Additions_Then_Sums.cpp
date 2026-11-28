
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
    int n, m, q; cin >> n >> m >> q;
    vector<int> a(n); for (auto &i: a) cin >> i;
    vector<int> b(n + 2);

    int l, r, x;

    while (m--) {
        cin >> l >> r >> x;
        b[l] += x;
        b[r + 1] -= x;
    }

    for (int i = 1; i <= n; ++i) {
        b[i] += b[i-1];
    }

    for (int i = 1; i <= n; ++i) {
        a[i-1] += b[i];
    }

    vector<int> pref(n + 2);
    for (int i = 1; i <= n; ++i) {
        pref[i] += pref[i-1] + a[i-1];
    }

    while (q--) {
        cin >> l >> r;
        cout << pref[r] - pref[l-1] << endl;
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
