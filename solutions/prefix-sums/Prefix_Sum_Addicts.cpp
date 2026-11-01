#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

#define int long long

void solve() {
    int n, k; cin >> n >> k;
    vector<int> pref(n); for (int i = n-k; i < n; ++i) cin >> pref[i];

    if (n == 1 || k == 1) {
        cout << "Yes" << endl; return;
    }

    vector<int> a(n);
    a[0] = pref[0];
    for (int i = n-1; i >= 1; --i) {
        a[i] = pref[i] - pref[i-1];
    }

    auto sorted = [](vector<int> &a, int n, int k) {
        for (int i = n-k+1; i < n-1; ++i) if (a[i] > a[i+1]) return false;
        return true;
    };

    if (!sorted(a, n, k)) cout << "No" << endl;
    else {
        if (pref[n-k] <= a[n-k + 1] * (n - k + 1)) {
            cout << "Yes" << endl;
        } else cout << "No" << endl;
    }

}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
