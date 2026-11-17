#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    string s; cin >> s;
    int n = s.size();

    vector<int> ans;
    stack<int> st;

    for (int i = 0; i < n;++i) {
        if (s[i] == ')') {
            while (!st.empty() && s[st.top()] != '(') {
                st.pop();
            }
            if (!st.empty() && s[st.top()] == '(') {
                ans.push_back(st.top());
                ans.push_back(i);
                st.pop();
            }
        }  else st.push(i);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto x: ans) cout << s[x];
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
