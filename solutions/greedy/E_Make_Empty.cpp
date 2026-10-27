#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a.begin(), a.end());

    int ans = 0;
    vector<int> marked(n);

    int i = 0;
    while(i < n-1) {
        // try pairing i with i+1
        if (a[i+1] - a[i] <= 2) {
            marked[i + 1] = 1;
            marked[i] = 1;
            ++ans;
            i += 2;
        }  else {
            ++i;
        }
    }

    for (auto i: marked) ans += (i == 0);
    cout << ans << "\n";
}