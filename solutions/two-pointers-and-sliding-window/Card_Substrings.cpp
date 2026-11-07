#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    string s, mm; cin >> s >> mm;

    unordered_map<char, int> mp;
    for (auto c: mm) mp[c]++;
    ll ans = 0;

    unordered_map<char, int> mp2;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        mp2[s[r]]++;
        while (mp2[s[r]] > mp[s[r]]) {
            mp2[s[l++]]--;
        }

        ans += (r - l + 1);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
