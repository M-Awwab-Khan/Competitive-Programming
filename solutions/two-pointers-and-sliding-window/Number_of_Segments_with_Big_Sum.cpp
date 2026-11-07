#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n; cin >> n;
    ll s; cin >> s;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    int r = 0;
    ll csum = 0;
    ll ans = 0;

    for (int l = 0; l < n; ++l) {
        while (r < n && csum < s) {
            csum += a[r++];
        }
        if (csum >= s) ans += (n -r + 1);
        csum -= a[l];
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
