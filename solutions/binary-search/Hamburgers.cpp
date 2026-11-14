#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int long long

struct Kitchen {
    ll bread, sausage, cheese;
};

struct Price {
    ll bread, sausage, cheese;
};
void solve() {
    string s; cin >> s;
    map<char, int> mp;
    for (auto c: s) mp[c]++;

    Kitchen k;
    cin >> k.bread >> k.sausage >> k.cheese;
    Price p;
    cin >> p.bread >> p.sausage >> p.cheese;

    ll r; cin >> r;

    auto can = [&](ll x) {
        ll req = 0;
        req += p.bread * max(1LL*mp['B']*x - k.bread, 0LL);
        req += p.sausage * max(1LL*mp['S']*x - k.sausage, 0LL);
        req += p.cheese * max(1LL*mp['C']*x - k.cheese, 0LL);
        return req <= r;
    };

    ll lo = 0, hi = 1;
    while(can(hi)) hi *= 2;
    ll ans = 0;
    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;
        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        } else hi = mid - 1;
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
