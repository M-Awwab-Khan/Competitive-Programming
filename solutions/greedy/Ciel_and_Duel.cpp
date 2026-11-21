#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int ll

void solve() {
    int n, m; cin >> n >> m;
    vector<int> def;
    vector<int> atk;

    string type; int x;
    for (int i = 0; i < n;++i) {
        cin >> type >> x;
        if (type == "ATK") atk.push_back(x);
        else def.push_back(x);
    }

    sort(begin(def), end(def));
    sort(begin(atk), end(atk));

    multiset<int> a; for (int i = 0; i < m; ++i) {
        cin >> x; a.insert(x);
    }
    multiset<int> b(a);

    debug(a);
    // take down all of his defense cards
    int ans = 0;
    int down = 0;
    for (auto x: def) {
        auto it = a.upper_bound(x);
        if (it == a.end()) {
            break;
        } else {
            a.erase(it);
            ++down;
        }
    }
    debug(a);
    debug(down);


    int i = 0;
    while (!a.empty()) {
        debug("enered");
        auto it = prev(a.end());
        debug(*it);

        if (i < size(atk) && *it >= atk[i]) {
            ans += *it - atk[i];
            i++;
            a.erase(it);
        } else {
            break;
        }
    }

    debug(i);
    if (i == atk.size() && down == def.size()) {
        while (!a.empty()) {
            ans += *a.begin();
            a.erase(a.begin());
        }
    }

    // kill attack cards first
    int ans2 = 0;

    i = 0;
    while (i < size(atk)) {
        if (b.empty()) break;
        auto it = prev(end(b));
        if (*it >= atk[i]) {
            ans2 += (*it - atk[i]);
            i++;
            b.erase(it);
        } else break;
    }
    if ( i != atk.size()) {
        goto anss;
    }

    i = 0;
    while (i < size(def)) {
        if (b.empty()) break;
        auto it = b.upper_bound(def[i]);
        if (it != b.end()) {
            b.erase(it);
            ++i;
        } else {
            break;
        }
    }

    while (i == def.size() && !b.empty()) {
        auto it = b.begin();
        ans2 += *it;
        b.erase(it);
    }
    anss:;
    cout << max(ans, ans2) << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
