#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
   int a, b, c; cin >> a >> b >> c;
   vector<int> x;
   x.push_back(a);
   x.push_back(b);
   x.push_back(c);

   debug(x);
   sort(x.begin(), x.end());
   if(abs(x[0] - x[1]) == 1 && abs(x[1] - x[2]) == 1) {
       cout << "YES";
   } else {
       cout << "NO";
   }
   cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
