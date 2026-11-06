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
    stack<char> st;

    for (char c : s) {
        st.push(c);
        if (st.size() >= 3) {
            char a = st.top(); st.pop();
            char b = st.top(); st.pop();
            char c = st.top(); st.pop();
            if (a == 'C' && b == 'B' && c == 'A') continue;
            st.push(c);
            st.push(b);
            st.push(a);
        }

    }
    string ans = "";
    while(!st.empty()) ans += st.top(), st.pop();
    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
