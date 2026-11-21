#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n; cin >> n;

    int x = INT_MAX, y = INT_MAX;
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        int v; cin >> v;

        if (v <= x && v <= y) {
            if (x < y) x= v;
            else y = v;
        }

        else if (v <= x) {
            x = v;
        }
        else if (v <= y) {
            y = v;
        }
        else {
            ++ans;
            if (x < y) x = v;
            else y = v;
        }
    }

    cout << ans << '\n';
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
