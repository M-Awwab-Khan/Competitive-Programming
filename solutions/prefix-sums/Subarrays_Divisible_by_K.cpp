#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int ll

void solve() {
    int n, s; cin >> n >> s;

    map<int, int> mp;
    mp[0] = 1;
    int ans = 0;
    int sum = 0;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
       sum +=  x;
       sum %= s;
       if (sum < 0) sum += s;
       ans += mp[sum];
       mp[sum]++;
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
