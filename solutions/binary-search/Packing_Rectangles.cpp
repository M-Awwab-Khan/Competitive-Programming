#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;


void solve() {
    ll w, h, n;
    cin >> w >> h >> n;

    auto fits = [&](ll side) {
        ll cols = side / w;
        ll rows = side / h;

        if (rows == 0) return false;

        // Check cols * rows >= n without multiplying.
        ll neededCols = n / rows + (n % rows != 0);
        return cols >= neededCols;
    };

    ll lo = 0;
    ll hi = max(w, h);

    while (!fits(hi)) hi *= 2;

    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (fits(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
