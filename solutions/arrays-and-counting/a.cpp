#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

        map<int, int> mp;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += mp[a[i] - i];
            mp[a[i] - i]++;
        }
        cout << ans << endl;


    }
}
