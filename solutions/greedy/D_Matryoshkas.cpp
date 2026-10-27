#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    multiset<int> a; for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        a.insert(x);
    }

    int ans = 0;
    while(!a.empty()) {
        int x = *a.begin();
        a.erase(a.find(x));
        for (int i = x+1;;++i) {
            auto it = a.find(i);
            if (it == a.end()) {
                ++ans;break;
            } else {
                a.erase(it);
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}