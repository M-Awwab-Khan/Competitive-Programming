#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    ll n; cin >> n;
    ll k; cin >> k;

    if (k > n*(n-1)/2) {
        cout << -1 << "\n"; return;
    }

    vector<ll> a(n);
    ll j = 0;
    ll i = n;
    while (true) {
        ll chaos = min(k, n-(j+1));
        k -= chaos;
        a[n-chaos-1] = i;
        --i;
        ++j;
        if (k == 0) break;
    }


    ll x = 1;
    for(ll i = 0; i < n; ++i) {
        if (a[i] == 0) a[i] = x++;
    }

    for (auto x: a) cout << x << " ";
    cout << "\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t; cin >> t; while(t--)
    solve();

    return 0;
}