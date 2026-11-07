#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, rr; cin >> n >> rr;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    ll ans = 0;

    int r = 0;
    for (int l = 0; l < n; ++l) {
        while (r < n && a[r] - a[l] <= rr) ++r;

        if (a[r] - a[l] > rr) {
            ans += n - r;
        }
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
