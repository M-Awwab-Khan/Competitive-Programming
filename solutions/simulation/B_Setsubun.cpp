#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int ans = n;
    int ans2 = 0;
    while (n < k) {
        n += (ans + 1);
        ans2 += 1;
        ans++;
    }
    cout << ans2 << "\n";
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