#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define pii pair<int, int>
#define int ll

void solve() {
    int n; cin >> n;
    vector<pii> a(n); for (auto &[c, w]: a) cin >> c >> w;

    sort(a.begin(), a.end(), [](const pii &a, const pii &b) {
        return a.second < b.second;
    });

    int i = 0;
    int j = n-1;
    int ans = LLONG_MIN;
    while (i < j) {
        // pair up maximum number of a[i] and a[j]s
        int x = min(a[i].first, a[j].first);
        a[i].first -= x;
        a[j].first -= x;
        ans = max(ans, a[i].second + a[j].second);
        if (a[i].first == 0 && a[j].first == 0) {i++;j--;}
        else if (a[i].first == 0) i++;
        else j--;
    }

    if (i == j) {
        ans = max(ans, 2*a[i].second);
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
