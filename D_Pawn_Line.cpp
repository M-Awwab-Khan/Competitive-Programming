#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];   // start with max possible
    }

    // Left to right pass
    for (int i = 1; i < n; i++) {
        b[i] = min(b[i], b[i - 1] + 1);
    }

    // Right to left pass
    for (int i = n - 2; i >= 0; i--) {
        b[i] = min(b[i], b[i + 1] + 1);
    }

    long long cost = 0;
    for (int i = 0; i < n; i++) {
        cost += (a[i] - b[i]);
    }

    cout << cost << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}