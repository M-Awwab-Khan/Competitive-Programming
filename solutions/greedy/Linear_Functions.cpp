#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int ll

struct Function {
    int a, b, id;
};

void solve() {
    int n; cin >> n;
    vector<Function> k(n);
    for (int i = 0; i < n; ++i) {
        cin >> k[i].a >> k[i].b;
        k[i].id = i + 1;
    }

    auto cmp = [](const Function &a, const Function &b) {
        __int128 ab = a.a + a.b;
        ab = ab * b.a + b.b;

        __int128 ba = b.a + b.b;
        ba = ba * a.a + a.b;

        if (ab > ba) return true;
        else return false;
    };
    sort(k.begin(), k.end(), cmp);

    for (auto x: k) {
        cout << x.id << " ";
    }
    cout << endl;

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
