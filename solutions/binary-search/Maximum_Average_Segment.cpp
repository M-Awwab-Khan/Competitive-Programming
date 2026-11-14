#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    auto can = [&](long double average) {
        vector<long double> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + a[i - 1] - average;
        }

        int minPrefix = 0;
        for (int end = k; end <= n; ++end) {
            int candidate = end - k;
            if (prefix[candidate] < prefix[minPrefix]) {
                minPrefix = candidate;
            }
            if (prefix[end] >= prefix[minPrefix]) return true;
        }
        return false;
    };

    long double lo = *min_element(a.begin(), a.end());
    long double hi = *max_element(a.begin(), a.end());
    for (int iteration = 0; iteration < 100; ++iteration) {
        long double mid = lo + (hi - lo) / 2;
        if (can(mid)) lo = mid;
        else hi = mid;
    }

    vector<long double> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + a[i - 1] - lo;
    }

    int minPrefix = 0;
    for (int end = k; end <= n; ++end) {
        int candidate = end - k;
        if (prefix[candidate] < prefix[minPrefix]) {
            minPrefix = candidate;
        }
        if (prefix[end] >= prefix[minPrefix]) {
            cout << minPrefix + 1 << " " << end << '\n';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
