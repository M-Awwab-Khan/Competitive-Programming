#include "bits/stdc++.h"
using namespace std;

using ll = long long;


ll lcm (ll a, ll b, ll limit) {
    ll g = gcd(a, b);

    __int128_t res = (__int128_t)(a/g)*b;
    if (res > limit) return limit + 1;
    return (ll)res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, l, r; cin>> n >> l >> r;
    vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    ll ans = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        ll lc = 1;
        int setbits = 0;
        bool overflow = false;

        for (int i = 0; i < n; ++i) {
            if ((1 << i) & mask) {
                setbits++;
                lc = lcm(lc, a[i], r);

                if (lc > r) {
                    overflow = true;
                    break;
                }
            }
        }
        if (overflow) continue;
        ll cnt = (r/lc) - (l-1)/lc;

        if (setbits % 2 == 0) {
            ans -= cnt;
        } else ans += cnt;
    }
    cout << ans << "\n";

    return 0;
}