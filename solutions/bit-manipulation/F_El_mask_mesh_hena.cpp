#include "bits/stdc++.h"
using namespace std;

void no() {cout << "NO" << "\n";}
void yes() {cout << "YES" << "\n";}

void solve() {
    int n, q; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin>> a[i];

    int ans = a[0];
    for (int i = 0; i < n; ++i) ans &= a[i];
    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while (t--)
    solve();
    return 0;
}