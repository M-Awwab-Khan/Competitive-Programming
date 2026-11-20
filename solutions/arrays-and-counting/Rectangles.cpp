#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;
#define int ll

const int INF = INT_MAX;
struct Rect {
    int x1, x2, y1, y2;

    Rect (int a, int b, int c, int d) {
        x1 = a; x2 = b; y1 = c; y2 = d;
    }
    Rect () {
        x1 = INF; x2 = INF; y1 = INF; y2 = INF;
    }


    Rect intersect(const Rect& b) const {
        int nx1 = max(x1, b.x1);
        int nx2 = min(x2, b.x2);
        int ny1 = max(y1, b.y1);
        int ny2 = min(y2, b.y2);

        if (nx1 <= nx2 && ny1 <= ny2) {
            return Rect(nx1, nx2, ny1, ny2);
        }
        return Rect();
    }

};

void solve() {
    int n; cin >> n;
    vector<Rect> a(n); for (auto &r: a) cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;

    vector<Rect> prefix(n + 1);

    prefix[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = prefix[i-1].intersect(a[i]);
    }

    vector<Rect> suffix(n + 1);

    suffix[n-1] = a[n-1];
    for (int i = n-2; i > 0; --i) {
        suffix[i] = suffix[i + 1].intersect(a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            if (suffix[i + 1].x1 != INF) {
                cout << suffix[i + 1].x1 << " " << suffix[i + 1].y1 << endl;
                return;
            }
        } else if (i == n-1) {
            if (prefix[n-2].x1 != INF) {
                cout << prefix[n-2].x1 << " " << prefix[n-2].y1 << endl; return;
            }
        } else {
            Rect temp = prefix[i-1].intersect(suffix[i+1]);
            if (temp.x1 != INF) {
                cout << temp.x1 << " " << temp.y1 << endl; return;
            }
        }
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
