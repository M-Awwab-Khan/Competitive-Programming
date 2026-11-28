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
    vector<int> a(n); for(auto &x: a) cin >>x;
    vector<int> b(n); for(auto &x: b) cin >>x;


    vector<int> dp1(n, 0);
    vector<int> dp2(n, 0);

    for (int i = 0; i < n; ++i) {
        if (i != n-1) {
            // skip
            if (a[i] + a[i + 1] < b[i]) {
                ++i;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
