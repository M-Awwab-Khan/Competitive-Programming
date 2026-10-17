#include "bits/stdc++.h"
using namespace std;


using ll = long long;
void solve() {

    int n, m; cin >> n >> m;
    vector<ll> a(m); for (ll &x: a) cin >> x;
    sort(a.begin(), a.end());

    vector<ll> gaps;

    for (int i = 0; i < m - 1; ++i) gaps.push_back(a[i+1] - a[i] - 1);

    gaps.push_back(a[0] + n - a[m-1] - 1);

    sort(gaps.rbegin(), gaps.rend());

    ll days = 0;
    ll saved = 0;

    for (auto g: gaps) {
        ll remaining = g - 2*days;
        if (remaining <= 0) continue;
        if (remaining == 1) {
            ++saved; ++days;
        } else {
            saved += remaining - 1;
            days += 2;
        }
    }



    cout << n - saved << "\n";

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t; while(t--) solve();

    return 0;
}