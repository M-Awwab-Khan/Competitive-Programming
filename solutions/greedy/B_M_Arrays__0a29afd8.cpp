#include "bits/stdc++.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

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
#define endl "\n"
#define yes cout << "YES\n"
#define no cout << "NO\n"

// ---------------- CONSTANTS ----------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;


// ---------------- SOLVE ----------------
void solve(){
    ll n, m; cin >> n >> m;
    ll x;
    multiset<ll> a; for (int i = 0; i < n; ++i) {
    	cin >> x;
    	a.insert(x % m);	
    }

    int ans = 0;
	x = *a.begin();
    while (!a.empty()) {
        a.erase(a.find(x));

    	ll y = ((m - (x % m)) + m) % m;
    	if (a.count(y)) {
    		x = y;

    	} else {
    		++ans;
            if (!a.empty())
                x = *a.begin();
    	}
    }
    cout << ans << endl;
}

// ---------------- MAIN ----------------
int main(){
    fastio();

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("myoutput.txt","w",stdout);
    freopen("error.txt","w",stderr);
#endif
    auto start = high_resolution_clock::now();

    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }

    auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	cerr << "Time: " << duration.count() << " ms" << endl;

    return 0;
}