#include "bits/stdc++.h"
using namespace std;

void solve() {
    long long n, m; cin >> n >> m;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    auto possible = [&](long long height) {
        long long amt = 0;
        for (int i = 0; i < n; ++i) {
            amt += max(0LL, a[i] - height);
            if (amt >= m) return true;
        }
        return amt >= m;
    };

    long long lo = 0, hi = 1e10, ans = 0;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) /2;
        if (possible(mid)) {
            ans = mid; lo = mid + 1;
        } else hi = mid - 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}