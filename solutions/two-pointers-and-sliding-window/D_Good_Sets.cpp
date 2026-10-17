#include "bits/stdc++.h"
using namespace std;

using ll = long long;
const ll MOD = 998244353;
const int MAXN = 200005;

ll pow2[MAXN];

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n); for (int i= 0;i < n; ++i) cin >> a[i]; 

    deque<int> mx;
    deque<int> mn;

    int l = 0;
    ll subarrays = 0;
    for (int r = 0; r < n; ++r) {
        while (!mx.empty() && a[mx.back()] <= a[r]) mx.pop_back();
        mx.push_back(r);

        while (!mn.empty() && a[mn.back()] >= a[r]) mn.pop_back();
        mn.push_back(r);

        while (a[mx.front()] - a[mn.front()] > k) {
            if (mx.front() == l) mx.pop_front();
            if (mn.front() == l) mn.pop_front();
            l++;
        }

        subarrays += (r - l + 1);
    }
     subarrays %= MOD;

    sort(a.begin(), a.end());

        ll subseq = 0;
        l = 0;

        for (int r = 0; r < n; r++) {

            while (a[r] - a[l] > k) l++;

            subseq = (subseq + pow2[r-l]) % MOD;
        }

        cout << subarrays << " " << subseq << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        pow2[i] = (pow2[i-1] * 2) % MOD;
    int t; cin >> t; while(t--)
    solve();

    return 0;
}