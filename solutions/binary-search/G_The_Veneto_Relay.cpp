#include <bits/stdc++.h>
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
    void unite(int x, int y) {
        x=find(x); y=find(y);
        if(x==y) return;
        if(rank[x]<rank[y]) swap(x,y);
        parent[y]=x;
        if(rank[x]==rank[y]) rank[x]++;
    }
    bool same(int x, int y) { return find(x)==find(y); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M,K;
    cin >> N >> M >> K;
    vector<int> milestones(K);
    for(int i=0;i<K;i++) cin >> milestones[i];

    vector<tuple<int,int,int>> edges(M);
    for(int i=0;i<M;i++) {
        int u,v,w;
        cin >> u >> v >> w;
        edges[i]={u,v,w};
    }

    int lo=1, hi=100;
    int ans=-1;

    auto check = [&](int V) {
        DSU dsu(N);
        for(auto &[u,v,w]: edges) {
            if(w<=V) dsu.unite(u,v);
        }
        int root = dsu.find(milestones[0]);
        for(int i=1;i<K;i++)
            if(dsu.find(milestones[i]) != root) return false;
        return true;
    };

    while(lo<=hi) {
        int mid = (lo+hi)/2;
        if(check(mid)) {
            ans=mid;
            hi=mid-1;  // try smaller threshold
        } else lo=mid+1;
    }

    cout << ans << "\n";
    return 0;
}