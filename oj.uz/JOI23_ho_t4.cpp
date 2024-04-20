#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int a[N],pa[N],sz[N],hv[N],lv[N],hd[N],ord[N],fa[N];
vector<int> adj[N];
long long dp[N];

void dfs(int u,int p=0){
    pa[u]=p;
    sz[u]=1;
    lv[u]=lv[p]+1;
    for(auto v:adj[u])if(v!=p){
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

int dist(int u,int v){
    return lv[u]+lv[v]-2*lv[lca(u,v)];
}

int fp(int u){
    return fa[u]=fa[u]==u?u:fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1);
    iota(fa+1,fa+n+1,1);
    iota(ord+1,ord+n+1,1);
    sort(ord+1,ord+n+1,[&](int i,int j){
        return a[i]<a[j];
    });
    for(int i=1;i<=n;i++){
        int u=ord[i];
        for(auto v:adj[u])if(a[u]>a[v]){
            v=fp(v);
            dp[u]=max(dp[u],dp[v]+dist(u,v));
            fa[v]=u;
        }
    }
    cout << dp[ord[n]];
}