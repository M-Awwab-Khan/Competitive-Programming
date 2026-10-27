// GIVING UP :)
#include <bits/stdc++.h>
using namespace std;
# define ll long long

void solve() {
    int n; cin >> n;
    vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    map<ll, ll> mp; for (auto &x: a) mp[x]++;
    ll mx = *max_element(a.begin(), a.end());

    vector<ll> b(mx + 1, 0);

    for (int i = 1; i <= mx; ++i) {
        if (i - 2 >= 0) b[i] = max(b[i-1], b[i-2] + 1LL*mp[i]*i);
        else b[i] = max(b[i-1], 1LL*mp[i]*i);
    }

    cout << b[mx] << endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    solve();
    return 0;
}

// oh time increased.
