#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#define f first
#define s second
#define ll long long
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
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define fise(i, s, e) for (long long int i = s; i < e; i++)
#define fnr(i, n) for (long long int i = 0; i < n; i++)
#define fora(a) for(auto u:a)
#define cf(i, s, e) for (long long int i = s; i <= e; i++)
#define fies(i, e, s) for (long long int i = e; i > s; i--)
// #define sort(a) sort(a.begin(), a.end())
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
#define nearestPowerOfTwo(S) (1<<lround(log2(S)))
#define turnOffLastBit(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveBits(S) ((S) & (S+1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S-1))
/* PRINTS */
template <class T> void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }
template <class T> void print(T str) { cout << str << endl; }
template <class T> void prints(T str) { cout << str << " "; }
/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
ll max(ll a, ll b) { if (a>b) return a; return b; }
ll min(ll a,ll b) { if (a<b) return a; return b; }
int max(int a,int b) { if (a>b) return a; return b; }
int min(int a,int b) { if (a<b) return a; return b; }
ll gcd(ll a,ll b) { return __gcd(a, b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
ll modexp(ll a,ll b,ll m) { ll res=1; while (b>0) { if (b&1) res=(res*a)%m; a=(a*a)%m; b>>=1; } return res; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
/* All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
vpll mergeIntervals(vpll& intervals) {
    if (intervals.empty()) return {};
    sort(all(intervals));
    vpll merged;
    merged.pb(intervals[0]);

    fnr(i, intervals.size()) {
        if (intervals[i].f <= merged.back().s+ 1) {
            merged.back().s = max(merged.back().s, intervals[i].s);
        } else {
            merged.pb(intervals[i]);
        }
    }
    return merged;
}

void solve() {

        int n, m;
        cin >> n >> m;
        vll x(n), r(n);
        fnr(i, n) cin >> x[i];
        fnr(i, n) cin >> r[i];

        vpll y0;
        fnr(i, n) {
            int start = x[i] - r[i];
            int end = x[i] + r[i];
            y0.pb({start, end});
        }
        // x wale
        vpll merged_y0 = mergeIntervals(y0);
        ll ans = 0;
        for (auto& interval : merged_y0) {
            ans += interval.s - interval.f + 1;
        }
        // higher
        map<ll, vpll> y_dict;
        fnr(i, n) {
            ll xi = x[i];
            ll ri = r[i];
            cf(y, 1, m) {
                ll y_sq = (ll)y * y;
                ll r_sq = (ll)ri * ri;
                if (y_sq > r_sq) break;

                ll dx = sqrt(r_sq - y_sq);
                ll start = xi - dx;
                ll end = xi + dx;
                if (start <= end) {
                    y_dict[y].pb({start, end});
                }
            }
        }

        for (auto& [y, intervals] : y_dict) {
            vpll merged = mergeIntervals(intervals);
            ll total = 0;
            for (auto& interval : merged) {
                total += interval.s - interval.f + 1;
            }
            ans += 2 * total;
        }

        print(ans);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
