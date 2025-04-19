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
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define fise(i, s, e) for (long long int i = s; i < e; i++)
#define fnr(i, n) for (long long int i = 0; i < n; i++)
#define fora(a) for(auto u:a)
#define cf(i, s, e) for (long long int i = s; i <= e; i++)
#define fies(i, e, s) for (long long int i = e; i > s; i--)
#define len(s) (ll)s.size()
#define pb push_back
#define eb emplace_back
#define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed, ios::floatfield);

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
template <class T> void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }
template <class T> void print(T str) { cout << str << '\n'; }
template <class T> void prints(T str) { cout << str << " "; }
void printInt128(__int128 x) { if (x == 0) { cout << "0"; return; } string res = ""; while (x) { res += (char)('0' + (x % 10)); x /= 10; } reverse(res.begin(), res.end()); cout << res; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
string to_upper(string a) { for (int i = 0; i < (int)a.size(); ++i) if (a[i] >= 'a' && a[i] <= 'z') a[i] -= 'a' - 'A'; return a; }
string to_lower(string a) { for (int i = 0; i < (int)a.size(); ++i) if (a[i] >= 'A' && a[i] <= 'Z') a[i] += 'a' - 'A'; return a; }
bool prime(ll a) { if (a == 1) return 0; for (int i = 2; i <= round(sqrt(a)); ++i) if (a % i == 0) return 0; return 1; }
ll modexp(ll a, ll b, ll m) { ll res = 1; while (b > 0) { if (b & 1) res = (res * a) % m; a = (a * a) % m; b >>= 1; } return res; }
void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

/* All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef __int128 lll;

void solve() {
    // nth tribonacci number modulo 26
    // t0 = t1 = 0
    // t2 = 1
    // ti = ti-1 + ti-2 + ti- 3
    // n = 9
    // 0 0 1 1 2 4 7 13 24 44 

    int n; cin >> n;
    ll t0 = 0, t1 = 0;
    ll t2 = 1;

    if (n == 1) print(t0);
    else if (n == 2) print(t1);
    else if (n == 3) print(t2);
    else {

        ll ti = 0;
        fnr(i, n-2) {
            ti = t0 + t1 + t2;

            t0 = t1; t1 = t2; t2 = ti;

        }
        print(ti % 26);
    }
}

int main() {
    //auto st = std::chrono::high_resolution_clock::now();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    // int t; cin >> t; while(t--)
    solve();

    //cerr << "Time measured: " << (ld)(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st)).count() / 1000.0 << " seconds.\n";

    return 0;
}