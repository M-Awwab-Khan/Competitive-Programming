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
    vector<int> h(n + 2), p(n + 2), s(n + 2);

    auto win = [](char a, char b) {
        if (a == 'P' && b == 'H') return 1;
        if (a == 'S' && b == 'P') return 1;
        if (a == 'H' && b == 'S') return 1;
        return 0;
    };
    char c;
    for (int i = 1; i <= n; ++i) {
        cin >> c;
        h[i] = h[i-1] + (win(c, 'H'));
        p[i] = p[i-1] + (win(c, 'P'));
        s[i] = s[i-1] + (win(c, 'S'));
    }

    int mx = 0;
    for (int i = 0; i <= n; ++i) {
        int hp = h[i] + (p[n] - p[i]);
        int sp = s[i] + (p[n] - p[i]);
        int hs = h[i] + (s[n] - s[i]);
        int sh = s[i] + (h[n] - h[i]);
        int ps = p[i] + (s[n] - s[i]);
        int ph = p[i] + (h[n] - h[i]);

        mx = max(mx, max({hp, sp, hs, sh, ps, ph}));
    }
    cout << mx << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
