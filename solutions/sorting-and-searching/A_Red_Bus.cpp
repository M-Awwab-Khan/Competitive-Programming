#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n/2; ++i) ans += a[i];

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}