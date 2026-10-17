#include "bits/stdc++.h"
using namespace std;
#define ll long long

void solve() {
    ll a, b, n; cin >> a >> b>>n;

    if (n == 1 || a == b) {
        cout << 1 << "\n";
    } else {
        if (a/n < b) cout << 2 << "\n";
        else cout << 1 << "\n";
    }


}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();


    return 0;
}