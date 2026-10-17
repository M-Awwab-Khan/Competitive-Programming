#include "bits/stdc++.h"
// #include "debugging.cpp"
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
    vector<int> a(n + 1); for (int i = 1; i <= n; ++i) cin >>a[i];

    int ans = 0;


    for (int i = 1; i <= n; ++i) {
    	for (ll s = a[i]; s <= 2*n; s += a[i]) {
    		ll j = s - i;
    		if (j <= n && j > i && (i + j == 1LL*a[i]*a[j])) ++ans;
    	}
    }
    cout << ans << endl;

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