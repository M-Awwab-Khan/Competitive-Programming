#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    ll n, m, s, A, B; cin >> n >> m >> s >> A >> B;
    vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    vector<ll> b(m); for (int i = 0; i < m; ++i) cin >> b[i];

    sort(a.begin(), a.end(), [](ll aa, ll bb) {return aa > bb;});
    sort(b.begin(), b.end(), [](ll aa, ll bb) {return aa > bb;});

    vector<ll> prefA(n + 1); for (int i = 1; i <= n; ++i) prefA[i] = prefA[i-1] + a[i-1];
    vector<ll> prefB(m + 1); for (int i = 1; i <= m; ++i) prefB[i] = prefB[i-1] + b[i-1];

    ll ans = 0;

    for (int x = 0; x <= n; ++x) {
        if (1LL * x * A > s) break;
        ll y = min(m, (s - x*A)/B);

        ans = max(ans, prefA[x] + prefB[y]);
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
