#include "bits/stdc++.h"
using namespace std;

void no() {cout << "NO" << "\n";}
void yes() {cout << "YES" << "\n";}

const int MAXA = 1000005;
int xor_divs[MAXA];
int pref[MAXA];

void solve() {
     int n, q, k;
    cin >> n >> q >> k;

    for (int i = 1; i < MAXA; ++i) {
        for (int j = i; j < MAXA; j += i) {
            xor_divs[j] ^= i;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        int is_spy = (xor_divs[a] % k == 0) ? 1 : 0;
        pref[i] = pref[i - 1] + is_spy;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l - 1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while (t--)
    solve();
    return 0;
}