#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
int t = 0;

void solve(int c, int s) {
    vector<int> masses(2 * c, 0);
    ll total = 0;
    for (int i = 0; i < s; ++i) {
        cin >> masses[i];
        total += masses[i];
    }

    sort(begin(masses), end(masses));
    const double mean = static_cast<double>(total) / c;
    double imbalance = 0;

    cout << "Set #" << t << '\n';
    for (int i = 0; i < c; ++i) {
        const int left = masses[i];
        const int right = masses[2 * c - 1 - i];
        const ll chamberMass = static_cast<ll>(left) + right;
        imbalance += fabs(static_cast<double>(chamberMass) - mean);

        cout << ' ' << i << ':';
        if (left != 0) cout << ' ' << left;
        if (right != 0) cout << ' ' << right;
        cout << '\n';
    }

    cout << "IMBALANCE " << fixed << setprecision(5) << imbalance << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // For multiple test cases: cin >> t;
    int c , s;
    while (cin >> c >> s) {
        t++;
        solve(c, s);
    }
    return 0;
}
