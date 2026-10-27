#include "bits/stdc++.h"
using namespace std;

const int MOD = 2026;
void solve() {
    int D; cin >> D;
    vector<long long> dp(D + 1, 0);
    dp[0] = 1;

    for (int sum = 1; sum <= D; ++sum) {
        for (auto x: {1, 2}) {
            if (sum - x >= 0)
            dp[sum] = (dp[sum] + dp[sum-x]) % MOD;
        }
    }


    cout << dp[D] << endl;
}

int main() {
    // int t; cin >> t; while (t--)
        solve();
}
