#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int a, b, k; cin >> a >> b >> k;

    vector<int> boys(k);
    vector<int> girls(k);

    vector<int> boysfreq(a + 1, 0);
    vector<int> girlsfreq(b+ 1, 0);

    for (int i = 0; i < k; ++i) {
        cin >> boys[i];
        boysfreq[boys[i]]++;
    }
    for (int i = 0; i < k; ++i){
        cin >> girls[i];
        girlsfreq[girls[i]]++;
    }

    ll ans = 0;

    for (int i = 0; i < k; ++i) {
        pair<int, int> p = {boys[i], girls[i]};
        ll temp = (k - boysfreq[p.first] - girlsfreq[p.second] + 1);
        ans += temp;
    }
    cout << ans / 2 << endl;

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
