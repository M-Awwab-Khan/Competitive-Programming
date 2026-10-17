#include "bits/stdc++.h"
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    string a; cin >> a;

    const long long MOD = 1000000007;

    long long ans = 1;
    for (auto c: a) {
        int val = c - 'a' + 1;
        ans = (ans * val) % MOD;
    }
    cout << ans << "\n";
}