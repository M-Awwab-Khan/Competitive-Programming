#include <bits/stdc++.h>
using namespace std;
# define ll long long

void solve() {

    ll n, k;
    cin >> n >> k;

    ll l = k, r = 10000000000;
    ll ans;
    while (l <= r) {
        ll mid = (l + r) / 2;
        // is mid the answer?
        if (mid - mid/n >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << endl;


}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while (t--) solve();

    return 0;
}
