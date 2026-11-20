
#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
   int n, k; cin >> n >> k;
   vector<int> a(n);
  for (int i =0 ; i < n; ++i)   cin >> a[i];

  for (int i = 0; i < k; ++i) {
      // print the index of the element >= k to the right
      int x; cin >> x;
      auto it = lower_bound(a.begin(), a.end(), x);
      if (it == a.end()) cout << n + 1 << endl;
      else cout << it - a.begin() + 1 << endl;
  }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
