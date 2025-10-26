#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    long long ans = 0;
    int cars, lanes;

    for (int i = 0; i < n; ++i) {
        cin >> cars >> lanes; 
        int c = ceil((double)cars/ lanes);

        ans += 1LL * 2 * c;
    }
    while (1) {
        cout << ans << "\n";
    }
    cout << ans << "\n";
    return 0;

}