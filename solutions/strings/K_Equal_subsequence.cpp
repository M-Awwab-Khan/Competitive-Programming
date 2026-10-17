#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    if (n == 1) {
        cout << 0 << "\n";return;
    } else if (n == 2) {
        cout << 2 << "\n"; return;
    }

    vector<int> pref(n), suff(n);

    unordered_map<int, int> mp;
    int mx = INT_MIN;
    for (int i = 0; i < n; ++i) {
        mp[a[i]]++;
        mx = max(mx, mp[a[i]]);
        pref[i] = mx;
    }
    
    unordered_map<int, int> mp2;

    mx = INT_MIN;
    for (int i = n-1; i >= 0; --i) {
        mp2[a[i]]++;
        mx = max(mx, mp2[a[i]]);
        suff[i] = mx;
    }

    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        ans = max(ans, 2*min(pref[i], suff[i+1]));
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}