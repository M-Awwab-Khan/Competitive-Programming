#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n); for (int i = 0; i < n;++i) cin >> a[i];

    sort(a.begin(), a.end());

    int ans = 0;
    int i = 0;
    for (int j= n-1; j>= 0; --j) {
        if (i > j) break;
        int y = x-a[j];
        if (i != j && a[i] <= y) ++i;
        ++ans;
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
