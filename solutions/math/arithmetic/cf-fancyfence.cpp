#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    int n; cin >> n;
    cout << ((360 % (180 - n) == 0) ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
