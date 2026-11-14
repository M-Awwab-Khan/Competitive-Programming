#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int long long

struct Person {
    int x, v;
};

void solve() {
    int n; cin >> n;
    vector<Person> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].v;


    auto can = [&](double t) {
        double l = -1e100;
        double r = 1e100;

        for (const auto& person : p) {
            l = max(l, (double)person.x - t * person.v);
            r = min(r, (double)person.x + t * person.v);
        }

        return l <= r;
    };

    double lo = 0, hi = 1e12;
    for (int iteration = 0; iteration < 100; ++iteration) {
        double mid = lo + (hi - lo) / 2;
        if (can(mid)) hi = mid;
        else lo = mid;
    }

    cout << fixed << setprecision(10) << hi << '\n';

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
