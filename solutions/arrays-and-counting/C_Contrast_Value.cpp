#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> b(n); for (int i = 0; i < n ; ++i) cin >> b[i];

    vector<int> a;
    a.push_back(b[0]);
    for (int i = 1; i < n; ++i) {
        if (b[i] == a.back()) continue;
        a.push_back(b[i]);
    }

    if (a.size() == 1) {
        cout << 1 << "\n";
        return;
    }

    if (n <= 2) {
        cout << (n) << "\n"; return;
    }

    // long long k= 0;
    // for (int i = 1; i < n; ++i) k += a[i] - a[i-1];

    // debug(a);


    int ans = 0;

    int peaks = 0, valleys = 0;
    for (int i = 1; i < a.size() - 1; ++i) {
        if ((a[i] > a[i-1]) && (a[i] > a[i+1])) ++peaks;
        else if ((a[i] < a[i-1]) && (a[i] < a[i+1])) ++valleys;
    }
    ans = peaks + valleys + 2;
    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}