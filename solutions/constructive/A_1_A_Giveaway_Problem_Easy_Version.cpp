#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

void solve() {
    int n; cin >> n;
    set<int> st;
    set<int> st2;
    vector<int> ans(n);
    for (int i = 1; i <= n; ++i) {
        cin >> ans[i-1];
    } 

    for (auto x: ans) st.insert(x);

    for (int i = 1; i <= n; ++i) {
        if (st.count(i) == 0) {
            st2.insert(i);
        }
    }
    // debug(ans, st, st2);

    for (int i = 0; i < n; ++i) {
        if (ans[i] == 0) {
            ans[i] = *st2.begin();
            st2.erase(st2.begin());
        }
    }
    for (auto x: ans) cout << x << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}