#include "bits/stdc++.h"
using namespace std;

int main() {
    int n; cin >> n;

    vector<int> f(n); for (int i = 0; i < n; ++i) cin >> f[i];

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> a[i][j];
    }

    vector<vector<int>> dp((1 << n), vector<int>(n, INT_MAX));

    // base case
    for (int i = 0; i < n; ++i) {
        dp[(1 << i)][i] = f[i];
    }

    // explore all bitmasks
    for (int mask = 0; mask < (1 << n); ++mask) {

        // find the one that is visited
        for (int i = 0; i < n; ++i) {
            if (dp[mask][i] == INT_MAX) continue;

            for (int j = 0; j < n; ++j) {
                if (mask & (1 << j)) continue;

                int nMask = mask | (1 << j);
                dp[nMask][j] = min(dp[nMask][j], dp[mask][i] + a[i][j]);
            }
        }
    }

    int complete = (1 << n) - 1;
    int ans = INT_MAX;

    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[complete][i]);
    }
    cout << ans << endl;
}
