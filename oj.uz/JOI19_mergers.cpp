#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n,k;
pair<int,int> edge[N];
vector<int> adj[N],comp[N];
int sz[N],hv[N],lv[N],hd[N],pa[N];
int a[N],deg[N];
int fa[N];

int fp(int u){
    return fa[u]=fa[u]==u?u:fp(fa[u]);
}

void uni(int u,int v){
    fa[fp(u)]=fp(v);
}

void dfs(int u,int p=0){
    pa[u]=p;
    sz[u]=1;
    for(auto v:adj[u])if(v!=p){
        lv[v]=lv[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p=0){
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        u=pa[hd[u]];
    }
    return lv[u]<lv[v]?u:v;
}

void dfs2(int u,int p=0){
    for(auto v:adj[u])if(v!=p){
        dfs2(v,u);
        a[u]+=a[v];
        if(a[v])uni(u,v);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        auto &[u,v]=edge[i];
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        comp[x].emplace_back(i);
    }
    dfs(1);
    hld(1);
    for(int i=1;i<=k;i++){
        for(int j=1;j<comp[i].size();j++){
            int u=comp[i][j-1],v=comp[i][j];
            a[u]++,a[v]++,a[lca(u,v)]-=2;
        }
    }
    iota(fa+1,fa+n+1,1);
    dfs2(1);
    for(int i=1;i<n;i++){
        auto [u,v]=edge[i];
        u=fp(u),v=fp(v);
        if(u!=v)deg[u]++,deg[v]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans+=deg[i]==1;
    cout << (ans+1)/2;
}