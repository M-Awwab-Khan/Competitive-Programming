#include "bits/stdc++.h"
using namespace std;
 vector<long long> pow2(105);
const int MOD = 998244353;
void solve() {
    string s; cin >> s;

   
     long long ans = 0;
     for (int i = 1; i < s.size(); ++i) {
        ans = (ans + pow2[i]) % MOD;
     }

    bool valid = true;
    for (int i = 0; i < s.size(); ++i) {
        int rem = s.size() - i - 1;
        char c = s[i];
        if ('4' < c) ans = (ans + pow2[rem]) % MOD;

        if ('7' < c) ans = (ans + pow2[rem]) % MOD;

        if ('4' == c || '7' == c) continue;

        valid = false;
        break;
    }

    if (valid) ans = (ans + 1) % MOD;
    cout << ans << "\n";
}

int main() {

    ios::sync_with_stdio(0);cin.tie(0);
     pow2[0] = 1;
    for(int i = 1; i < 105; ++i) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }

    int t; cin >> t; while(t--)
    solve();

    return 0;
}