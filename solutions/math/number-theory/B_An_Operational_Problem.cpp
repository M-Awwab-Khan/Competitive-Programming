#include "bits/stdc++.h"
using namespace std;

bool isPowerOfTwo(int n) {
    // Check if n is positive and the bitwise AND is zero
    return (n > 0) && ((n & (n - 1)) == 0);
}

void solve() {
    int n; cin >> n;
    int odd = 0;
    map<int, int> freq;
    vector<int> a(n); for (int i = 0; i < n; ++i) {
        cin >> a[i];
        odd += (a[i] % 2);
        freq[a[i]]++;
    }



    if (odd % 2) {
        cout << 0 << "\n"; return;
    } else if (odd > 0) {
        cout << 1 << "\n"; return;
    } else {
        int gans = INT_MAX;
        for (auto [k, v]: freq)  {
            int e, f;
            e = k; f = v;
            int ans = 0;
            while (e % 2 == 0) {
                e /= 2;
                ++ans;
            }
            if (f % 2 == 0) ++ans;
            gans = min(ans, gans);
        }

        cout << gans << "\n";
    }

}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) solve();

    return 0;
}