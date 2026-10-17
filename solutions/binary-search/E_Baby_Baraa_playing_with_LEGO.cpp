#include "bits/stdc++.h"
using namespace std;

void no() {cout << "NO" << "\n";}
void yes() {cout << "YES" << "\n";}

const int MAXN = 200005;
int n, q;
int a[MAXN];
int last_occ[MAXN];
int seg[4*MAXN];

void build(int node, int l, int r) {
    if (l == r) {
        seg[node] = last_occ[l];
        return;
    }
    int mid = (l + r) /2;
    build(2*node, l, mid);
    build(2*node + 1, mid + 1, r);
    seg[node] = min(seg[2*node], seg[2*node + 1]);
}

void update(int node, int l, int r, int idx){
    if (l == r) {
        seg[node] = last_occ[l];
        return;
    }
    int mid = (l + r)/2;
    if (idx <= mid) update(2*node, l, mid, idx);
    else update(2*node + 1, mid+1, r, idx);

    seg[node] = min(seg[2*node], seg[2*node+1]);
}

int query(int node, int l, int r, int ql, int qr, int val) {
    if (r < ql || l > qr || seg[node] >= val) return -1;
    if (l == r) return l;

    int mid = (l + r) / 2;
    int left = query(2*node, l, mid, ql, qr, val);
    if (left!=-1) return left;
    return query(2*node + 1, mid+1, r, ql, qr, val);
}

void solve() {
    cin >> n >>q;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 1; i <= n; ++i) last_occ[i] = 0;

    build(1, 1, n);

    vector<vector<pair<int, int>>> queries(n + 1);
    vector<int> ans(q);

    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        queries[r].push_back({l, i});
    }

    for (int r=1; r<= n; ++r) {
        last_occ[a[r]] = r;
        update(1, 1, n, a[r]);

        for (auto [l, idx]: queries[r]) {
            ans[idx] = query(1, 1, n, 1, n, l);
        }
    }

    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
}

// write min seg tree
// store last occ indices in seg tree nodes
// sort the queries by r in increasing order
// iterate over those queries and try to find any lego type that is beyond the range
// store the ans in separate array
// iterate through the array printing all the answers




int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int t; cin >> t; while (t--)
    solve();
    return 0;
}