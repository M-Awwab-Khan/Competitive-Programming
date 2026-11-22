#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

void solve() {
    int n, l, w;
    while (cin >> n >> l >> w) {
        vector<pair<long double, long double>> intervals;
        int L, R;
        const long double halfWidth = w / 2.0L;

        for (int k = 0; k < n; ++k) {
            cin >> L >> R;
            const long double radicand = 1.0L * R * R - halfWidth * halfWidth;
            if (radicand < 0) continue;

            const long double dx = sqrt(radicand);
            intervals.push_back({L - dx, L + dx});
        }

        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });

        long double covered = 0.0L;
        size_t i = 0;
        bool possible = true;
        int ans = 0;

        while (covered < l) {
            long double max_r = covered;
            while (i < intervals.size() && intervals[i].first <= covered) {
                max_r = max(max_r, intervals[i].second);
                ++i;
            }

            if (max_r <= covered) {
                possible = false;
                break;
            }

            covered = max_r;
            ++ans;
        }

        cout << (possible ? ans : -1) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
