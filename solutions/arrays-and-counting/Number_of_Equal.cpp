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
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b(m); for (int i = 0; i < m; ++i) cin >> b[i];


    unordered_map<int, int> mpb;

    for (auto x: b) mpb[x]++;

    ll ans = 0;

    for (auto x: a) ans += mpb[x];
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
