#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

void solve() {

    int C, n, q; cin >> C >> n >> q;

    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });


    // for each point between 0 and c, minR[i] = the minimum right endpoint of an interval that covers i
    vector<int> minR(C + 1, INT_MAX);

    int j = 0;
    for (int i = 0; i <= C; i++) {
        while (j < n && intervals[j].second < i) {
            j++;
        }
        if (j < n) {
            minR[i] = intervals[j].second;
        }
    }

    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    });
    // for each point between 0 and c, maxL[i] = the maximum left endpoint of an interval that covers i
    vector<int> maxL(C + 1, INT_MIN);
    j = n - 1;
    for (int i = C; i >= 0; i--) {
        while (j >= 0 && intervals[j].first > i) {
            j--;
        }
        if (j >= 0) {
            maxL[i] = intervals[j].first;
        }
    }


    while(q--) {
        int x, y;
        cin >> x >> y;

        if (x > y) {
            swap(x, y);
        }
        if (x == y) {
            cout << "NO\n";
            continue;
        }

        if (minR[x] < maxL[y]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }



}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}