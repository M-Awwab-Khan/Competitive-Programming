
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifndef ONLINE_JUDGE
#include "debugging.h"
#else
#define debug(x) 0
#endif

using namespace std;
using namespace __gnu_pbds;

#define ff first
#define ss second
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
#define vpll vector<pair<long long, long long>>
#define vvll vector<vector<long long>>
#define vc vector<char>
#define vs vector<string>
#define vb vector<bool>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define mll map<long long, long long>
#define umap unordered_map
#define uset unordered_set
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define fise(i, s, e) for (long long int i = s; i < e; i++)
#define fnr(i, n) for (long long int i = 0; i < n; i++)
#define fora(a) for(auto u:a)
#define cf(i, s, e) for (long long int i = s; i <= e; i++)
#define rcf(i, e, s) for (long long int i = e; i >= s; i--)
#define fies(i, e, s) for (long long int i = e; i > s; i--)
#define len(s) (ll)s.size()
#define pb push_back
#define eb emplace_back
#define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed,ios::floatfield);

#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))
#define clearBit(S, j) (S &= ~(1<<j))
#define toggleBit(S, j) (S ^= (1<<j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1<<n)-1)
#define modulo(S, N) ((S) & (N-1))
#define isPowerOfTwo(S) (!(S & (S-1)))
#define nearestPowerOfTwoLess(S) (1<<(int)log2(S))
#define nearestPowerOfTwoMore(S) (1<<((int)log2(S) + 1))
#define turnOffLastBit(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveBits(S) ((S) & (S+1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S-1))

/* PRINTS */
template <class T> void print_v(vector<T> &v) { for (auto x : v) cout << x << " "; cout << "\n"; }
template<char sep=' ', char end='\n', class T, class... U>
void print( const T& first, const U&... rest)
{
    std::cout << first;
    ((std::cout << sep << rest ), ...);
    std::cout << end;
}
void print() {cout << '\n';}
void printInt128(__int128 x) { if (x == 0) { cout << "0"; return; } string res = ""; while (x) { res += (char)('0' + (x % 10)); x /= 10; } reverse(res.begin(), res.end()); cout << res; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()

ll gcd(ll a,ll b) { return __gcd(a, b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
ll modexp(ll a,ll b,ll m) { ll res=1; while (b>0) { if (b&1) res=(res*a)%m; a=(a*a)%m; b>>=1; } return res; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void Case(int &x) {cout << "Case " << x++ << ": ";}

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

/* All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef __int128 lll;

int tc = 1;

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	// CUSTOM CHANGE: Added variables for sum and toggle lazy propagation
	ll sum = 0; // sum of the range
	bool toggle_lazy = false; // lazy toggle flag
	
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
			// CUSTOM CHANGE: Initialize sum
			sum = l->sum + r->sum;
		}
		else {
			val = v[lo];
			sum = v[lo]; // CUSTOM CHANGE: Initialize sum for leaf
		}
	}
	
	// CUSTOM CHANGE: Constructor for empty range with sum
	Node(int lo, int hi, ll init_sum) : lo(lo), hi(hi), sum(init_sum) {}
	
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	
	// CUSTOM CHANGE: Added sum query function
	ll query_sum(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return sum;
		push();
		return l->query_sum(L, R) + r->query_sum(L, R);
	}
	
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	
	// CUSTOM CHANGE: Added toggle function for range toggle
	void toggle(int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			// Toggle all bits in this range
			toggle_lazy = !toggle_lazy;
			sum = (hi - lo) - sum; // flip the sum
		} else {
			push();
			l->toggle(L, R);
			r->toggle(L, R);
			sum = l->sum + r->sum;
		}
	}
	
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid, 0); r = new Node(mid, hi, 0); // CUSTOM CHANGE: Initialize with sum
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
			
		// CUSTOM CHANGE: Handle toggle lazy propagation
		if (toggle_lazy) {
			l->toggle(lo, hi);
			r->toggle(lo, hi);
			toggle_lazy = false;
		}
	}
};

// CUSTOM CHANGE: Global variables for the solution
vector<vector<int>> adj;
vector<int> euler_tour;
vector<int> start_time, end_time;
vector<int> lights;
int timer = 0;

// CUSTOM CHANGE: DFS for Euler tour
void dfs(int v) {
	start_time[v] = timer;
	euler_tour.push_back(lights[v]);
	timer++;
	
	for (int u : adj[v]) {
		dfs(u);
	}
	
	end_time[v] = timer;
}

void solve() {
	// CUSTOM CHANGE: Complete solution implementation
	int n;
	cin >> n;
	
	adj.assign(n + 1, vector<int>());
	start_time.assign(n + 1, 0);
	end_time.assign(n + 1, 0);
	lights.assign(n + 1, 0);
	euler_tour.clear();
	timer = 0;
	
	// Read parent information and build adjacency list
	for (int i = 2; i <= n; i++) {
		int p;
		cin >> p;
		adj[p].push_back(i);
	}
	
	// Read initial light states
	for (int i = 1; i <= n; i++) {
		cin >> lights[i];
	}
	
	// Perform Euler tour starting from root (vertex 1)
	dfs(1);
	
	// Create segment tree
	Node* seg = new Node(euler_tour, 0, n);
	
	int q;
	cin >> q;
	
	while (q--) {
		string op;
		int v;
		cin >> op >> v;
		
		if (op == "pow") {
			// Toggle lights in subtree of v
			seg->toggle(start_time[v], end_time[v]);
		} else {
			// Get count of lights on in subtree of v
			cout << seg->query_sum(start_time[v], end_time[v]) << "\n";
		}
	}
}

int main() {
    // auto st = std::chrono::high_resolution_clock::now();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    // CUSTOM CHANGE: Remove multiple test cases as this problem has only one test case
    solve();

    // cerr << "Time measured: " << (ld)(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st)).count() / 1000.0 << " seconds.\n";

    return 0;
}