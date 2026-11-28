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
    int r, c, m; cin >> r >> c >> m;
    vector<vector<int>> a(r + 1, vector<int>(c + 1));

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> diff(r + 2, vector<int>(c + 2));


    int r1, c1, r2, c2, x;
    while(m--) {
        cin >> r1 >> c1 >> r2 >> c2 >> x;
        diff[r1][c1] += x;
        diff[r2 + 1][c2 + 1] += x;
        diff[r1][c2 + 1] -= x;
        diff[r2 + 1][c1] -= x;
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            diff[i][j] += diff[i][j-1];
        }
    }
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            diff[i][j] += diff[i-1][j];
        }
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cout << a[i][j] + diff[i][j] << " ";
        }
        cout << endl;
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
