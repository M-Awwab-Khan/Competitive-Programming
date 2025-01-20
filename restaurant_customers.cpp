#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define mll map<long long, long long>
#define fise(i, s, e) for (long long int i = s; i < e; i++)
#define fnr(i, n) for (long long int i = 0; i < n; i++)
#define fora(a) for(auto u:a)
#define cf(i, s, e) for (long long int i = s; i <= e; i++)
#define fies(i, e, s) for (long long int i = e - 1; i >= s; i--)
#define sort(a) sort(a.begin(), a.end())
#define pb push_back
#define eb emplace_back
#define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed,ios::floatfield);
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
void readint(ll &n) {     cin >> n; }
/* All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll n;
    cin >> n;
    vector<pll> times;
    // fnr(i, n) cin >> times[i].f >> times[i].s;

    // sort(times);
    // ll ans = 0, curr = 0;
    // ll i = 0, j = 0;
    // while (i < n && j < n) {
    //     if (times[i].f < times[j].s) {
    //         curr++;
    //         i++;
    //     } else {
    //         curr--;
    //         j++;
    //     }
    //     ans = max(ans, curr);
    // }
    // print(ans);
    fnr(i, n) {
        ll a, b;
        cin >> a >> b;
        times.eb(a, 1);
        times.eb(b, -1);
    }

    sort(times);
    ll ans = 0, curr = 0;
    fora(times) {
        curr += u.s;
        ans = max(ans, curr);
    }
    print(ans);
    return 0;
}
