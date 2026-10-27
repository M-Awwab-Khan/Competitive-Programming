#include "bits/stdc++.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;

template <class T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ll long long
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi>
#define vvll vector<vll>
#define endl '\n'
#define pb push_back

#define f(i, s, e) for (ll i = (s); i < (e); ++i)
#define fr(i, s, e) for (ll i = (s); i > (e); --i)
#define iv(vec) for(auto &value: vec) cin>>value;
#define pr(vec) {for(auto value: vec) cout<<value<<" ";}

#define all(a) a.begin(), a.end()

int tc = 1;
void yesno(int x) { cout << (x ? "YES\n" : "NO\n"); }
void printCase(int x)
{
    cout << "Case " << x << ": ";
}

const int N = 200005;
int aa[N][19];

void solve()
{
    ll n, q; cin >> n >> q;
    vector<ll> a(n + 1); for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> s;
    s.reserve(n);

    for (int i = 1; i <= n; ++i) {
        while (!s.empty() && a[s.back()] < a[i]) s.pop_back();

        if (!s.empty()) aa[i][0] = s.back();

        s.push_back(i);
    }

    for (int l = 1; l < 19; ++l) {
        for (int i = 1; i <= n; ++i) {
            aa[i][l] = aa[aa[i][l-1]][l-1];
        }
    }

    for (int l = 0; l < 5; ++l) {
        cout << "level " << l << "   ";
        for (int i = 1; i <= n; ++i) cout << aa[i][l] << " ";
        cout << endl;
    }

    while (q--) {
        int l, r; cin>> l >> r;
        int ans = 1;
        int c = r;

        for (int level = 19-1; level >= 0; --level) {
           if (aa[c][level] >= l) {
               ans += (1 << level);
               c = aa[c][level];
           }
        }
        cout << ans << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

    return 0;
}
