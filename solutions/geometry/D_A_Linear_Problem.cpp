#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;


using ll = long long;

void solve() {
    int n; cin >> n;

    vector<pair<ll, ll>> points(n);
    for (int i = 0; i  < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    map<pair<ll, ll>, int> freq;
    for (auto [x, y]: points) {
        if (x == 0 && y == 0) {
            cout << 1 << "\n"; return;
        }
        ll g = gcd(x, y);
        pair<ll, ll> dir = {x/g, y/g};
        freq[dir]++;
    }

    // debug(freq);

    int ans = 0;
    for (auto [k, v]: freq) {
        ans += 1;
    }
    cout << ans << "\n";
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) solve();

    return 0;
}