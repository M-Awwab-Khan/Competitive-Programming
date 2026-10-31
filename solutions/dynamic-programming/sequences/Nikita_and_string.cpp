#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n + 2, vector<int>(3));

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') {
            dp[i + 1][0] = dp[i][0] + 1;
            dp[i + 1][1] = dp[i][1];
            dp[i + 1][2] = max(dp[i][1], dp[i][2]) + 1;
        } else {
            dp[i + 1][0] = dp[i][0];
            dp[i + 1][1] = max(dp[i][0], dp[i][1]) + 1;
            dp[i + 1][2] = dp[i][2];
        }
    }

    cout << max(dp[n][0], max(dp[n][1], dp[n][2])) << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
