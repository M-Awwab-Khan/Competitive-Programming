#include "bits/stdc++.h"
#include "debugging.cpp"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    set<int> st;

    for (int i = 0; i < n; ++i) st.insert(a[i]);

    int i = 0, j = n-1;

    while (i < j - 2) {
        if (*st.begin() != a[i] && *st.begin() != a[j] && *st.rbegin() != a[i] && *st.rbegin() != a[j]) {
            cout << i + 1 << " " << j + 1 << "\n"; return;
        } else if (*st.begin() == a[i] || *st.rbegin() == a[i]) {
            st.erase(a[i]);
            ++i;
        } else {
            st.erase(a[j]);
            --j;
        }
    }
    cout << -1 << "\n";
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}