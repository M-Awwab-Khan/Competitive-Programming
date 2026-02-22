#include "bits/stdc++.h"
using namespace std;

#ifndef ONLINE_JUDGE
#include "debugging.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif

void solve() {
    int n, q; cin >>n >> q;
    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] += pref[i-1] + a[i-1];
    }
    // debug(pref);

    while (q--) {
        int type; cin >> type;
        
        if(type == 1) {
            int i; cin >> i;
            // swap i with i + 1;

            pref[i] -= a[i-1];
            pref[i] += a[i];
            swap(a[i-1], a[i]);

            // debug(a, pref);
        }  else {
            int l, r; cin >> l >> r;
            cout << pref[r] - pref[l-1] << "\n";
        }

    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}