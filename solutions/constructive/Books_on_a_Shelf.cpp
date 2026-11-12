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
    vector<int> a(n); for (int i = 0; i < n;++i) cin >> a[i];

    sort(a.begin(), a.end());

    vector<int> b(n);
    int left = 0, right = n - 1;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) b[left++] = a[i];
        else             b[right--] = a[i];
    }

    int ans = min(2, n);
    set<int> st;
    st.insert(0); st.insert(n-1);
    for (int i = 1; i < n;++i) {
        if (b[i] > b[i-1]) st.insert(i);
    }
    for (int i = n-2; i >= 0; --i) {
        if (b[i] > b[i+1]) st.insert(i);
    }

    cout << st.size() << endl;
    for (auto x: b) cout << x << " ";
    cout << endl;
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
