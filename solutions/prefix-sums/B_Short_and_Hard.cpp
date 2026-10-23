#include "bits/stdc++.h"
using namespace std;

using ll = long long;
using vll = vector<ll>;

void solve() {
    int n;
    cin >> n;

    vll a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) {
            cout << "0.000000\n";
            return;
        }
    }

    vector<double> pref(n + 1, 0.0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + log((double)a[i]);
    }

    double minLogGM = 1e18;

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int len = j - i + 1;
            double sumLog = pref[j] - pref[i-1];
            double logGM = sumLog / len;
            minLogGM = min(minLogGM, logGM);
        }
    }

    double ans = exp(minLogGM);
    cout << fixed << setprecision(6) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}