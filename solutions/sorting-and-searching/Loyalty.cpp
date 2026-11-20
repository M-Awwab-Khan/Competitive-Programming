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
    int n, x; cin >> n >> x;
    vector<int> a(n); for (auto &y: a) cin >> y;
    if (n == 1) {
        cout << ((a[0] / x) ? a[0] : 0 )<< endl;
        cout << a[0] << endl;
        return;
    }

    sort(a.begin(), a.end());

    vector<int> b;
    int i = 0, j = n-1;
    int s = 0;
    int ans = 0;
    while (i < j) {
        if ((s + a[j]) / x > (s / x)) {
            s += a[j];
            ans += a[j];
            b.push_back(a[j]);
            --j;
            continue;
        }
        if ((s + a[i]) / x > (s/x)) ans += a[i];
        s += a[i];
        b.push_back(a[i]);
        ++i;
    }

    if (b.size() != n && i == j) {
        ans += ((s + a[i])/x > s/x) ? a[i] : 0;
        b.push_back(a[i]);
    }
    cout << ans << endl;
    for (auto y: b) cout << y << " ";
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
