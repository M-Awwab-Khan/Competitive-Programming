#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int n, x; cin >> n >> x;
    int ans = 0;

    for (int a = 1; a + a + 1 <= n && a + 2 <= x; ++a) {
        for (int b = 1; a*b + b + a <= n && a + b + 1 <= x; ++b) {
            int c1 = (n - a*b) / (a + b);
            int c2 = x - a - b;

            ans += min(c1, c2);
        }
    }
    cout << ans << endl;
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
