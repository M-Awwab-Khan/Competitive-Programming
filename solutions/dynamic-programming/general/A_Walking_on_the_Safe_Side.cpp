#include "bits/stdc++.h"
using namespace std;

int t;

void solve() {
    int R, C; cin >> R >> C;
    cin.ignore();
    vector<string> mat(R, string(C, '.'));

    string line;
    for (int i = 0; i < R; ++i) {
        getline(cin, line);
        stringstream ss(line);
        int st; ss >> st;
        
        int x; 
        while (ss >> x) {
            mat[st-1][x-1] = '#';
        }
    }

    vector<vector<long long>> dp(R, vector<long long>(C, 0));
    dp[0][0] = mat[0][0] != '#';

    auto inRange  = [&](int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    };
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (mat[i][j] != '#') {
                if (inRange(i-1, j)) dp[i][j] += dp[i-1][j];
                if (inRange(i, j-1)) dp[i][j] += dp[i][j-1];
            }
        }
    }

    // for (int i = 0; i < R; ++i) {
    //     for (int j = 0; j < C; ++j) {
    //         cout << dp[0][0] << " ";
    //     }
    //     cout << endl;
    // }
    cout << dp[R-1][C-1] << "\n";
    if (t != 0) cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t; while(t--)
    solve();

    return 0;
}