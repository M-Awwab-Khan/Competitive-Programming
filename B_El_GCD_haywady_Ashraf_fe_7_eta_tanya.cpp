#include "bits/stdc++.h"
using namespace std;

void no() {cout << "NO" << "\n";}
void yes() {cout << "YES" << "\n";}

void solve() {
    long long n; cin >> n;
    auto isPrime = [&](long long n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n %3 == 0) return false;
        for (long long i = 5; i*i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    };

    if (n <= 2) no();
    else if (!isPrime(n)) yes();
    else no();

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t; while (t--)
    solve();
    return 0;
}