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

/* -------------------- Debug -------------------- */

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x << endl;
#else
#define debug(x)
#endif

/* -------------------- Solve -------------------- */

void solve(){
   	 int n;cin >> n;
   	 vector<string> a(n);

for (int i = 0; i < n; ++i) cin >> a[i];

   	 	int ans = 0;
   	 for (int i = 0; i < n/2; ++i) {
   	 	for (int j = 0; j < n/2; ++j) {
   	 		char a1 = a[i][j];
   	 		char a2 = a[j][n-i-1];
   	 		char a3 = a[n-i-1][n-j-1];
   	 		char a4 = a[n-j-1][i];

   	 		char mx = max({a1, a2, a3, a4});

   	 		ans += (mx - a1);
   	 		ans += (mx - a2);
   	 		ans += (mx - a3);
   	 		ans += (mx - a4);
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