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

    vector<tuple<int, int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        auto &[l, r, idx] = a[i];
        cin >> l >> r;
        idx = i;
    }

    sort(a.begin(), a.end());

    vector<int> ans(n);

    int room = 0;
    set<pair<int, int>> st;

    for (auto [l, r, idx] : a) {
        int id;

        if (!st.empty() && l > st.begin()->first) {
            auto it = st.begin();
            id = it->second;
            st.erase(it);
        }
        else {
            id = ++room;
        }

        ans[idx] = id;
        st.insert({r, id});
    }

    cout << room << endl;
    for (auto x : ans) cout << x << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
