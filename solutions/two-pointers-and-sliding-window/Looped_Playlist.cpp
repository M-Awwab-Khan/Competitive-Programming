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
    ll p; cin >> p;
    vector<int> a(n); for (int i = 0; i < n;++i) cin >> a[i];
    ll sum = accumulate(a.begin(), a.end(), 0LL);

    ll ans = p / sum;
    ll rem = p % sum;
    if (rem == 0) {
        cout << 1 << " " << ans * n << endl;
        return;
    }

    vector<int> b(2*n); for (int i = 0; i < 2*n; ++i) {
        b[i] = a[i%n];
    }

    ll csum = 0;
    int l = 0;
    int ans2 = INT_MAX;
    int idx = 0;
    for (int r = 0; r < 2*n; ++r) {
        csum += b[r];
        while (csum >= rem) {
            if ((r - l + 1) < ans2) {
                ans2 = r - l + 1;
                idx = (l % n) + 1;
            }
            csum -= b[l++];
        }
    }
    cout << idx << " " << (1LL* ans * n) + ans2 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
