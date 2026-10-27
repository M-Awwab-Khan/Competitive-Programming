#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    sort(begin(a), end(a));

    int ans = 0;
    int l = 0, r = 0;

    int mx = 0;
    while (r < n) {
        mx = max(mx, a[r]);
        if (mx <= r - l + 1) {
            ++ans;
            l = r + 1;
            r = l;
        }
        else {
            ++r;
        }
    }

    cout << ans << endl;
}

int main() {

    int t; cin >> t; while (t--) solve();
}
