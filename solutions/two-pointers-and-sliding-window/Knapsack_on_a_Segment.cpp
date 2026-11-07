#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, s; cin >> n >>s;
    vector<int> w(n); for (int i = 0; i < n; ++i) cin >> w[i];
    vector<int> c(n); for (int i = 0; i < n; ++i) cin >> c[i];

    ll wsum = 0;
    ll csum = 0;
    ll ans = 0;

    int l = 0;
    for (int r = 0; r < n; ++r) {
        wsum += w[r];
        csum += c[r];

        while (wsum > s) {
            wsum -= w[l];
            csum -= c[l];
            ++l;
        }
        ans = max(ans, csum);
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
