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
    int n, m; cin >> n >> m;
    // cover [0, m] using minimum number of intervals (n)
    //

    vector<pair<int, int>> a(n); for (auto &[l, r]: a) cin >> l >> r;

    sort(a.begin(), a.end()); // sort by left endpoint

    int covered = 0;
    int i = 0;
    int count = 0;

    while (covered < m) {
        int farthest = covered;

        while (i < n && a[i].first <= covered) {
            farthest = max(farthest, a[i].second);
            ++i;
        }

        if (farthest == covered) {
            cout << -1 << '\n';
            return;
        }

        covered = farthest;
        ++count;
    }

    cout << count << '\n';

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
