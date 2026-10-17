#include "bits/stdc++.h"
using namespace std;

const int INF = 1e9;

void solve() {
    int X;
    cin >> X;
    int N = X / 100;

    // wind[altitude][segment]
    vector<vector<int>> wind(10, vector<int>(N));

    // input comes from altitude 9 down to 0
    for (int h = 9; h >= 0; --h) {
        for (int d = 0; d < N; ++d) {
            cin >> wind[h][d];
        }
    }

    // dp[altitude][segment]
    vector<vector<int>> dp(10, vector<int>(N + 1, INF));

    // start at altitude 0 before any segment
    dp[0][0] = 0;

    for (int d = 1; d <= N; ++d) {
        for (int h = 0; h <= 9; ++h) {

            // stay
            if (dp[h][d - 1] != INF) {
                dp[h][d] = min(dp[h][d],
                               dp[h][d - 1] + 30 - wind[h][d - 1]);
            }

            // climb (from h-1 to h)
            if (h > 0 && dp[h - 1][d - 1] != INF) {
                dp[h][d] = min(dp[h][d],
                               dp[h - 1][d - 1] + 60 - wind[h][d - 1]);
            }

            // sink (from h+1 to h)
            if (h < 9 && dp[h + 1][d - 1] != INF) {
                dp[h][d] = min(dp[h][d],
                               dp[h + 1][d - 1] + 20 - wind[h][d - 1]);
            }
        }
    }

    // must end at altitude 0 after N segments
    cout << dp[0][N] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
        if (T) cout << "\n";  // blank line between cases
    }

    return 0;
}