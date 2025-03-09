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
#define sort(a) sort(a.begin(), a.end())
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

struct Bigint {
    string a;
    int sign;

    Bigint(){}
    void operator = (string b) {
        a= (b[0]=='-' ? b.substr(1) : b);
        reverse(a.begin(), a.end());
        (*this).Remove0(b[0]=='-' ? -1 : 1);
    }
    Bigint(string x) {(*this)=x;}
    Bigint(ll x) {(*this)=to_string(x);}
    void operator = (ll x){*this=to_string(x);}

    char operator[](int i){return a[i];}
    int size() {return a.size();}
    Bigint inverseSign() {sign*=-1; return (*this);}

    Bigint Remove0(int newSign) {
        sign = newSign;
        for(int i=a.size()-1; i>0 && a[i]=='0'; i--) a.pop_back();
        if(a.size()==1 && a[0]=='0') sign=1;
        return (*this);
    }

    bool operator == (Bigint x) {return sign==x.sign && a==x.a;}
    bool operator == (string x) {return *this==Bigint(x);}
    bool operator == (ll x)     {return *this==Bigint(x);}
    bool operator != (Bigint x) {return !(*this==x);}
    bool operator != (string x) {return !(*this==x);}
    bool operator != (ll x)     {return !(*this==x);}

    bool operator < (Bigint b) {
        if (sign!=b.sign) return sign<b.sign;
        if(a.size()!=b.size()) return a.size()*sign<b.size()*sign;
        for(int i=a.size()-1; i>=0; i--)
            if(a[i] != b[i]) return a[i]<b[i];
        return false;
    }
    bool operator <  (string x) {return *this<Bigint(x);}
    bool operator <  (ll x)     {return *this<Bigint(x);}
    bool operator <= (Bigint b) {return *this==b || *this<b;}
    bool operator <= (string b) {return *this==b || *this<b;}
    bool operator <= (ll b)     {return *this==b || *this<b;}
    bool operator >  (Bigint b) {return !(*this==b || *this<b);}
    bool operator >  (string x) {return !(*this==x || *this<x);}
    bool operator >  (ll b)     {return !(*this==b || *this<b);}
    bool operator >= (Bigint b) {return *this==b || *this>b;}
    bool operator >= (string b) {return *this==b || *this>b;}
    bool operator >= (ll b)     {return *this==b || *this>b;}

    Bigint operator + (Bigint b) {
        if(sign != b.sign) return (*this)-b.inverseSign();
        Bigint sum;
        for(int i=0, carry=0; i<a.size() || i<b.size() || carry; i++){
            if (i<a.size()) carry+=a[i]-'0';
            if (i<b.size()) carry+=b[i]-'0';
            sum.a += (carry % 10 + 48);
            carry /= 10;
        }
        return sum.Remove0(sign);
    }
    Bigint operator +  (string x) {return *this+Bigint(x);}
    Bigint operator +  (ll x)     {return *this+Bigint(x);}
    Bigint operator ++ (int) {*this+=1; return *this-1;}
    Bigint operator ++ ()    {*this+=1; return *this;}
      void operator += (Bigint x) {*this = *this+x;}
      void operator += (string x) {*this = *this+x;}
      void operator += (ll x)     {*this = *this+x;}


    Bigint operator - ( Bigint b ) {
        if(sign != b.sign) return (*this)+b.inverseSign();
        if(*this < b) return (b - *this).inverseSign();
        Bigint sub;
        for(int i=0,borrow=0; i<a.size(); i++) {
            borrow = a[i]-borrow-(i<b.size() ? b.a[i] : '0');
            sub.a += borrow>=0 ? borrow+'0' : borrow + 58;
            borrow = borrow>=0 ? 0:1;
        }
        return sub.Remove0(sign);
    }
    Bigint operator - (string x) {return *this-Bigint(x);}
    Bigint operator - (ll x)     {return *this-Bigint(x);}
    Bigint operator -- (int) {*this-=1; return *this+1;}
    Bigint operator -- ()    {*this-=1; return *this;}
      void operator -= (Bigint x) {*this = *this-x;}
      void operator -= (string x) {*this = *this-x;}
      void operator -= (ll x)     {*this = *this-x;}

