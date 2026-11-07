#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int N; cin >> N;
    ll s; cin >> s;
    vector<int> a(N); for (int i = 0; i < N; ++i) cin >> a[i];

    int ans = 0;
    int l = 0;
    ll csum = 0;
    for (int r = 0; r < N; ++r) {

        csum += a[r];
        while (csum > s) {
            csum -= a[l++];
        }

        ans = max(ans, r - l + 1);
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
