#include "bits/stdc++.h"
#include "debugging.cpp"
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m; 
    if (!(cin >> n >> m)) return 0;
    vector<long long> H(n); 
    for (int i = 0; i < n; ++i) cin >> H[i];
    vector<long long> W(m); // Note: W is size M, not N
    for (int i = 0; i < m; ++i) cin >> W[i];

    sort(H.begin(), H.end());

    vector<long long> pre(n + 1, 0); 
    vector<long long> suf(n + 1, 0); 

    // Prefix pairs: (0,1), (2,3), (4,5) ...
    for (int i = 1; i < n; i += 2) {
        pre[i + 1] = pre[i - 1] + (H[i] - H[i - 1]);
    }

    // Suffix pairs: (n-1, n-2), (n-3, n-4) ...
    for (int i = n - 2; i >= 0; i -= 2) {
        suf[i] = suf[i + 2] + (H[i + 1] - H[i]);
    }

    debug(pre, suf);
    
    long long ans = 2e18;
    for (auto x : W) {
        int it = lower_bound(H.begin(), H.end(), x) - H.begin();
        
        int i = it;
        if (i % 2 == 1) i--; 
        
        long long current_cost = pre[i] + abs(x - H[i]) + suf[i + 1];
        ans = min(ans, current_cost);
    }
    
    cout << ans << "\n";
    return 0;
}