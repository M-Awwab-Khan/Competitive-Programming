#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n; cin >> n;
    vector<long long> h(n); for (long long i = 0; i< n; ++i) cin >> h[i];
    vector<long long> c(n);
    for (long long i = 0; i < n; ++i) cin >> c[i];

    vector<pair<long long, long long>> hc(n); 
    for (long long i = 0;i < n; ++i) {
        hc[i] = {h[i], c[i]};
    }


    auto cost = [&](long long x) {
        long long cst = 0;
        for (long long i = 0;i  < n; ++i) {
            cst += 1LL* abs(hc[i].first - x) * hc[i].second;
        }
        // cout << cst << " " << x << endl;
        return cst;
   };

   sort(hc.begin(), hc.end());
   long long l = hc[0].first, r = hc.back().first;

   while (r - l > 3) {
    long long mid1 = l + (r - l) / 3;
    long long mid2 = r - (r - l) / 3;

    if (cost(mid1) > cost(mid2)) {
        l = mid1 + 1;
    } else r = mid2 - 1;
   }

   long long ans = LLONG_MAX;
   for (long long i = l; i <= r; ++i) {
    ans = min(ans, cost(i));
   }
   cout << ans << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long t; cin >> t; while (t--) solve();
    return 0;
}