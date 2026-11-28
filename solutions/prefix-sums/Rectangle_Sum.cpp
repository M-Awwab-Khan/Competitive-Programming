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
    int r, c, q; cin >> r >> c >> q;
    vector<vector<int>> a(r + 1, vector<int>(c + 1));


    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> a[i][j];
        }
    }


    vector<vector<int>> b(r + 1, vector<int>(c + 1));

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            b[i][j] = a[i][j] + b[i-1][j] + b[i][j-1] - b[i-1][j-1];
        }
    }

    int r1, r2, c1, c2;
    while (q--) {
        cin >> r1 >> c1 >> r2 >> c2;
        cout << b[r2][c2] - b[r1-1][c2] - b[r2][c1-1] + b[r1-1][c1-1] << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
