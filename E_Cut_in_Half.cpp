#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll countPieces(const vector<ll>& A, ll L, ll K) {
    ll count = 0;
    for (ll a : A) {
        count += min(a / L, K + 1); 
        if (count > 1e15) break; // prevent overflow
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        ll K, X;
        cin >> N >> K >> X;
        vector<ll> A(N);
        ll maxA = 0;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            maxA = max(maxA, A[i]);
        }

        ll lo = 1, hi = maxA, ans = 1;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            if (countPieces(A, mid, K) >= X) {
                ans = mid;
                lo = mid + 1;  // try larger L
            } else {
                hi = mid - 1;  // too big
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
