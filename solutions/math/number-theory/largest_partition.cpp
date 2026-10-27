#include "bits/stdc++.h"
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> groups;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] >= a[i-1]) ++cnt;
        else {
            groups.push_back(cnt);
            cnt = 1;
        }
    }

    groups.push_back(cnt);

    if (groups.size() == 1) {
        cout << groups[0] << endl; return 0;
    }
    int g = groups[0];
    for (int i = 1; i < groups.size() - 1; ++i) {
        g = gcd(g, groups[i]);
    }

    cout << g << endl;
}
