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

    int cur = 0;
    for (int i = 0; i < k; ++i) {
        if (s[i] == 'B') ++cur;
    }

    int ans = cur;
    for (int i = k; i < n; ++i) {
        cur += (s[i] == 'B');
        if (s[i-k] == 'B') --cur;
        ans = max(ans, cur);
    }

    cout << k - ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
