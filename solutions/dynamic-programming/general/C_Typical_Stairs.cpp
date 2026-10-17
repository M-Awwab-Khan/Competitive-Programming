#include "bits/stdc++.h"
using namespace std;

const int MOD = 1000000007;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(k); for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    set<int> st(a.begin(), a.end());

    // for (int i = 0; i < k; ++i) dp[k] = -1;

    for (int i = 1; i <= n; ++i) {
        if (i - 1 >= 0) dp[i] = (dp[i] +  dp[i-1]) % MOD;
        if (i - 2 >= 0) dp[i] = (dp[i] + dp[i-2]) % MOD;
        if (st.count(i)) dp[i] = 0;
    }
    cout << dp[n] % MOD << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    solve();
    return 0;
}