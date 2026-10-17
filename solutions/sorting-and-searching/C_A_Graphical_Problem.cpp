#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;


using ll = long long;

void solve() {
    int n; cin >> n;
    vector<long long> h(n); for (int i = 0; i < n; ++i) cin >> h[i];
    sort(h.begin(), h.end());

long long mn = h[n-1] - h[0];

long long mx = h[n-1] - h[0];
for (int i = 1; i < n-1; ++i) {
    mx += max((h[i] - h[0]), (h[n-1] - h[i]));
}

cout << mn << " " << mx << "\n";

}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) solve();

    return 0;
}