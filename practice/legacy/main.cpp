#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n; cin >> n;
    int msb = 0;

    int x = n;
    while (x != 0) {
        x /= 2;
        msb++;
    }
    long long y = (1 << msb) - 1;

    long long ans = (n * (n + 1) / 2) - (2 * y);
    cout << ans << endl;
}

int main() {

    int t; cin >> t; while(t--)
    solve();
}