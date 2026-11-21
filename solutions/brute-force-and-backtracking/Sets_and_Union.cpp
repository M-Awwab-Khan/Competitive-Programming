#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n; cin>> n;
    vector<unordered_set<int>> v(n);
    unordered_set<int> u;
    for (int  i = 0; i < n; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x;
            v[i].insert(x);
            u.insert(x);
        }
    }

    int ans = -1;
    for (auto x: u) {
        unordered_set<int> temp;
       // try to make the set without x
       for (auto st: v) {
           if (st.count(x)) continue;
           else {
               temp.insert(st.begin(), st.end());
           }
       }
       ans = max(ans, (int)size(temp));
    }

    cout << ans << endl;
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
