#include "bits/stdc++.h"
using namespace std;

void solve() {
    double A, B; cin >> A >> B;

    // newton's method
    double t0 = 0;
    for (int i = 0; i < 10; ++i) {
        t0 = t0 + (exp(-A*t0) + exp(-B*t0) - 1) / (A*exp(-A*t0) +B*exp(-B*t0));
    }
    cout << setprecision(10) << fixed;
    cout << t0 << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while (t--)
        solve();
    return 0;
}
