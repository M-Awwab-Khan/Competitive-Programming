#include "bits/stdc++.h"
using namespace std;

#define ll long long

const int MAX = 1e6 + 1;
vector<int> phi(MAX + 1);
void phi_1_to_n() {
    for (int i = 0; i <= MAX; i++)
        phi[i] = i;

    for (int i = 2; i <= MAX; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= MAX; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}


void solve() {
    // number of coprime pairs from 1 to n
    int n ;cin >> n;
    int ans = 0;
    for (int i = 2; i < n+1; ++i) {
        ans += phi[i] - 1;
    }
    ans = 2*(ans);
    cout << ans << endl;
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    phi_1_to_n();

    int t; cin >> t; while (t--) solve();
    // solve();

    return 0;
}