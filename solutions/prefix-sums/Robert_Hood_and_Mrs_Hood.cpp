#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define pii pair<int, int>

void solve() {
    int n, d, k; cin >> n >> d >> k;
    vector<pii> intervals(n);
    for (int i = 0; i < k ;++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    vector<int> starts(n + 1, 0);
    vector<int> ends(n + 1, 0);


    for (auto [l, r]: intervals) {
        starts[l]++;
        ends[r]++;
    }

    for (int i = 1; i <= n; ++i) {
        starts[i] += starts[i-1];
        ends[i] += ends[i-1];
    }

    int minintervals = INT_MAX;
    int beststart = -1;

    int mxintervals = INT_MIN;
    int beststart2 = -1;

    for (int x = 1; x + d - 1 <= n; ++x) {
        int  y = x + d - 1;
        int covering = starts[y] - ends[x-1];

        if (covering < minintervals) {
            minintervals = covering;
            beststart = x;
        }

        if (covering > mxintervals) {
            mxintervals = covering;
            beststart2 = x;
        }
    }

    cout << beststart2 << " " << beststart << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
