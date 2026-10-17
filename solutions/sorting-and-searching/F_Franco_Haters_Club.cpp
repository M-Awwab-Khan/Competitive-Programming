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
    string s; cin >> s;
    string order= "7AB5CDE6FGHI3JKL1MNO9PQR2ST0UV4WXYZ8";
    int i = 0;
    map<char, int> mp;
    for (char c: order) {
        mp[c] = i;
        ++i;
    }

    sort(s.begin(), s.end(), [&](char &a, char &b) {
        return mp[a] < mp[b];
    });
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while(t--) 
    solve();
    return 0;
}