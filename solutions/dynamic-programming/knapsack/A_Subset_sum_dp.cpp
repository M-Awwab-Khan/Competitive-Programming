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
// #define debug(x) cerr << #x << " = " << x << endl;
#include "debugging.cpp"
#else
#define debug(x)
#endif

/* -------------------- Solve -------------------- */

void solve(){
   int n, x; 
   cin >> n >> x;

   vector<int> a(n);
   for (auto &y: a) cin >> y;

   int sumA = accumulate(a.begin(), a.end(), 0);

   vector<int> dp(sumA + 1);
   dp[0] = 1;

   for (auto y: a){
      for (int s = sumA; s >= y; s--){
         dp[s] |= dp[s-y];
      }
   }

   int S = sumA + x;
   int ans = INT_MAX;

   for (int i = 0; i <= sumA; i++){
      if (dp[i]){
         int A = x + i;
         int B = S - A;
         ans = min(ans, abs(A - B));
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