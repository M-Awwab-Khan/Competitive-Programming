#include <iostream>
#include <string>
#include <vector>
using namespace std;

int prefix_len(const string &a, const string &b, int l2) {
    int i = 0;
    while (i < l2 && a[i] == b[i]) {
        i++;
    }
    return i;
}

int suffix_len(const string &a, const string &b, int l1) {
    int count = 0;
    int i = l1 - 1;
    while (i > 0 && a[i] == b[i - 1]) {
        count++;
        i--;
    }
    return count;
}

void solve() {
    string a, b;
    cin >> a >> b;

    int l1 = a.length();
    int l2 = b.length();

    int pl = prefix_len(a, b, l2);
    int sl = suffix_len(a, b, l1);

    int total = (pl + 1) - (l1 - sl) + 1;
    total = max(total, 0);

    cout << total << endl;

    for (int i = 0; i < total; i++) {
        cout << (i + l1 - sl) << " ";
    }
}

int main() {
    solve();
    return 0;
}
