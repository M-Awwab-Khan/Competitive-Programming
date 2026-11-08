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

    long long n, k; cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
        a[i] = ((a[i] % k) + k) % k;
    }

    sort(a.rbegin(), a.rend());

    long long aa = 0, b =0;
    for (int i = 0; i < n; ++i) {
        aa += (i % 2 == 0) * (a[i]);
        b += (i % 2 == 1) * (a[i]);
    }
    string ans = (aa > b ) ? "YES" : "NO";

    cout << ans << "\n";
}