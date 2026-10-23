#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<long long> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    vector<long long> b(n); for (int i = 0; i < n; ++i) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long ans = 0;
    for (int i = 0; i < n; ++i) ans += abs(a[i] - b[i]);

    cout << ans << endl;
}

int main() {
    // int t; cin >> t; while(t--)
    solve();
}
