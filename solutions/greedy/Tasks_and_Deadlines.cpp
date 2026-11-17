#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define pii pair<int, int>
#define int ll

void solve() {
    int n; cin >> n;
    vector<pii> arr(n); for (auto &[a, d]: arr ) cin >> a >> d;

    int time = 0;
    sort(arr.begin(), arr.end());

    int reward = 0;
    for (auto &[a, d]: arr) {
        time += a;
        reward += (d - time);
    }
    cout << reward << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
