#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    for (auto &s : a) cin >> s;

    const long long NEG = -1e18;
    vector<vector<long long>> dp(n, vector<long long>(3, NEG));

    auto val = [&](char c) {
        if (c == '*') return NEG;
        if (c == 'c') return 1LL;
        return 0LL;
    };

    long long ans = 0;

    // bottom row
    for (int j = 0; j < 3; j++) {
        dp[n-1][j] = val(a[n-1][j]);
        ans = max(ans, dp[n-1][j]);
    }

    for (int i = n-2; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {

            if (val(a[i][j]) == NEG) continue;

            long long best = NEG;

            if (j == 0)
                best = max(dp[i+1][0], dp[i+1][1]);
            else if (j == 1)
                best = max({dp[i+1][0], dp[i+1][1], dp[i+1][2]});
            else
                best = max(dp[i+1][1], dp[i+1][2]);

            if (best != NEG)
                dp[i][j] = best + val(a[i][j]);

            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << "\n";
}