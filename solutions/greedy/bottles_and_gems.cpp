#include "bits/stdc++.h"
using namespace std;
#define ll long long

void solve() {
   int n;
   while (cin >> n) {
       if (n == 0) break;
    vector<pair<ll, ll>> cg(n);
    for (int i = 0; i < n; ++i) cin >> cg[i].first >> cg[i].second;

    sort(cg.begin(), cg.end());

    ll gems = 0;
    ll coins = 0;
    // forward pass;
    for (int i = 0; i < n; ++i) {
        if (cg[i].second > 0) {
            if (gems == 0) {
                coins += cg[i].first;
                gems += cg[i].second;
            }
            else {
                gems += cg[i].second - 1;
            }
        }
    }

    // backward pass
    for (int i = n-1; i >= 0; --i) {
        if (cg[i].second == 0) {
            if (gems > 0) {
                --gems;
            } else {
                coins += cg[i].first;
            }
        }
    }
    cout << coins << endl;
   }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
