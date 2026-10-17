#include "bits/stdc++.h"
using namespace std;

void solve() {

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int q; cin >> q;
    while (q--) {
        int h; cin >> h;

        auto lo = lower_bound(a.begin(), a.end(), h);
        auto hi = upper_bound(a.begin(), a.end(), h);

        if (lo == a.begin()) cout << "X ";
        else cout << *(--lo) << " ";

        if (hi == a.end()) cout << "X\n";
        else cout << *hi << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}