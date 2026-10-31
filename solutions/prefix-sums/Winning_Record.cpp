#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;

    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + (s[i-1] =='W');
    }
    string ans = "";

    while(k--) {
        int l, r; cin >> l >> r;
        ans += (2*(pref[r] - pref[l-1]) > (r - l + 1)) ? "Y" : "N";
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
