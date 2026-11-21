#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int ll

void solve() {
    int a, b, c; cin >> a >> b >> c;
    int m; cin >> m;

    vector<int> usb;
    vector<int> ps2;
    int x;
    string type;
    for (int i = 0; i < m; ++i) {
        cin >> x>> type;
        if (type == "USB") usb.push_back(x);
        else ps2.push_back(x);
    }

    sort(begin(usb), end(usb));
    sort(begin(ps2), end(ps2));

    int i = 0;
    int cost = 0;
    while (i < size(usb) && i < a) {
        cost += usb[i++];
    }

    int j = 0;
    while (j < size(ps2) && j < b) {
        cost += ps2[j++];
    }

    while (c > 0 && i < size(usb) && j < size(ps2)) {
        if (usb[i] < ps2[j]) {
            cost += usb[i++];
        } else {
            cost += ps2[j++];
        }
        --c;
    }

    while (c > 0 && i < size(usb)) cost += usb[i++], c--;
    while (c > 0 && j < size(ps2)) cost += ps2[j++], c--;

    cout << i + j << " " << cost << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
