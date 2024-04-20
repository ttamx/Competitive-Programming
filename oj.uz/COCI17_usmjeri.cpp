#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int MOD=1e9+7;

int n,m;
vector<int> adj[N];
vector<pair<int,int>> adj2[N];
int pa[N],lv[N],sz[N],hv[N],hd[N],top[N],col[N];
int ans=1;

void dfs(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p){
        pa[v]=u;
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

void link(int u,int p=0){
    for(auto v:adj[u])if(v!=p){
        link(v,u);
        top[u]=min(top[u],top[v]);
        if(top[v]<lv[u]){
            adj2[u].emplace_back(v,0);
            adj2[v].emplace_back(u,0);
        }
    }
}

bool check(int u,int p=0,int c=2){
    if(col[u])return col[u]==c;
    col[u]=c;
    for(auto [v,w]:adj2[u])if(v!=p){
        if(!check(v,u,c^w))return false;
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1);
    for(int i=1;i<=n;i++)top[i]=lv[i];
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        int a=lca(u,v);
        top[u]=min(top[u],lv[a]);
        top[v]=min(top[v],lv[a]);
        if(u!=a&&v!=a){
            adj2[u].emplace_back(v,1);
            adj2[v].emplace_back(u,1);
        }
    }
    link(1);
    for(int i=2;i<=n;i++)if(!col[i]){
        if(!check(i))ans=0;
        ans*=2;
        if(ans>=MOD)ans-=MOD;
    }
    cout << ans;
}