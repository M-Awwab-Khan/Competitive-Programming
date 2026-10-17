#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// Definition of the ordered_set
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n;++i) cin >> a[i];
    sort(a.begin(), a.end());

    vector<long long> pref(n + 1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + a[i-1];

    int q; cin >> q;
    while(q--) {
        long long x; cin >> x;
        auto it = upper_bound(pref.begin(), pref.end(), x) - pref.begin();

        cout << it - 1<< "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while(t--) 
    solve();
    return 0;
}