#include "bits/stdc++.h"
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    int n; cin >> n;
    vll a(n); for (int i = 0;i < n;++i) cin >> a[i];
    vll b(n); for (int i = 0;i < n;++i) cin >> b[i];

    multiset<ll> sa(a.begin(), a.end());
    multiset<ll> sb(b.begin(), b.end());


    ll ans = 0;
    ll j = n;
    for (int i = 0; i < n; ++i) {
        auto it = sb.lower_bound(a[i]);
        if (it == sb.end()) {
            continue;
        } else {
            sb.erase(it);
            ans += j;
            --j;
        }
    }
    cout <<  (ans) << "\n";
    

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();


    return 0;
}