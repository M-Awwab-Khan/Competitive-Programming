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
    vector<pair<int, int>> a(n); for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i].first;
        b[i].second = i;
    }

    sort(begin(a), end(a));
    sort(begin(b), end(b));

    vector<int> ans(n);
    // The smallest k values of b make the largest k values of a wins.
    for (int i = 0; i < k; ++i) {
        int ai = n - k + i;
        if (a[ai].first <= b[i].first) {
            cout << "NO" << endl;
            return;
        }
        ans[a[ai].second] = b[i].first;
    }

    // Pair the remaining values in order so every position is a non-win.
    for (int i = 0; i < n - k; ++i) {
        if (a[i].first > b[k + i].first) {
            cout << "NO" << endl;
            return;
        }
        ans[a[i].second] = b[k + i].first;
    }

    cout << "YES" << endl;
    for (auto x: ans) cout << x << " ";
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
