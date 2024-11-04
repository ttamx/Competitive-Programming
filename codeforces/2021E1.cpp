#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct DSU{
    int n;
    vector<int> p,sz;
    vector<vector<ll>> dp;
    DSU(int _n){
        n=_n;
        p.assign(n,0);
        iota(p.begin(),p.end(),0);
        sz.assign(n,0);
        dp.assign(n,vector<ll>(1,0LL));
    }
    int fp(int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    }
    bool uni(int u,int v,ll w){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        vector<ll> ndp(sz[u]+sz[v]+1,LINF);
        for(int i=0;i<=sz[u];i++){
            for(int j=0;j<=sz[v];j++){
                ndp[i+j]=min(ndp[i+j],dp[u][i]+dp[v][j]);
            }
        }
        for(int i=1;i<=sz[u];i++){
            ndp[i]=min(ndp[i],dp[u][i]+w*sz[v]);
        }
        for(int i=1;i<=sz[v];i++){
            ndp[i]=min(ndp[i],dp[v][i]+w*sz[u]);
        }
        dp[u].clear();
        dp[v].clear();
        swap(dp[u],ndp);
        p[v]=u;
        sz[u]+=sz[v];
        return true;
    }
    vector<ll> &get_dp(int u){
        u=fp(u);
        return dp[u];
    }
};

void runcase(){
    int n,m,p;
    cin >> n >> m >> p;
    DSU dsu(n);
    for(int i=0;i<p;i++){
        int x;
        cin >> x;
        x--;
        dsu.sz[x]++;
        dsu.dp[x]=vector<ll>{LINF,0LL};
    }
    vector<tuple<int,int,int>> edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        edges.emplace_back(w,u,v);
    }
    sort(edges.begin(),edges.end());
    for(auto [w,u,v]:edges){
        dsu.uni(u,v,w);
    }
    auto ans=dsu.get_dp(0);
    while(ans.size()<=n){
        ans.emplace_back(0LL);
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}