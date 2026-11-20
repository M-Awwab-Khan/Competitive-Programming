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

    set<int> a; for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        a.insert(x);
    }

    for (int i = 0; i < k; ++i) {
        int x; cin >> x;
        if (a.find(x) != a.end()) cout << "YES\n";
        else cout << "NO\n";
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
