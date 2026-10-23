
#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;

    int turn = 1;
    while (true) {
        n -= (n+1)/2;
        turn ^= 1;
    }
}

int main() {
    int t; cin >> t; while(t--)
    solve();
}
