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
    string a; cin >> a;

    int ans = 0;

    for (char c = 'z'; c >= 'a'; --c) {
        int i = 0, j = n-1;
        while (i < j) {
            if ((a[i] == c && a[j] < c) || (a[j] == c && a[i] < c)) goto decrease;
            ++i; --j;
        }
        goto skip;

        decrease:;
        for (auto &x: a) if ( x == c) --x;
        ++ans;
        skip:;
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
