#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

#define int long long

void solve() {
   int n; cin >> n;
   vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
   vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
   sort(a.begin(), a.end());

   vector<int> pref(n);
   pref[0] = b[0];
  for (int i = 1; i < n; ++i) {
      pref[i] = pref[i-1] + b[i];
  }

  int ans = LLONG_MIN;
  for (int i = 0; i < n; ++i) {
     int diff = a[i];
    int rest = n - i;

    auto idx = upper_bound(pref.begin(), pref.end(), rest) - pref.begin();
    debug(idx * diff);
    ans = max(ans, (idx) * diff);
// [0, 2, 2, 3, 4, 5]
  }

  cout << ans << endl;

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
