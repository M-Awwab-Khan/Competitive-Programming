#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// Definition of the ordered_set
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin>>a[i];

    ordered_set<pair<int, int>> s;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        // cout << i - s.order_of_key({a[i], i}) << " ";
        int idx = (i) - s.order_of_key({a[i], i});
        ans += idx;
        s.insert({a[i], i});
    }
    // cout << endl;
    cout << ans << "\n";
}