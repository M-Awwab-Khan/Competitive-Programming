#include "bits/stdc++.h"
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    string s, t; cin >> s >> t;

    if (n % 2 == 0) {
        if (s == t) cout << "Deletion succeeded" << "\n";
        else cout << "Deletion failed\n";
    } else {
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == t[i]) {
                cout << "Deletion failed" << "\n"; return 0;
            }
        }
        cout << "Deletion succeeded\n";
    }
}