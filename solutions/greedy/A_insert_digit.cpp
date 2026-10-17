#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, d; cin >> n >> d;
    string x; cin >> x;

    int pos = 0;
    while (pos < n && d <= x[pos] - '0') {
        ++pos;
    }

    string ans;
    ans.reserve(x.size() + 1);
    ans.append(x, 0, pos);
    ans.push_back(static_cast<char>('0' + d));
    ans.append(x, pos, string::npos);

    cout << ans << '\n';
}

int main() {

    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
