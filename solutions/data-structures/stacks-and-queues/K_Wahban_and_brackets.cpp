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
    string s; cin >> s;
    int ans = 0;
    stack<char> stack;
    for (char c: s) {
        if (!stack.empty() && c == '(' && stack.top() == ')') {
            stack.pop();
            ++ans;
            continue;
        }
        stack.push(c);
        // debug(stack);
    }


    if (ans == 0) ans = -1;
    else ans *= 2;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while(t--) 
    solve();
    return 0;
}