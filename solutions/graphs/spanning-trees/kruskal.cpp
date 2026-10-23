#include "bits/stdc++.h"
using namespace std;
#define ll long long

struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n+1), rank(n+1, 0) {
        for(int i=1;i<=n;i++) parent[i]=i;
    }
    int find(int x) {
        if(parent[x]==x) return x;
        return parent[x]=find(parent[x]);
    }
    bool unite(int x, int y) {
        x=find(x); y=find(y);
        if(x==y) return false;
        if(rank[x]<rank[y]) swap(x,y);
        parent[y]=x;
        if(rank[x]==rank[y]) rank[x]++;
        return true;
    }
    bool same(int x, int y) { return find(x)==find(y); }
};

struct Edge {
    int u, v;
    ll cost;
    int id;
};
void solve() {
    int n, m; cin >> n >> m;
    int j; cin >> j;

    vector<Edge> edges(m);
    for (int i= 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
        edges[i].id = i;
    }

    DSU dsu(n);

    ll ans = edges[j - 1].cost;
    dsu.unite(edges[j-1].u, edges[j-1].v);

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){
        return a.cost < b.cost;
    });

    int cnt = 1;
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i].id == j-1) continue;
        if (dsu.unite(edges[i].u, edges[i].v)){
            ans += edges[i].cost;
            ++cnt;
            if (cnt == n-1) break;
        }
    }

    cout << ans << endl;


}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
