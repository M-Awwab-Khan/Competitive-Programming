#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define endl '\n'

void solve() {
    ll x, y; cin >> x >> y;
    

    if (x == y) {
        cout << 0 << endl; return;
    }
    if (x < y) {
        int ans = 0;
        while (x < y) {
            x *= 2;
            ans++;
        }
        cout << ans << endl;
    } else {
        if (y < 3) {
            cout << -1 << endl; return;
        }
        int ans = 0;
        // choose the smallest integer m such that 3m/2 is strictly greater than x
        // (3*m + 1)/2 > x;
        while (x > y) {

            
            ll l = 0, r = 2*x;
            ll m;
            while (l <= r) {
                ll mid = (l + r) /2;
                if ((3*mid + 1) /2 > x) {
                    m = mid; 
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            
            ans += 1;

            if (ans > 50) {
                cout << -1 << endl;
                return;
            }
            
            if (y >= m) break;
            x = m;
        }
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while (t--) solve();

    return 0;
}