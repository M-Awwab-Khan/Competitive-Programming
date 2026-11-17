#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int long long

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    map<pair<int, int>, int> mp;
    map<int, pair<int, int>> mp2;
    int i = 1;
    for (auto &[l, r]: a) {
        cin >> l >> r;
        mp[{l, r}] = i;
        mp2[i] = {l, r};
        i++;
    }

    sort(a.begin(), a.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    vector<int> ans;
    ans.push_back(mp[a[0]]);
    for (int i = 1; i < n; ++i) {
        if (a[i].first >= mp2[ans.back()].second) ans.push_back(mp[a[i]]);
    }
    cout << ans.size() << endl;
    for (auto x: ans) cout << x << " ";
    cout << endl;

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
