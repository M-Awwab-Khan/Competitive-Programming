#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<string> g(n);
    for (int i = 0; i < n; i++)
        cin >> g[i];

    int ans = 0;

    for (int i = 0; i < (n+1)/2; i++) {
        for (int j = 0; j < n/2; j++) {

            int ones = 0;

            ones += g[i][j] == '1';
            ones += g[j][n-1-i] == '1';
            ones += g[n-1-i][n-1-j] == '1';
            ones += g[n-1-j][i] == '1';

            ans += min(ones, 4 - ones);
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}