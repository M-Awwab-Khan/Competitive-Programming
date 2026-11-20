#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    string s; cin >> s;

    int ans = 0;
    for (auto c: s) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || (c >= '0' && c <= '9' && (c - '0') % 2)) ++ans;
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
