#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #include "debugging.cpp"

using namespace __gnu_pbds;

// Definition of the ordered_set
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

void solve() {
    int n; cin >> n; 
    string s; cin >> s;

    vector<long long> pref(n + 2, 0);
    vector<long long> suff(n + 2, 0);
    vector<long long> prefcost(n + 2, 0);
    vector<long long> suffcost(n + 2, 0);

    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + (s[i-1] == '1');
        prefcost[i] = prefcost[i-1] + pref[i-1];
    }

    for (int i = n; i >= 1; --i) {
        suff[i] = suff[i + 1] + (s[i-1] == '1');
        suffcost[i] = suffcost[i + 1] + suff[i + 1];
    }

    // debug(pref, suff);

    vector<long long> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        ans[i] = prefcost[i] + suffcost[i];
    }

    for (int i = 1; i <= n; ++i) cout << ans[i] << " ";
    cout << "\n";


}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while(t--) 
    solve();
    return 0;
}