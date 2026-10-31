#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

#define int long long

void solve() {
    int n, k, q; cin >> n >> k >> q;
    vector<int> a(200005, 0);

    int l, r;
    for (int i = 0; i < n; ++i) {
        cin >> l >> r;
        a[l]++;
        a[r+1]--;
    }

    for (int i = 1; i < 200005; ++i) a[i] += a[i-1];

    vector<int> pref(200005, 0);
    for (int i = 1; i < 200005; ++i) {
        pref[i] = pref[i-1] + (a[i] >= k);
    }

    while (q--) {
        int aa, b; cin >> aa >> b;
        debug(aa, b);

        // how many values in the range a[a...b] are >= k;
        cout << pref[b] - pref[aa-1] << endl;

    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
