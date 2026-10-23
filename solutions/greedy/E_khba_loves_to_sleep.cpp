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
 
#define endl '\n'
 
/* -------------------- Constants -------------------- */
 
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;
 
/* -------------------- Debug -------------------- */
 
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x << endl;
#else
#define debug(x)
#endif
 
/* -------------------- Solve -------------------- */
 
void solve(){
    int n, k; cin >> n >> k;
    ll x; cin >> x;

    vector<ll> a(n + 2); for (int i = 1; i < n+1;++i) cin >> a[i];


    a[n+1] = x;

    sort(all(a));

    vector<pair<ll, ll>> b; for (int i = 0; i < n + 1; ++i) {
        pair<ll, ll> y;
        y.ff = (a[i+1] - a[i]);
        y.ss = ((a[i+1] + a[i]) / 2);

        b.pb(y);
    }
    // first -> distance
    // second -> center point

    sort(rall(b));

    for (int i = 0; i < k; ++i) {
        cout << b[i].ss << " ";
    }
    cout << endl;



}
 
/* -------------------- Main -------------------- */
 
int main(){
 
    fastio();
 
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
 
    auto start = chrono::high_resolution_clock::now();
 
    int t = 1;
    cin >> t;
 
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