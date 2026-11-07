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
    ll c; cin >> c;
    string s; cin >> s;
    ll a = 0, b = 0, ab = 0;
    int ans = 0;

    int l = 0;
    for (int r = 0; r< n;++r) {
        a += s[r] == 'a';
        b += s[r] == 'b';

        if (s[r] == 'b') ab += a;
        while (ab > c) {
            if (s[l] == 'a') {ab -= b; --a;}
            if (s[l] == 'b') b -= 1;
            ++l;
        }

        ans = max(ans, r - l + 1);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
