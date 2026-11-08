#include "bits/stdc++.h"
using namespace std;

/* -------------------- Macros -------------------- */

#define fastio() ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#define ll long long
#define ull unsigned long long
#define ld long double

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define sz(x) ((int)(x).size())

#define yes cout << "YES\n"
#define no cout << "NO\n"

#define endl '\n'

/* -------------------- Constants -------------------- */

const ll INF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

/* -------------------- Solve -------------------- */

void solve(){
    int n; cin >> n;
    ll k, x; cin >> k >> x;
    vector<ll> a(n); for (auto &v: a) cin >> v;

    sort(all(a));
    // debug(a);

vector<ll> costs;
    for (int i = 0; i < n-1; ++i) {
    	if (a[i+1] - a[i] > x) {
    		ll delta = (a[i + 1] - a[i] - 1) / x;
            costs.pb(delta);
    	}
    }

    sort(all(costs));

    int groups = costs.size() + 1;
    for (auto c: costs) {
        if (k >= c) {
            k -= c; --groups;
        }  else {
            break;
        }
    }
    cout << groups << endl;
}

/* -------------------- Main -------------------- */

int main(){

    fastio();

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("myoutput.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    auto start = chrono::high_resolution_clock::now();

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }

#ifndef ONLINE_JUDGE
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cerr << "Time: " << duration.count() << " ms" << endl;
#endif

    return 0;
}