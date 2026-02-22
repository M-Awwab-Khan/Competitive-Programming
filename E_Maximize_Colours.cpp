#include "bits/stdc++.h"
using namespace std;

void solve() {
    int x, y, z; cin >> x >> y >> z;
    int ans = 0;
    if (x > 0) {--x; ++ans;}
    if (y > 0) {--y; ++ans;}
    if (z > 0) {--z; ++ans;}

    vector<int> nums = {x, y, z};
    sort(nums.begin(), nums.end(), greater<int>());
    x = nums[0];
    y = nums[1];
    z = nums[2];
    if (x > 0 && y > 0) {--x; --y; ++ans;}
    if (x > 0 && z > 0) {--x; --z; ++ans;}
    if (y > 0 && z > 0) {--y; --z; ++ans;}
    cout << ans << "\n";
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}