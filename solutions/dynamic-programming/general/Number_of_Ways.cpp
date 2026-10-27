#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int s, e; cin >> s >> e;

    vector<int> dp(e + 1, 0);

    dp[s] = 1;
    for (int i = s; i <= e; ++i) {
        for (auto j: {1, 2, 3}) {
            if (i - j >= 0) dp[i] += dp[i-j];
        }
    }
    cout << dp[e] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--) solve();
    return 0;
}
