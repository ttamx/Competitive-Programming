#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> par(n);
    iota(par.begin(),par.end(),1);
    par[n-1]=-1;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        par[u]=max(par[u],v);
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++)adj[par[i]].emplace_back(i);
    vector<int> sz(n,-1),hv(n,-1),tin(n,-1),tout(n,-1),pos(n,-1),dep(n);
    int timer=-1;
    function<void(int)> dfs=[&](int u){
        tin[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        for(auto v:adj[u]){
            dep[v]=dep[u]+1;
            dfs(v);
            sz[u]+=sz[v];
            if(hv[u]==-1||(sz[v]>sz[hv[u]]))hv[u]=v;
        }
        tout[u]=timer;
    };
    dfs(n-1);
    Fenwick<ll> fcnt(n),fsum(n);
    ll cnt=0,ans=0;
    auto query=[&](int d){
        cnt+=fcnt.query(0,d)+fcnt.query(d,n-1);
        ans+=d*fcnt.query(d,n-1);
        ans+=fsum.query(d);
    };
    auto update=[&](int d,int v){
        fcnt.update(d,v);
        fsum.update(d,d*v);
    };
    function<void(int,bool)> sack=[&](int u,bool del){
        for(auto v:adj[u])if(v!=hv[u])sack(v,true);
        if(hv[u]!=-1)sack(hv[u],false);
        cnt=0;
        query(dep[u]);
        update(dep[u],+1);
        for(auto v:adj[u])if(v!=hv[u]){
            for(int i=tin[v];i<=tout[v];i++)query(dep[pos[i]]);
            for(int i=tin[v];i<=tout[v];i++)update(dep[pos[i]],+1);
        }
        ans-=cnt*dep[u];
        if(del)for(int i=tin[u];i<=tout[u];i++)update(dep[pos[i]],-1);
    };
    sack(n-1,true);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}