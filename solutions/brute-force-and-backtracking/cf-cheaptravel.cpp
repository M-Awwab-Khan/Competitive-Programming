#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int n, m, a, b; cin >> n >> m >> a >> b;
    int ans = INT_MAX;
    for (int xx = 0; xx <= n; ++xx) {
        // buying x rides independently using a rubbles
        int temp = xx*a;


        // buy rest of them using tickets.
        int rest = n - xx;
        temp += b * ((rest + m - 1) / m);
        ans = min(ans, temp);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
