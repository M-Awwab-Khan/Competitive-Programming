#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    int MAXN = 3000;

    vector<int> spf(MAXN + 1);
    [&]() {
        for (int i = 0; i <= MAXN; ++i) spf[i] = i;

        for (int i = 2; i * i <= MAXN; ++i) {
            if (spf[i] == i) {
                for (int j = i * i; j <= MAXN; j += i) {
                    if (spf[j] == j) spf[j] = i;
                }
            }
        }
    }();


    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        unordered_set<int> s;
        int temp = i;
        while (temp > 1) {
            s.insert(spf[temp]);
            temp /= spf[temp];
        }

        ans += s.size() == 2;
    }
    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}