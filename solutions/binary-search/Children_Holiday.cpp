#include "bits/stdc++.h"
using namespace std;

#define int long long

struct X {
    int t, z, y;
};

void solve() {
    int m, n;
    cin >> m >> n;

    vector<X> a(n);

    for (int i = 0; i < n; ++i)
        cin >> a[i].t >> a[i].z >> a[i].y;

    auto calc = [&](int time, X x) {
        int cycle = x.t * x.z + x.y;
        int bl = x.z * (time / cycle);
        int rem = time % cycle;

        bl += min(rem / x.t, x.z);
        return bl;
    };

    auto okay = [&](int time) {
        int ans = 0;

        for (auto x : a) {
            ans += calc(time, x);
            if (ans >= m) return true;
        }

        return false;
    };

    int l = 0, r = 1; int ans = 0;

    while (!okay(r)) r *= 2;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (okay(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << '\n';

    int remaining = m;

    for (auto x : a) {
        int cnt = min(remaining, calc(ans, x));

        cout << cnt << " ";
        remaining -= cnt;
    }

    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
