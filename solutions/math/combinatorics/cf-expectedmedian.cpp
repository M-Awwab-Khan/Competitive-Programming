#include "bits/stdc++.h"
using namespace std;

using ll = long long;

const int N = 2e5 + 1;
const int MOD = 1e9 + 7;
vector<ll> fact(N + 1);
vector<ll> invFact(N + 1);

ll modPow(ll a, ll b) {
    ll result = 1;
    while (b > 0) {
        if (b & 1) result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
    }

    invFact[N] = modPow(fact[N], MOD-2);

    for (int i = N-1; i >= 0; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
}

ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

void solve() {
    int n, k; cin >> n >> k;
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        mp[x]++;
    }
    if (mp[1] < (k + 1)/2) {
        cout << 0 << endl;
        return;
    }

    ll ans = 0;
    for (int i = (k + 1)/2; i <= min(k, mp[1]); ++i) {
        ans += nCr(mp[1], i) * nCr(mp[0], k-i) % MOD;
    }
    cout << ans % MOD << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    precompute();
    while (t--) solve();
    return 0;
}
