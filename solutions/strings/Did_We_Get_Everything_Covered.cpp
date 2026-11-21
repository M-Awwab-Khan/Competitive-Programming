#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, k, m; cin >> n >> k >> m;
    string s; cin >> s;


    int b = 0;
    unordered_set<int> st;
    string last = "";
    for (int i = 0; i < m; ++i) {
        st.insert(s[i] - 'a');

        if (st.size() == k) {
            last.push_back(s[i]);
            ++b; st.clear();
        }
    }

    if (b >= n) {
        cout << "YES" << endl;
    } else {
        string ans = string(last);
        for (int i = 0; i < k; ++i) {
            if (!st.count(i)) {
                char c = 'a' + i;
                ans += string(n - size(last), c);
                break;
            }
        }
        cout << "NO" << endl;
        cout << ans << endl;
    }


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
