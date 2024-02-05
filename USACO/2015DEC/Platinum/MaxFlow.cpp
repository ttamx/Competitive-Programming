#include<bits/stdc++.h>

using namespace std;

const int N=50005;

int n,k;
vector<int> adj[N];
int sz[N],hv[N],lv[N],hd[N],pa[N],a[N];

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

void pull(int u,int p=0){
    for(auto v:adj[u])if(v!=p){
        pull(v,u);
        a[u]+=a[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1);
    for(int i=0;i<k;i++){
        int u,v;
        cin >> u >> v;
        int x=lca(u,v);
        a[u]++,a[v]++,a[x]--,a[pa[x]]--;
    }
    pull(1);
    cout << *max_element(a+1,a+n+1);
}