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
    vector<ll> a(n + 1); for (int i = 1;i <= n; ++i) cin >> a[i];

    vector<ll> fdist(n + 1);
    fdist[1] = 0;
    fdist[2] = 1;
    for (int i = 3; i <= n; ++i) {
        fdist[i] = fdist[i-1] + ((a[i] - a[i-1] > a[i-1] - a[i-2]) ? (a[i] - a[i-1]) : 1);
    }

    vector<ll> bdist(n + 1);
    bdist[n-1] = 1;
    for (int i = n-2; i >= 1; --i) {
        bdist[i] = bdist[i + 1] + ((a[i+1] - a[i] > a[i+2] -a[i+1]) ? (a[i+1] - a[i]): 1);
    }

    int q; cin >> q;
    while (q--){
        int l, r; cin >> l >> r;
        if (l < r) cout << fdist[r] - fdist[l] << endl;
        else cout << bdist[r] - bdist[l] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
