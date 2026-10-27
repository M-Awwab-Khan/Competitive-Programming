#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i< n; ++i) cin >> a[i];

    int ans = 1;
    int curr = 1;
    for (int i = 1; i< n; ++i) {
        if (a[i] >= a[i-1]) ++curr;
        else curr = 1;
        ans = max(ans, curr);
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
