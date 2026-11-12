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
    string s; cin >> s;

    char curr = 'R';

    int ans = 0;
    for (auto c: s) {
        if (c != curr) {
            curr = (curr == 'R') ? 'B' : 'R';
            ans++;
        }
        curr = (curr == 'R') ? 'B' : 'R';
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
