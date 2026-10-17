#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (auto &x: a) cin >> x;

    unordered_map<int, int> freq;
    for (auto x: a) freq[x]++;

    int mx = *max_element(a.begin(), a.end());

    int ans = 0;

    if (freq[mx] == 1) ++ans;

    int i = 0;
    for (int j = 0; j < n; ++j) {
        if (a[j] ==mx) i = j;
    }

    ans += (n - i - 1);
    cout << ans << "\n";

}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t; while(t--)
    solve();
}