#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> csum(n); for (int i = 0; i < n; ++i) cin >> csum[i];
    vector<int> rsum(n); for (int i = 0; i < n; ++i) cin >> rsum[i];
    vector<int> grid;

    function<bool(int)> backtrack = [&](int r) {
        if (r == n) {
            return true;
        }

        for (int mask = 0; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) != rsum[r]) continue;

            // Reduce column sums by 1 or 0
            for (int i = 0; i < n; ++i) {
                csum[i] -= ((mask >> i) & 1);
            }

            int remaining = n - r - 1;
            bool valid = true;
            for (int i = 0; i < n; ++i) {
                if (csum[i] < 0 || csum[i] > remaining) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                grid.push_back(mask);
                if (backtrack(r + 1)) return true;
                grid.pop_back();
            }

            // Undo column updates
            for (int i = 0; i < n; ++i) {
                csum[i] += ((mask >> i) & 1);
            }
        }
        return false;
    };

    if (backtrack(0)) {
        // Do NOT reverse grid, row 0 was pushed first
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << ((grid[i] >> j) & 1);
            }
            cout << "\n";
        }
    } else {
        cout << "No valid grid found\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
