#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isSquare(long long x) {
    if (x < 0) return false;
    long long s = sqrt(x);
    return s * s == x;
}

void solve() {
    int n;
    cin >> n;

    long long total_sum = (long long)n * (n + 1) / 2;

    if (isSquare(total_sum)) {
        cout << -1 << endl;
        return;
    }

    if (n == 1) {
        cout << -1 << endl;
        return;
    }

    vector<int> perm;
    perm.push_back(2);
    perm.push_back(1);

    long long current_sum = 3;
    int i = 3;

    while (i <= n) {
        long long s = current_sum + i;
        if (isSquare(s)) {
            if (i + 1 > n) {
                cout << -1 << endl;
                return;
            }
            perm.push_back(i + 1);
            perm.push_back(i);
            current_sum += (i + 1) + i;
            i += 2;
        } else {
            perm.push_back(i);
            current_sum += i;
            i += 1;
        }
    }

    for (int num : perm) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
