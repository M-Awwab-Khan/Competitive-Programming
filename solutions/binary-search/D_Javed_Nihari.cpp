#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
using ll = long long;

void solve() {
    int n; cin >> n;
    int k; cin >> k;

    vector<int> a(n); for (int i = 0;i < n; ++i) {
        cin >> a[i];
    }


    auto check = [&](int x) {
        int mn = a[0];
        int mx = a[0];
        int segments = 1;
        for (int i = 1; i < n; ++i) {
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);

            if (mx - mn > x) {
                ++segments;
                mn = mx = a[i];
            }
        }
        return segments <= k;
    };

    int lo = 0, hi = 1e9;
    int ans = 0;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid; hi = mid - 1;
        } else lo = mid + 1;
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