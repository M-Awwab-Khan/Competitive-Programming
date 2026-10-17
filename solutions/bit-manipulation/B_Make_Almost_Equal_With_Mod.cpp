#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

using ll = long long;

void solve() {

    int n; cin >> n;
    ll x;
    vector<long long> a(n); for (int i= 0;i < n; ++i) {
        cin >> x;
        a[i] = x;
    }


        for (ll i = 1; i <= 58; ++i) {
            set<long long> s;
            for (int j = 0; j < n; ++j) {
                s.insert(a[j] % (1LL << i));
            }

            if (s.size() == 2) {
                cout << (1LL << i) << "\n";
                return;
            }
        }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) 
    solve();

    return 0;
}