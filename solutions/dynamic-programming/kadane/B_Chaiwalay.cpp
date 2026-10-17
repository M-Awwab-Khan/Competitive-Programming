#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    ll n; cin >> n;
    vector<ll> c(n); for (ll i = 0; i < n; ++i) cin >> c[i];

    vector<ll> p(n); for (ll i = 0; i < n; ++i) cin >> p[i];

    for (ll i = 0;i < n; ++i) p[i] -= c[i];

    /// kadane's

    ll ans = 0;
    ll curr = 0;
    for (ll i = 0; i < n; ++i) {
        curr = max(p[i], curr + p[i]);
        ans = max(ans, curr);
    }
    
    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t; cin >> t; while(t--)
    solve();

    return 0;
}