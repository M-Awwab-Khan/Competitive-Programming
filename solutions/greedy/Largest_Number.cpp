#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n; cin >> n;
    vector<string> a(n); for (auto &s: a) cin >> s;

    auto cmp = [](const string a, const string b) {
        string ab = a + b;
        string ba = b + a;
        if (ab > ba) return true;
        else return false;
    };

    sort(a.begin(), a.end(), cmp);

    string ans = "";
    for (auto s: a) ans += s;

    int i = 0;
    while (i < ans.size() && ans[i] == '0') ++i;
    if (i == ans.size()) cout << 0;
    else for (; i < ans.size(); ++i) cout << ans[i];
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
