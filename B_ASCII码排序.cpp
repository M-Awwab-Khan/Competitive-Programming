#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        vector<char> a;
        for (char c : s) {
            a.push_back(c);
        }

        sort(a.begin(), a.end());

        for (int i = 0; i < a.size(); i++) {
            cout << a[i]; 
            if (i != a.size() - 1)
                cout << " ";
        }
        cout << '\n';
    }
    return 0;
}
