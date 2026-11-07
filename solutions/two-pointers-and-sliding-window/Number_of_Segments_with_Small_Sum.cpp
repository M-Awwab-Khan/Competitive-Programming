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

    int l = 0;
    ll ans = 0;
    ll csum = 0;


    for (int r = 0; r < n; ++r) {
        csum += a[r];
        while (csum > s) csum -= a[l++];
        ans += r - l + 1;
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
