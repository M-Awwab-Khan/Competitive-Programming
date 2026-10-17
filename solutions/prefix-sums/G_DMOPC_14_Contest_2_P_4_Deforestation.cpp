#include "bits/stdc++.h"
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + a[i-1];
    }

    int q; cin >> q;

    while(q--) {
        int l, r; cin >> l >> r;
        l++; r++;
        cout << pref[r] - pref[l-1] << "\n";
    }
    return 0;
}