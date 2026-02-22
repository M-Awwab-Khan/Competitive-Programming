#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// Definition of the ordered_set
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<string> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    sort(v.begin(), v.end(), [](const string &a, const string &b) {
        return a + b < b + a;
    });

    string result = "";
    for (const string &s : v) {
        result += s;
    }
    cout << result << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while(t--) 
    solve();
    return 0;
}