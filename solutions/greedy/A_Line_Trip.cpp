#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, x; cin >> n >>x;
    vector<int> a(n + 2); for (int i = 1;i  <= n; ++i) cin >> a[i];
    a[0] = 0;
    a[n+1] = x;

    int ans = INT_MIN;
    for (int i = 0; i < n+1; ++i) {
        ans = max(ans, abs(a[i+1] - a[i]));
    }
    cout << (max(ans, 2*(x-a[n]))) <<"\n";
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >>t; while(t--)
    solve();

    return 0;
}