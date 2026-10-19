#include "bits/stdc++.h"
using namespace std;

using ll = long long;

void solve() {
    string s; cin >> s;
    int n = s.size();
    // 1. delete all vowels
    set<char> vowels = {'A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'};

    for (auto chr: vowels) {
        erase(s, chr);
    }

    // put . before every consonant.
    int i = 0;
    while (i < s.size()) {
        if (vowels.count(s[i]) == 0) {
            s.insert(i, 1, '.');
            ++i;
        }
        ++i;
    }

    // uppercase to lowercase
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
    }

    cout << s << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
