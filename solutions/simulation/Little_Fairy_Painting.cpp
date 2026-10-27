#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    set<int> s;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        s.insert(x);
    }

    while (1) {
        x = size(s);
        if (s.count(x)) {
            cout << x << endl;
            break;
        }
        s.insert(x);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
