#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n; cin >> n;
    set<int> a;
    set<int> b;
    int x;
    for (int i = 0; i < n;++i) {
        cin >> x; b.insert(x);
    }

    for (int i = 1; i <= 2*n; ++i) {
        if (b.count(i) == 0) a.insert(i);
    }

    int ans = 0;
    for (auto x: b) {
        auto it = a.upper_bound(x);
        if (it != a.end()){
            ++ans;
            a.erase(it);
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
