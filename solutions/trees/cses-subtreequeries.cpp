#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n+1, 0) {}

    void update(int i, long long delta) {
        for (; i <= n; i += i & -i)
            bit[i] += delta;
    }

    long long query(int i) {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    long long rangeQuery(int l, int r) {
        return query(r) - query(l-1);
    }
};

const int MAXN = 200005;
vector<int> g[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
long long val[MAXN];        // node values
long long flat[MAXN];       // array after Euler Tour

void dfs(int u, int p) {
    tin[u] = ++timer;
    flat[timer] = val[u];
    for (int v : g[u]) if (v != p)
        dfs(v, u);
    tout[u] = timer;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> val[i];

    for (int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);

    Fenwick fenw(n);
    // build fenwick tree using flat[]
    for (int i = 1; i <= n; i++)
        fenw.update(i, flat[i]);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int s;
            long long x;
            cin >> s >> x;
            long long current = fenw.rangeQuery(tin[s], tin[s]);
            fenw.update(tin[s], x - current); // point update
        }
        else {
            int s;
            cin >> s;
            cout << fenw.rangeQuery(tin[s], tout[s]) << "\n";
        }
    }
}
