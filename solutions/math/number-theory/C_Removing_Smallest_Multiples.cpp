#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;


    int cost[n+1]{};

    int a[n+1] {};
    for(int i = 0; i < n; ++i) {
        a[i + 1] = s[i] == '1';
    }

    for (int i = n; i >= 1; --i) {
        for (int j = i; j <= n; j += i) {
            if (a[j]) break;
            cost[j] = i;
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += cost[i];
    }
    cout << ans << "\n";

}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) solve();

    return 0;
}