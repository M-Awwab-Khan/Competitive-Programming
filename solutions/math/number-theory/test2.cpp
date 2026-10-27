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

void solve() {
    ll M; cin >> M;

    ll n = M;
    vector<ll> factors;
    while (n % 2 == 0) {
        n /= 2;
        factors.push_back(2);
    }

    for (int i = 3; i*i <= n; i += 2) {
        while (n % i == 0) {
            n /= i;
            factors.push_back(i);
        }
    }

    if (n > 1) factors.push_back(n);


    sort(factors.begin(), factors.end(), [&](const int &a, const int &b) {
        if ((int)to_string(a).size() == (int)to_string(b).size()) return a > b;
        return (int)to_string(a).size() < (int)to_string(b).size();
    });

    // for (auto x: factors) cout << x << " ";

    ll ans = 0;
    int i = 0;
    while (M > 1) {
        ans += (M * (int)to_string(factors[i]).size());
        // cout << ans << " ";
        M /= factors[i++];
    }

    cout << ans << endl;


}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