    Bigint operator * (Bigint b) {
        Bigint mult("0");
        for(int i=0, k=a[i]; i<a.size(); i++, k=a[i]) {
            while(k-- -'0') mult=mult+b;
            b.a.insert(b.a.begin(),'0');
        }
        return mult.Remove0(sign * b.sign);
    }
    Bigint operator * (string x) {return *this*Bigint(x);}
    Bigint operator * (ll x)     {return *this*Bigint(x);}
      void operator *= (Bigint x) {*this = *this*x;}
      void operator *= (string x) {*this = *this*x;}
      void operator *= (ll x)     {*this = *this*x;}

    Bigint operator / (Bigint b) {
        if(b.size()==1 && b[0]=='0') b.a[0]/=(b[0]-'0');
        Bigint c("0"), d;
        for(int j=0; j<a.size(); j++) d.a += "0";
        int dSign = sign*b.sign; b.sign=1;
        for(int i=a.size()-1; i>=0; i--) {
            c.a.insert(c.a.begin(),'0');
            c=c+a.substr(i,1);
            while(!(c<b)) c=c-b, d.a[i]++;
        }
        return d.Remove0(dSign);
    }
    Bigint operator / (string x) {return *this/Bigint(x);}
    Bigint operator / (ll x)     {return *this/Bigint(x);}
      void operator /= (Bigint x) {*this = *this/x;}
      void operator /= (string x) {*this = *this/x;}
      void operator /= (ll x)     {*this = *this/x;}

    Bigint operator % (Bigint b) {
        if( b.size()==1 && b[0]=='0') b.a[0]/=(b[0]-'0') ;
        Bigint c("0");
        int cSign = sign*b.sign; b.sign=1;
        for( int i=a.size()-1; i>=0; i-- ) {
            c.a.insert( c.a.begin(),'0');
            c = c+a.substr(i,1);
            while(!(c<b)) c=c-b;
        }
        return c.Remove0(cSign);
    }
    Bigint operator % (string x) {return *this%Bigint(x);}
    Bigint operator % (ll x)     {return *this%Bigint(x);}
      void operator %= (Bigint x) {*this = *this%x;}
      void operator %= (string x) {*this = *this%x;}
      void operator %= (ll x)     {*this = *this%x;}

    void print() {
        if(sign==-1) putchar('-');
        for(int i=a.size()-1; i>=0; i--) putchar(a[i]);
    }
    friend istream& operator >>(istream &in,Bigint &x){
        string s; in>>s; x=s; return in;
    }
    friend ostream& operator <<(ostream &out,Bigint &x){
        if(x.sign==-1) putchar('-');
        for(int i=x.size()-1; i>=0; i--)
            putchar(x[i]);
        return out;
    }

    friend Bigint pow(Bigint base, Bigint pw){
        Bigint ans=1;
        while(pw!=0){
            if(pw%2 !=0) ans*=base;
            base*=base, pw/=2;
        }
        return ans;
    }
    friend Bigint pow(Bigint a, Bigint b,Bigint mod) {
        if (b==0) return Bigint(1);
        Bigint tmp=pow(a,b/2,mod);
        if ((b%2)==0) return (tmp*tmp)%mod;
        else return (((tmp*tmp)%mod)*a)%mod;
    }
    friend Bigint sqrt(Bigint x) {
        Bigint ans=x,tmp=(x+1)/2;
        while (tmp<ans) ans=tmp, tmp=(tmp+x/tmp)/2;
        return ans;
    }
    friend Bigint gcd(Bigint a,Bigint b){
        return a%b==0 ? b : gcd(b, a%b);
    }
    friend Bigint lcm(Bigint a,Bigint b){
        return a/gcd(a,b);
    }
};

void printInt128(__int128 x) {
    if (x == 0) { cout << "0"; return; }
    string res = "";
    while (x) {
        res += (char)('0' + (x % 10));
        x /= 10;
    }
    reverse(res.begin(), res.end());
    cout << res;
}

__int128 explore(int i, int j, int n, vvi &board, vector<vector<__int128>> &dp) {
    if (i >= n || j >= n) return -1;
    if (i == n - 1 && j == n - 1) return 1;
    if (board[i][j] == 0) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    dp[i][j] = 0;
    if (i + board[i][j] < n) dp[i][j] += explore(i + board[i][j], j, n, board, dp);
    if (j + board[i][j] < n) dp[i][j] += explore(i, j + board[i][j], n, board, dp);

    return dp[i][j];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vvi board(n, vi(n));

    fnr(i, n) {
        fnr(j, n) {
            cin >> board[i][j];
        }
    }

    vector<vector<__int128>> dp(n, vector<__int128>(n, -1));
    printInt128(explore(0, 0, n, board, dp));
    return 0;
}
