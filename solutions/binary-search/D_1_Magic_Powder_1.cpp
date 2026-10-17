#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];

    auto possible = [&](int cookies) {
        long long need = 0;
        for (int i = 0; i < n; ++i) {
            need += max(0LL, (1LL * a[i] * cookies) - 1LL *b[i]);
            if (need > k) return false;
        }
        return need <= k;
    };

    int lo = 0, hi = 1e9, ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (possible(mid)) {
            ans = mid; lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << ans << "\n";

}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    // int t; cin >> t; while (t--)
    solve();
    return 0;
}