// Boundary and independent small-instance checks for the original cheat-sheet snippets.
#include "sp-reference.hpp"
#include <cassert>
using namespace std;
using ll = long long;
using i128 = __int128_t;

static bool point_on_segment_real(sp::Point a, sp::Point b, sp::Point p) {
    long double dx=b.x-a.x, dy=b.y-a.y, px=p.x-a.x, py=p.y-a.y;
    long double square=dx*dx+dy*dy;
    if (square==0) return a.x==p.x && a.y==p.y;
    long double t=(px*dx+py*dy)/square;
    return t>=0 && t<=1 && fabsl(px-t*dx)<1e-12L && fabsl(py-t*dy)<1e-12L;
}
static bool intersection_oracle(sp::Point a,sp::Point b,sp::Point c,sp::Point d) {
    long double ux=b.x-a.x,uy=b.y-a.y,vx=d.x-c.x,vy=d.y-c.y;
    long double qx=c.x-a.x,qy=c.y-a.y,det=ux*vy-uy*vx;
    if (det==0) return point_on_segment_real(a,b,c)||point_on_segment_real(a,b,d)
        ||point_on_segment_real(c,d,a)||point_on_segment_real(c,d,b);
    long double t=(qx*vy-qy*vx)/det,s=(qx*uy-qy*ux)/det;
    return t>=0 && t<=1 && s>=0 && s<=1;
}
int main() {
    for(ll a=-30;a<=30;++a) for(ll b=-8;b<=8;++b) if(b) {
        assert(sp::floor_div(a,b)==(ll)floorl((long double)a/b));
        assert(sp::ceil_div(a,b)==(ll)ceill((long double)a/b));
    }
    assert(sp::floor_div((i128)LLONG_MIN,-1)==((i128)1<<63));
    assert(sp::ceil_nonnegative(LLONG_MAX,2)==LLONG_MAX/2+1);
    for(ll x:vector<ll>{0,1,2,3,4,15,16,17,1'000'000'000'000'000'000LL,LLONG_MAX}) {
        ll r=sp::integer_sqrt(x);
        assert((i128)r*r<=x && (i128)(r+1)*(r+1)>x);
    }
    for(ll a=-15;a<=15;++a) for(ll e=0;e<=20;++e) for(ll m=1;m<=25;++m) {
        ll expected=1%m;
        for(ll i=0;i<e;++i) expected=(ll)((i128)expected*((a%m+m)%m)%m);
        assert(sp::power_mod(a,e,m)==expected);
    }
    assert(sp::power_mod(-1,3,LLONG_MAX)==LLONG_MAX-1);
    for(int n=0;n<=30;++n) for(int threshold=0;threshold<=n;++threshold) {
        assert(sp::first_true(0,n,[&](ll x){return x>=threshold;})==threshold);
        assert(sp::last_true(0,n,[&](ll x){return x<=threshold;})==threshold);
    }
    auto spf=sp::smallest_prime_factors(1000);
    for(int n=1;n<=1000;++n) {
        ll reconstructed=1;
        for(auto [p,e]:sp::factorize(n)) for(int j=0;j<e;++j) reconstructed*=p;
        assert(reconstructed==n);
        if(n>=2) {
            assert(spf[n]>=2 && n%spf[n]==0);
            for(int d=2;d<spf[n];++d) assert(n%d!=0);
        }
    }
    assert(sp::smallest_prime_factors(0)==vector<int>{0});
    sp::Combinations combinations(100,101);
    vector<vector<ll>> pascal(101,vector<ll>(101));
    for(int n=0;n<=100;++n) for(int k=0;k<=n;++k) {
        pascal[n][k]=(k==0||k==n)?1:(pascal[n-1][k-1]+pascal[n-1][k])%101;
        assert(combinations.choose(n,k)==pascal[n][k]);
    }
    assert(combinations.choose(2,3)==0 && combinations.choose(2,-1)==0);
    mt19937 rng(1729);
    for(int trial=0;trial<250;++trial) {
        int n=(int)(rng()%22);
        vector<ll>a(n);
        for(ll&x:a) x=(ll)(rng()%15)-7;
        set<ll> values(a.begin(),a.end()); int expected_mex=0;
        while(values.count(expected_mex)) ++expected_mex;
        assert(sp::mex(a)==expected_mex);
        for(ll k=-10;k<=10;++k) {
            ll expected=0,pairs=0;
            for(int l=0;l<n;++l) {
                ll sum=0;
                for(int r=l;r<n;++r) {sum+=a[r]; expected+=sum==k;}
                for(int r=l+1;r<n;++r) pairs+=a[l]+a[r]<=k;
            }
            assert(sp::count_sum_k(a,k)==expected);
            assert(sp::count_pairs_leq(a,k)==pairs);
        }
        for(int k=0;k<=5;++k) {
            ll expected=0;
            for(int l=0;l<n;++l) {
                set<ll> distinct;
                for(int r=l;r<n;++r) {distinct.insert(a[r]); expected+=(int)distinct.size()<=k;}
            }
            assert(sp::at_most_distinct(a,k)==expected);
        }
        for(int k=1;k<=n;++k) {
            vector<ll> expected;
            for(int l=0;l+k<=n;++l) expected.push_back(*max_element(a.begin()+l,a.begin()+l+k));
            assert(sp::window_maximum(a,k)==expected);
        }
        vector<int> dp(n,1); int best=0;
        for(int i=0;i<n;++i) {
            for(int j=0;j<i;++j) if(a[j]<a[i]) dp[i]=max(dp[i],dp[j]+1);
            best=max(best,dp[i]);
        }
        assert(sp::lis_length(a)==best);
        string text;
        for(int i=0;i<n;++i) text+=(char)('a'+rng()%3);
        auto pi=sp::prefix_function(text);
        for(int i=0;i<n;++i) {
            int longest=0;
            for(int len=1;len<=i;++len) if(text.substr(0,len)==text.substr(i-len+1,len)) longest=len;
            assert(pi[i]==longest);
        }
        sp::Fenwick fenwick(n); sp::SumSegTree tree(a);
        for(int i=0;i<n;++i) fenwick.add(i,a[i]);
        for(int step=0;step<60;++step) {
            if(n && rng()%2) {
                int index=(int)(rng()%(unsigned)n); ll value=(ll)(rng()%101)-50;
                fenwick.add(index,value-a[index]); a[index]=value; tree.set_value(index,value);
            }
            int l=(int)(rng()%(unsigned)(n+1)),r=(int)(rng()%(unsigned)(n+1));
            if(l>r) swap(l,r);
            ll expected=accumulate(a.begin()+l,a.begin()+r,0LL);
            assert(fenwick.range(l,r)==expected && tree.range(l,r)==expected);
        }
    }
    vector<ll> extremes{LLONG_MIN,0,LLONG_MAX,LLONG_MAX};
    ll expected_pairs=0;
    for(int i=0;i<4;++i) for(int j=i+1;j<4;++j) expected_pairs+=(i128)extremes[i]+extremes[j]<=LLONG_MAX;
    assert(sp::count_pairs_leq(extremes,LLONG_MAX)==expected_pairs);
    for(int trial=0;trial<150;++trial) {
        int n=(int)(rng()%10),capacity=(int)(rng()%20);
        vector<int>w(n); vector<ll>v(n);
        for(int i=0;i<n;++i) {w[i]=1+(int)(rng()%6);v[i]=(ll)(rng()%21)-10;}
        ll best=0;
        for(int mask=0;mask<(1<<n);++mask) {
            int weight=0;ll value=0;
            for(int i=0;i<n;++i) if(mask&(1<<i)) {weight+=w[i];value+=v[i];}
            if(weight<=capacity) best=max(best,value);
        }
        assert(sp::knapsack01(w,v,capacity)==best);
    }
    sp::DSU dsu(25); vector<int>labels(25); iota(labels.begin(),labels.end(),0);
    for(int step=0;step<150;++step) {
        int a=(int)(rng()%25),b=(int)(rng()%25),old=labels[b],replacement=labels[a];
        bool merged=old!=replacement; assert(dsu.unite(a,b)==merged);
        for(int& label:labels) if(label==old) label=replacement;
        for(int i=0;i<25;++i) {
            assert(dsu.size[dsu.find(i)]==count(labels.begin(),labels.end(),labels[i]));
            for(int j=0;j<25;++j) assert((dsu.find(i)==dsu.find(j))==(labels[i]==labels[j]));
        }
    }
    const ll INF=LLONG_MAX/4;
    for(int trial=0;trial<100;++trial) {
        int n=1+(int)(rng()%8);
        vector<vector<int>>g(n);
        vector<vector<pair<int,ll>>>weighted(n);
        vector<vector<ll>>floyd(n,vector<ll>(n,INF)),hops=floyd;
        for(int i=0;i<n;++i) {floyd[i][i]=0;hops[i][i]=0;}
        for(int i=0;i<n;++i) for(int j=0;j<n;++j) if(rng()%3==0) {
            ll weight=rng()%21;g[i].push_back(j);weighted[i].push_back({j,weight});
            floyd[i][j]=min(floyd[i][j],weight);hops[i][j]=min(hops[i][j],1LL);
        }
        for(int k=0;k<n;++k) for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
            if(floyd[i][k]!=INF && floyd[k][j]!=INF) floyd[i][j]=min(floyd[i][j],floyd[i][k]+floyd[k][j]);
            if(hops[i][k]!=INF && hops[k][j]!=INF) hops[i][j]=min(hops[i][j],hops[i][k]+hops[k][j]);
        }
        for(int source=0;source<n;++source) {
            assert(sp::dijkstra(weighted,source)==floyd[source]);
            auto distances=sp::bfs(g,source);
            for(int v=0;v<n;++v) assert(distances[v]==(hops[source][v]==INF?-1:hops[source][v]));
        }
    }
    vector<sp::Point> points;
    for(ll x=0;x<3;++x) for(ll y=0;y<3;++y) points.push_back({x,y});
    for(auto a:points) for(auto b:points) for(auto c:points) for(auto d:points)
        assert(sp::segments_intersect(a,b,c,d)==intersection_oracle(a,b,c,d));
    ll large=1'000'000'000'000'000'000LL;
    assert(sp::cross({-large,-large},{large,-large},{large,large})>0);
    assert(sp::segments_intersect({-large,-large},{large,large},{-large,large},{large,-large}));
    cout<<"All cheat-sheet snippet checks passed.\n";
}
