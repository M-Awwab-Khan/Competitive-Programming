#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

using ll = long long;
void solve() {
	int n;
    ll x;
    cin >> n >> x;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }


    
    sort(a.begin(), a.end());
    
    ll total_packs = 0;
    ll current_prefix_sum = 0;
    
    for (int i = 0; i < n; ++i) {
        current_prefix_sum += a[i];
        
        if (current_prefix_sum > x) {
            break;
        }
        
        ll k = i + 1; 
        ll days = (x - current_prefix_sum) / k + 1;
        
        total_packs += days;
    }
    
    cout << total_packs << "\n"; 
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("myoutput.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    int t; cin >> t; while(t--)
    solve();
}
