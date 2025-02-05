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
    unordered_map<int, int> rank_to_star;
    for(int i = 25; i >= 21; i--) {
        rank_to_star[i] = 2;
    }
    for(int i = 20; i >= 16; i--) {
        rank_to_star[i] = 3;
    }
    for(int i = 15; i >= 11; i--) {
        rank_to_star[i] = 4;
    }
    for(int i = 10; i >= 1; i--) {
        rank_to_star[i] = 5;
    }

    string s;
    cin >> s;

    bool legend = false;
    int rank = 25;
    int stars = 0;
    int winstreak = 0;

    for(auto i : s) {
        if(i == 'W') {
            winstreak++;

            // If winstreak
            if(rank >= 6 && winstreak >= 3) {
                stars++;
                if(rank_to_star[rank]+1 == stars) {
                    rank--;
                    stars = 1;
                }
            }

            // Normal star
            stars++;
            if(rank_to_star[rank]+1 == stars) {
                rank--;
                stars = 1;
            }

            // Check legend
            if(rank == 0) {
                legend = true;
            }

        }
        else {
            winstreak = 0;
            if(rank <= 20) {
                stars--;
            }
            if(stars == -1) {
                if(rank == 20) {
                    stars = 0;
                }
                else {
                    rank++;
                    stars = rank_to_star[rank]-1;
                }
            }
        }
    }

    if(legend) {
        cout << "Legend" << endl;
    }
    else {
        cout << rank << endl;
    }
    return 0;
}
