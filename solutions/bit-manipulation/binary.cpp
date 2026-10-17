#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define fe(i,s,e) for(long long int i=s;i<=e;i++)
#define fr(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()

/* PRINTS */
template <class T>
void print_v(vector<T> &v) { for (auto x : v) cout << x << ' '; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void printCase(int i) {cout << "Case " << i << ": ";}

string get(ll n) {
    string res = "";
    while(n) {

        res += char( (n % 2) + '0' );
        n = n / 2;
    }

    reverse(res.begin(), res.end());

    return res;

}

struct Node {
public:
    Node* l;
    Node* r;
    string val;

    Node(string val, Node* left = nullptr, Node* right = nullptr) {
        this->val = val;
        l = left;
        r = right;
    }
};

string func(Node* node) {
    if(!node) return "";

    return func(node->l) + node->val + func(node->r);

}

void solve() {
   ll n;
   cin >> n;

    string s = get(n);

    Node* root = new Node("1");

    Node* curr = root;
    bool first = true;
    for (char c : s) {
        if(first) {first = false; continue;}
        if (c == '0') {
            curr->l = new Node("0");
            curr = curr->l;
        } else {
            curr->r = new Node("1");
            curr = curr->r;
        }
    }

    string res = func(root);

    //cout << res << '\n';

    n = res.size();
    ll ans = 0;
    int j;
    f(i, 0, n) {
        j = n - i - 1;
        if(res[i] == '1') {
            ans += (1LL << j);
        }
    }

    cout << ans << '\n';

}

int main() {
   ios::ios_base::sync_with_stdio(0);
   cin.tie(NULL);
   int t = 1;
   // cin >> t;
   while(t--) {
       solve();
   }
   return 0;
}