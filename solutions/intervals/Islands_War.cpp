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
    vector<pair<int, int>> a(m);
    for (auto &[l, r]: a) cin >> l >> r;

    sort(a.begin(), a.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    int j = 1;
    int ans = 0;
    int i = 0;
    while (i < m) {
        j = i + 1;
        while (j < m && a[j].first < a[i].second) ++j;
        ++ans;
        i = j;
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
