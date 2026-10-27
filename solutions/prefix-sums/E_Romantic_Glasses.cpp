#include "bits/stdc++.h"
using namespace std;

#ifndef ONLINE_JUDGE
#include "debugging.cpp"
#else
#define debug(...) ((void)0)
#endif

// ---------------- FAST IO ----------------
#define fastio() ios::sync_with_stdio(false); cin.tie(NULL)

// ---------------- TYPES ----------------
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;

// ---------------- MACROS ----------------
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// ---------------- CONSTANTS ----------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

// ---------------- UTILITIES ----------------
ll gcdll(ll a, ll b){ return b ? gcdll(b, a % b) : a; }

ll lcmll(ll a, ll b){ return (a / gcdll(a,b)) * b; }

ll mod_pow(ll a, ll b, ll m = MOD){
    ll res = 1;
    a %= m;
    while(b){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// ---------------- SOLVE ----------------
void solve(){
	int n; cin >> n;
    vector<int> a(n); for (auto &x: a) cin >> x;

    vector<int> b(n); for (int i = 0; i < n; ++i) {
    	if (i % 2) b[i] = -a[i];
    	else b[i] = a[i];
    }

    ll pref = 0;
    map<ll, int> mp;
    mp[0] = 1;
    for (auto x: b) {
    	pref += x;

    	if (mp[pref]) {
    		cout << "YES\n"; return;
    	}
    	mp[pref]++;
    }
    cout << "NO\n";
}

// ---------------- MAIN ----------------
int main(){
    fastio();

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("myoutput.txt","w",stdout);
    freopen("error.txt","w",stderr);
#endif

    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}