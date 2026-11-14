#include <bits/stdc++.h>
using namespace std;

void solve() {
    double c; cin >> c;

    double l = 0, r = c;
    double ans;

    double eps = 1e-6;
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (mid*mid + sqrt(mid) <= c) {
            l = mid;
            ans = mid;
        }
        else r = mid;
    }
    cout << fixed << setprecision(6) << ans << endl;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	solve();
}
