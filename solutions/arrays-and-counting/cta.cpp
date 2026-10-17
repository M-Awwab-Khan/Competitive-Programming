#include "bits/stdc++.h"
#include "debugging.cpp"
using namespace std;
#define ll long long

void solve() {
    int n, q; cin >> n>> q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    while (q--) {
        int i, j; cin >> i >> j;
        i--; j--;

        unordered_map<int, int> freq;
        for (int k = i; k <= j; ++k) {
            freq[arr[k]]++;
        }
        int mode = arr[i];
        int maxFreq = 1;
        int secondFreq = 0;
        for (auto& [k, v] : freq) {
            if (v >= maxFreq) {
                secondFreq = maxFreq;
                mode = k;
                maxFreq = v;
            } else if (v == maxFreq) {
                secondFreq = v;
            } else if (v > secondFreq) {
                secondFreq = v;
            }
        }
        
        
        debug(maxFreq, secondFreq);
        if (secondFreq == 0) {
            cout << mode << "\n";
        } else if (secondFreq == maxFreq) {
            cout << 0 << "\n";
        } else {
            cout << mode << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);


    // int t; cin >> t; while(t--) 
    solve();

    return 0;
}