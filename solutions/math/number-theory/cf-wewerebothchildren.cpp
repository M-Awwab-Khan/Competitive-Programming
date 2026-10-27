#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int n; cin >> n;
    map<ll, ll> mp;
    int x; for (int i = 0; i < n; ++i) {
        cin >> x;
        mp[x]++;
    }

    vector<ll> a(n + 1, 0);

    for (auto [k, v]: mp) {
        if (k <= 0 || k > n) continue;
        for (int i = k; i <= n; i += k) {
            a[i] += v;
        }
    }

    ll ans = LLONG_MIN;
    for (int i = 0; i <= n; ++i) ans = max(ans, a[i]);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
