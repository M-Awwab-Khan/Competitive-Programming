#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;

    int ones = 0;
    for (auto c: s) ones += c == '1';

    if (ones <= k) {
        cout << "Alice" << endl; return;
    } else if (k > n/2) {
        cout << "Alice" << endl; return;
    } else {
        cout << "Bob" << endl; return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
