#include "bits/stdc++.h"
using namespace std;

void solve() {
    int H, N; cin >> H >> N;
    vector<int> a(N), b(N); for (int i = 0; i < N; ++i) {
        cin >> a[i] >> b[i];
    }


    vector<long long> dp(H + 1, LLONG_MAX);
    dp[0] = 0;

    for (int i = 1; i <= H; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i - a[j]>= 0) {
                dp[i] = min(dp[i - a[j]] + b[j], dp[i]);
            } else {
                // the jth spell reduces the health below zero
                dp[i] = min(1LL* b[j], dp[i]);
            }
        }
    }
    cout << dp[H] << endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}