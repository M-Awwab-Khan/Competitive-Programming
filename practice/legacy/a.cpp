#include "bits/stdc++.h"
#include "debugging.cpp"
using namespace std;
#define ll long long

#define MAX 200004

ll fact[MAX + 1];
ll invfact[MAX + 1];

#define MOD 1000000007

ll modPow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

void precomputefactorials() {
    fact[0] = 1;
    for (ll i = 1; i <= MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invfact[MAX] = modPow(fact[MAX], MOD - 2, MOD);
    for (ll i = MAX - 1; i >= 0; i--) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
}


void solve() {
 int n; cin >> n;
 vector<pair<int, int>> a(n);
 map<pair<int, int>, int> freq;

 for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
    freq[a[i]]++;
 }
 vector<pair<int, int>> unq;
for (auto it = freq.begin(); it != freq.end(); ++it) {
        unq.push_back(it->first);
    }

    debug(unq);
    debug(freq);

 long long ans = 0;

 for (int i = 0; i < (int)unq.size(); ++i) {
     // same group
     if (freq[unq[i]] >= 2) {
         ll num = 2* (unq[i].first + unq[i].second);
         ll den1 = unq[i].first * 2;
         ll den2 = unq[i].second * 2;
         

         debug(num, den1, den2);
         ll intermediate = 0;
         ll term = fact[num] * invfact[den1] % MOD * invfact[den2] % MOD;
         intermediate = (freq[unq[i]] * term) % MOD;
         ans = (ans + intermediate) % MOD;
     }
    for (int j = i+1; j < (int)unq.size(); ++j) {



        // different groups
        ll num = unq[i].first + unq[i].second + unq[j].first + unq[j].second;
        ll den1 = unq[i].first + unq[j].first;
        ll den2 = unq[i].second + unq[j].second;

        ll term = fact[num] * invfact[den1] % MOD * invfact[den2] % MOD;
        term = (term * freq[unq[j]]) % MOD;
        ans = (ans + term) % MOD;

    }

 }
 
 cout << ans  % MOD<< endl;


}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    precomputefactorials();

    // int t; cin >> t; while(t--) 
    solve();

    return 0;
}