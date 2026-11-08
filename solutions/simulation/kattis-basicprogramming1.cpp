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
    ll N, t; cin >> N >> t;
    vll a(N);
    fnr(i, N) cin >> a[i];
    if (t == 1) {
        print(7);
    } else if (t == 2) {
        if (a[0] > a[1]) {
            print("Bigger");
        } else if (a[0] == a[1]) {
            print("Equal");
        } else {
            print("Smaller");
        }
    } else if (t == 3) {
        vll b = {a[0], a[1], a[2]};
        sort(b);
        print(b[1]);
    } else if (t == 4) {
        ll sum = 0;
        fnr(i, N) sum += a[i];
        print(sum);
    } else if (t == 5) {
        ll sum = 0;
        fnr(i, N) {
            if (a[i] % 2 == 0) sum += a[i];
        }
        print(sum);
    } else if (t == 6) {
        string s = "";
        fnr(i, N) {
            s += (char)('a' + a[i] % 26);
        }
        print(s);
    } else if (t == 7) {
        set<ll> s;
        ll i = 0;
        while (1) {
            if (s.find(i) != s.end()) {
                print("Cyclic");
                break;
            }
            if (i >= N) {
                print("Out");
                break;
            }
            if (i == N - 1) {
                print("Done");
                break;
            }
            s.insert(i);
            i = a[i];
        }
    }
    return 0;
}
