#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];

    auto can = [&](ld x) {
        vector<ld> temp(n);
        for (int i =0 ; i < n; ++i) temp[i] = a[i] - x*b[i];

        sort(temp.rbegin(), temp.rend());
        ld sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += temp[i];
        }
        return sum >= 0;
    };

    ld l = 0, r = 1e10;
    for (int i = 0; i < 100; ++i) {
        ld mid = l + (r -l) /2;
        if (can(mid)) l = mid;
        else r = mid;
    }
    cout << fixed << setprecision(6) << l << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
