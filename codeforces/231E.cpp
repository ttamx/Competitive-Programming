#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int MOD=1e9+7;

int n,m,q;
vector<pair<int,int>> edges;
vector<int> adj[N],adj2[N];
int disc[N],cyc[N],cnt[N];
int timer;
int par[N],jump[N],dep[N];
int pw[N];

void dfs(int u,int p){
    disc[u]=++timer;
    cyc[u]=u;
    for(auto v:adj[u]){
        if(v==p)continue;
        if(!disc[v]){
            dfs(v,u);
            if(cyc[v]!=v){
                assert(cyc[u]==u);
                cyc[u]=cyc[v];
            }
        }else if(disc[v]<disc[u]){
            assert(cyc[u]==u);
            cyc[u]=v;
        }
    }
}

void dfs2(int u){
    for(auto v:adj2[u]){
        if(v==par[u])continue;
        par[v]=u;
        dep[v]=dep[u]+1;
        jump[v]=dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]?jump[jump[u]]:u;
        cnt[v]+=cnt[u];
        dfs2(v);
    }
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]!=dep[v])u=dep[jump[u]]>=dep[v]?jump[u]:par[u];
    while(u!=v){
        if(jump[u]!=jump[v])u=jump[u],v=jump[v];
        else u=par[u],v=par[v];
    }
    return u;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    edges.resize(m);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    for(auto [u,v]:edges){
        u=cyc[u],v=cyc[v];
        if(u==v)continue;
        adj2[u].emplace_back(v);
        adj2[v].emplace_back(u);
    }
    int root=0;
    for(int i=1;i<=n;i++){
        if(cyc[i]==i){
            root=i;
        }else{
            cnt[cyc[i]]=1;
        }
    }
    assert(root!=0);
    par[root]=jump[root]=root;
    dfs2(root);
    par[root]=0;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%MOD;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        u=cyc[u],v=cyc[v];
        int x=lca(u,v);
        cout << pw[cnt[u]+cnt[v]-cnt[x]-cnt[par[x]]] << "\n";
    }
}