#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int l, a, b;
    cin >> l >> a >> b;
    // 0, l-1
    set<int> aa, bb;
    aa.insert(0);
    int x = a;
    while (1) {
        x %= l;
        aa.insert(x);
        x += a;
        x %= l;
        if (aa.count(x)) break;
    }
    int y = b;
    bb.insert(0);
    while (1) {
        y %= l;
        bb.insert(y);
        y += b;
        y %= l;
        if (bb.count(y)) break;
    }

    int ans = 0;
    for (auto x: aa) {
        ans += (bb.count(x) > 0);
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
