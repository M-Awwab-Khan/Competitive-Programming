#include "bits/stdc++.h"
using namespace std;
#define ll long long


struct Point {
    long double x, y;
};

long double dist(Point &a, Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

void solve() {
    int n; cin >> n;
    int k; cin >> k;
    vector<Point> points(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<long double> dp(n + 1, 1e18);
    dp[1] = 0;

    for (int i = 2; i <= n; ++i) {
        for (int j = max(i-k, 1); j <= i; ++j) {
            dp[i] = min(dp[i],   dp[j] + dist(points[j], points[i]));
        }
    }

    cout << fixed << setprecision(7) << endl;
    cout << dp[n] << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int t; cin >> t; while (t--)
        solve();
   return 0;
}
