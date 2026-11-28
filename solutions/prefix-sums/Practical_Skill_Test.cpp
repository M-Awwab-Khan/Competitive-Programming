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
    int h, w, d; cin >> h >> w >> d;

    int x;
    vector<pair<int, int>> mp(h*w + 1);
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            cin >> x;
            mp[x] = {i, j};
        }
    }

    auto dis = [&](int i, int j) {
        return (abs(mp[i].first - mp[j].first) + abs(mp[i].second - mp[j].second));
    };

    vector<int> p(h*w + 1, 0);

    for (int i = d + 1; i <= h*w; ++i) {
        p[i] = p[i-d] + dis(i, i-d);
    }

    debug(p);
    int q; cin >> q;
    int l, r;
    while (q--) {
        cin >> l >> r;
        if (l == r) cout << 0 << endl;
        else cout << p[r] - p[l] << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
