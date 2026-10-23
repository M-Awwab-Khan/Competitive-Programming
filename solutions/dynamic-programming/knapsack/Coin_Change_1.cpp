#include "bits/stdc++.h"
using namespace std;

const long long MOD = 1e9 + 7;
void solve() {
    int n, x; cin >> n >> x;
    vector<int> coins(n); for (int i = 0; i < n; ++i) cin >> coins[i];

    vector<long long> dp(x + 1, 0);
    dp[0] = 1;

    for (auto coin: coins) {
        for (long long sum = coin; sum <= x; sum++) dp[sum] = (dp[sum] + dp[sum - coin]) % MOD;
    }

    cout << dp[x] << endl;
}
int main () {
    // int t; cin >> t; while (t--)
        solve();
}
