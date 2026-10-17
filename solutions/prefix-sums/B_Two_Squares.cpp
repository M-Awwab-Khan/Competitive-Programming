#include "bits/stdc++.h"
using namespace std;

const int n = 10000000;
vector<int> b(n + 1, 0);
vector<int> a(n + 1, 0);
void pre() {

    for (int i = 0; i * i <= n; ++i) {
        for (int j = i; i*i + j*j <= n; ++j) {
            int val = i*i + j*j;
            if (b[val] == 0) a[val]++;
            b[val] = 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        a[i] += a[i-1];
    }
}

void solve() {
    int x; cin >> x;
    cout << a[x] << endl;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    
    pre();
    int t; cin >> t; while(t--)
    solve();
}