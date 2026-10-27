#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> d;
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            d.push_back(i);
            if (n / i != i) d.push_back(n/i);
        }
    }
    sort(d.begin(), d.end());
    // for (auto x: d) cout << x << " ";
    if (k-1 >= d.size()) cout << -1 << endl;
    else cout << d[k-1] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
