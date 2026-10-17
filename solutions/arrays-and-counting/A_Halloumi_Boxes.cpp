#include "bits/stdc++.h"
using namespace std;

void solve() {

    int N, K; cin >>N >> K;

    vector<int> a(N); for (int i = 0; i < N; ++i) cin >> a[i];

    if (is_sorted(a.begin(), a.end()) || K > 1) {
        cout << "YES\n"; 
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) 
    solve();

    return 0;
}