#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, T; cin >> n >> T;
    long long ans = 0;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    if (n == 0) {
        cout << T << "\n";
        return;
    }
    ans += a[0];

    long long curr = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < curr + 100) continue;
        else {
            ans += a[i] - (curr + 100);
            curr = a[i];
        }
    }
    ans += max(0LL, T - (curr + 100));
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}