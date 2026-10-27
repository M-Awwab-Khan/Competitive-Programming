
#include "bits/stdc++.h"
using namespace std;
#define ll long long



void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b(a);

    ll ans1 = 0;
    for (int i = 1; i < n; ++i) {
        if (i % 2 != 0) {
            if (b[i] >= b[i-1]) {
                ans1 += b[i] - b[i-1] + 1;
                b[i] = b[i-1] - 1;
            }

        }
        else {
            if (b[i] <= b[i-1]) {
                ans1 += b[i-1] - b[i] + 1;
                b[i-1] = b[i] - 1;
            }
        }
    }

    b = a;
    ll ans2 = 0;
    for (int i = 1; i < n; ++i) {
        if (i % 2 != 0) {
            if (b[i] <= b[i-1]) {
                ans2 += b[i-1] - b[i] + 1;
                b[i-1] = b[i] - 1;
            }
        } else {
            if (b[i] >= b[i-1]) {
                ans2 += b[i] - b[i-1] + 1;
                b[i] = b[i-1] - 1;
            }
        }
    }
    cout << min(ans1, ans2) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int t; cin >> t; while (t--)
        solve();
   return 0;
}
