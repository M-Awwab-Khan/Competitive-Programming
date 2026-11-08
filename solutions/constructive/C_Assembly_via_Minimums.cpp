#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n*(n-1)/2); for (int i = 0; i < (n*(n-1)/2); ++i) cin >> a[i];

    map<int, int> freq;
    for (int i = 0; i < n*(n-1)/2; ++i) freq[a[i]]++;

    vector<int> ans(n);

    int j = 0; // current position to write on.
    for (auto &[k, v]: freq) {
        int x = v;
        while (x != 0) {
            int gainE = n - j - 1;
            if (x >= gainE) {
                x -= gainE;
                ans[j] = k; 
                ++j;
            }
        }
    }
    ans[n-1] = freq.rbegin()->first;

    for (auto x: ans) cout << x << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}