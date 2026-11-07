#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n1, n2, n3, n4; cin >> n1;
    vector<int> a(n1); for (int i = 0; i < n1 ;++i) cin >> a[i];
    cin >> n2;
    vector<int> b(n2); for (int i = 0; i < n2 ;++i) cin >> b[i];
    cin >> n3;
    vector<int> c(n3); for (int i = 0; i < n3 ;++i) cin >> c[i];
    cin >> n4;
    vector<int> d(n4); for (int i = 0; i < n4 ;++i) cin >> d[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    sort(d.begin(), d.end());

    int aa = 0, bb = 0, cc = 0, dd = 0;
    vector<int> ans(4, INT_MAX);
    int diff = INT_MAX;

    while (aa < n1 && bb < n2 && cc < n3 && dd < n4) {
        int mn = min({a[aa], b[bb], c[cc], d[dd]});
        int mx = max({a[aa], b[bb], c[cc], d[dd]});

        if (mx - mn < diff) {
            diff = mx - mn;
            ans[0] = a[aa];
            ans[1] = b[bb];
            ans[2] = c[cc];
            ans[3] = d[dd];
        }
        // advance the minimum pointer
        if (a[aa] == mn) {++aa; continue;}
        if (b[bb] == mn) {++bb; continue;}
        if (c[cc] == mn) {++cc; continue;}
        if (d[dd] == mn) {++dd; continue;}
    }

    for (auto x: ans) cout << x << " ";
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
