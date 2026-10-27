#include "bits/stdc++.h"
using namespace std;
#define ll long long

const ll MOD = 998244353;

int main() {
    int n, m; cin >> n >> m;
    vector<ll> P(n + 1); for (int i = 0; i < n + 1; ++i) cin >> P[i];
    vector<ll> Q(m + 1); for (int i = 0; i < m + 1; ++i) cin >> Q[i];

    vector<ll> R(1);
    R[0] = P[n];

    for (int i = n - 1; i >= 0; --i) {
        vector<ll> nR(Q.size() + R.size() - 1, 0);

        for (int j = 0; j < Q.size(); ++j) {
            for (int k = 0; k < R.size(); ++k) {
                nR[j + k] = (nR[j + k] + Q[j] * R[k]) % MOD;
            }
        }

        nR[0] = (nR[0] + P[i]) % MOD;
        R = move(nR);
    }

    for (int i = 0; i <= n * m; ++i) {
        cout << R[i] << " ";
    }
    cout << endl;
}
