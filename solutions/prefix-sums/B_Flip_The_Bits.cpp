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
    string a, b; cin >> a >> b;

    vector<int> pref1(n);
    pref1[0] = a[0] == '1' ? 1 : 0;
    for (int i = 1;i  < n; ++i) {
    	pref1[i] = pref1[i-1] + (a[i] == '1');
    }
    vector<int> pref0(n);
    pref0[0] = a[0] == '0' ? 1 : 0;
    for (int i = 1;i  < n; ++i) {
    	pref0[i] = pref0[i-1] + (a[i] == '0');
    }

	int flips =0;
    for (int i = n-1; i >= 0; i--) {
    	int x = flips % 2;
    	if (x) a[i] = (a[i] == '0') ? '1' : '0';
    	if (a[i] != b[i]) {
    		if (pref1[i] != pref0[i]) {
    			no; return;
    		}
    		flips++;
    		pref1[i] = (i + 1) - pref1[i];
    		pref0[i] = (i + 1) - pref0[i];
    		a[i] = b[i];
    	}
    }
    yes;
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