#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

using ll = long long;

void solve() {

    int n; cin >> n;
    set<int> res;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        res.insert(i);
        sum += i;
        if (sum > n) break;
    }

    if (sum == n) {
        cout << res.size() << endl;
        for (auto a: res) cout << a << " ";
        cout << "\n";
    } else {
        // debug(res, sum);
        res.erase(res.find(sum - n));
        cout << res.size() << endl;
        for (auto a: res) cout << a << " ";
        cout << "\n";
    }



}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while(t--) 
    solve();

    return 0;
}