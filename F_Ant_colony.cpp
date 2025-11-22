#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

#ifndef ONLINE_JUDGE
#include "debugging.cpp"
#else
#define debug(...)
#define debugArr(...)
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
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
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
template <typename... A> constexpr auto max(const A&... a){using T=std::common_type_t<A...>;return (std::max)({T(a)...});}
template <typename... A> constexpr auto min(const A&... a){using T=std::common_type_t<A...>;return (std::min)({T(a)...});}
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
template<typename T>
struct SegTree {
    int n;
    vector<T> tree;
    function<T(const T&, const T&)> merge;
    T identity;

    SegTree(int n, function<T(const T&, const T&)> mergeFunc, T identity)
        : n(n), merge(mergeFunc), identity(identity) {
        tree.assign(4 * n, identity);
    }

    void build(const vector<T> &arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(arr, v*2, tl, tm);
        build(arr, v*2+1, tm+1, tr);
        tree[v] = merge(tree[v*2], tree[v*2+1]);
    }

    void build(const vector<T> &arr) {
        build(arr, 1, 0, n-1);
    }

    void update(int v, int tl, int tr, int pos, T val) {
        if (tl == tr) {
            tree[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v*2, tl, tm, pos, val);
        else update(v*2+1, tm+1, tr, pos, val);
        tree[v] = merge(tree[v*2], tree[v*2+1]);
    }

    void update(int pos, T val) {
        update(1, 0, n-1, pos, val);
    }

    T query(int v, int tl, int tr, int l, int r) {
        if (l > r) return identity;
        if (l <= tl && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(
            query(v*2, tl, tm, l, min(r, tm)),
            query(v*2+1, tm+1, tr, max(l, tm+1), r)
        );
    }

    T query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};

void solve() {
    int n; cin >> n;
    vi a(n); rep(i,0,n) cin >> a[i];

    SegTree<int> sg(n, [&](const int &a, const int &b) {return gcd(a, b);}, 0);
    sg.build(a);

    umap<int, vi> mp;

    rep(i, 0, n) {
        mp[a[i]].pb(i);
    }
    int q; cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;
        --l;--r;
        int g = sg.query(l, r);
        debug(g);

        // freq of g in [l, r];
        if (mp.count(g)) {
            int x = upper_bound(all(mp[g]), r) - lower_bound(all(mp[g]), l);
            debug(x);
            print((r-l + 1) - x);
        }
        else print(r-l+1);
    }
}

int main() {
    // auto st = std::chrono::high_resolution_clock::now();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    // int t; cin >> t; while(t--)
    solve();

    // cerr << "Time measured: " << (ld)(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st)).count() / 1000.0 << " seconds.\n";

    return 0;
}