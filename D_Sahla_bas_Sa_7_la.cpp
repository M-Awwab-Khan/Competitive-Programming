#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// Definition of the ordered_set
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

void solve() {
    int A, B; cin >> A >> B;

    long long ans = 0;
    for (long long k = 1; k <= 10; ++k) {
        if (B + 1 >= pow(10, k)) ans += A;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--) 
    solve();
    return 0;
}