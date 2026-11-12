#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int long long

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int i = n-1;
    while (i >= 0 && a[i] <= 0) --i;
    if (i < 0) {
        cout << "Bob" << endl; return;
    }

    int deltaParity = 0;
    vector<int> eventParity(n, 0);
    bool aliceWins = false;

    for (int j = i; j >= 0; --j) {
        if (j + k + 1 < n) {
            deltaParity ^= eventParity[j + k + 1];
        }

        int pileParity = (a[j] & 1) ^ deltaParity;
        if (pileParity) {
            aliceWins = !aliceWins;
            eventParity[j] = 1;
            deltaParity ^= 1;
        }
    }

    cout << (aliceWins ? "Alice" : "Bob") << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
