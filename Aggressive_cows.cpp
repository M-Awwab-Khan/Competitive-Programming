#include "bits/stdc++.h"
using namespace std;

void solve() {

    int n, c; cin >> n >> c;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    auto possible = [&](int dist) {
        int prev = a[0];
        int placed = 1;

        for (int i = 1; i < n; ++i) {
            if (a[i] - prev >= dist)  {
                ++placed;
                prev = a[i];
            }
        }
        return placed >= c;
    };

    int lo = 1, hi = 1e9, ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        // cout << lo << " " << hi << " " << endl;
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

    int t; cin >> t; while (t--) 
    solve();
}