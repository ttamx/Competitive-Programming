#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(int i=0;i<n;i++)b[a[i]]=i;
    vector<vector<int>> adj(n),adj2(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    Fenwick<int> f(n+2);
    for(int i=0;i<=n+1;i++)f.update(i,1);
    vector<int> mex1(n),mex2(n),tin(n),tout(n),pos(n),sz(n),hv(n,-1),rt(n+1,-1);
    vector<ll> dp(n),dp2(n);
    int timer=-1;
    ll ans=0;
    Fenwick<ll> fcnt(n+2),fsum(n+2);
    function<void(int,int)> dfs=[&](int u,int p){
        tin[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        f.update(a[u],-1);
        dp[u]=mex1[u]=f.find(0);
        mex2[u]=f.find(1);
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            sz[u]+=sz[v];
            dp[u]+=dp[v];
            if(hv[u]==-1||sz[v]>sz[hv[u]])hv[u]=v;
            if(mex1[u]==mex1[v])adj2[u].eb(v);
        }
        f.update(a[u],+1);
        tout[u]=timer;
        rt[mex1[u]]=u;
    };
    auto update=[&](int u,int v){
        fcnt.update(mex1[u],v);
        fsum.update(mex1[u],v*mex1[u]);
    };
    function<void(int,int,bool)> sack1=[&](int u,int p,bool del){
        for(auto v:adj[u])if(v!=p&&v!=hv[u])sack1(v,u,true);
        if(hv[u]!=-1)sack1(hv[u],u,false);
        update(u,+1);
        for(auto v:adj[u])if(v!=p&&v!=hv[u]){
            for(int i=tin[v];i<=tout[v];i++)update(pos[i],+1);
        }
        if(a[u]>mex1[u]){
            dp2[u]+=1LL*a[u]*fcnt.query(a[u]+1,n+1)+fsum.query(a[u]);
        }
        if(del){
            for(int i=tin[u];i<=tout[u];i++)update(pos[i],-1);
        }
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        tin[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        hv[u]=-1;
        for(auto v:adj2[u])if(v!=p){
            dfs2(v,u);
            sz[u]+=sz[v];
            if(hv[u]==-1||sz[v]>sz[hv[u]])hv[u]=v;
        }
        tout[u]=timer;
    };
    auto update2=[&](int u,int v){
        fcnt.update(mex2[u],v);
        fsum.update(mex2[u],v*mex2[u]);
    };
    function<void(int,int,bool)> sack2=[&](int u,int p,bool del){
        for(auto v:adj2[u])if(v!=p&&v!=hv[u])sack2(v,u,true);
        if(hv[u]!=-1)sack2(hv[u],u,false);
        update2(u,+1);
        for(auto v:adj2[u])if(v!=p&&v!=hv[u]){
            for(int i=tin[v];i<=tout[v];i++)update2(pos[i],+1);
        }
        if(a[u]>mex1[u]){
            dp2[u]+=1LL*a[u]*fcnt.query(a[u]+1,n+1)+fsum.query(a[u])-sz[u]*mex1[u];
            ans=max(ans,dp2[u]-dp[u]);
        }
        if(del){
            for(int i=tin[u];i<=tout[u];i++)update2(pos[i],-1);
        }
    };
    dfs(0,-1);
    sack1(0,-1,true);
    for(auto x:rt){
        if(x==-1)continue;
        timer=-1;
        dfs2(x,-1);
        sack2(x,-1,true);
    }
    cout << ans+dp[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}