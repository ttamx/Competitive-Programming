#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
vector<int> adj[N];
int par[N],sz[N],hv[N],hd[N],disc[N],dep[N],pos[N];
int timer;
ll dp[N],sum[N];
vector<tuple<int,int,int>> qr1[N];
vector<tuple<int,int,int,int,int>> qr2[N];

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    ll query(int l,int r){
        return query(r)-query(l-1);
    }
}fw;

void dfs(int u){
    sz[u]=1;
    for(auto v:adj[u]){
        dep[v]=dep[u]+1;
        dfs(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u){
    disc[u]=++timer;
    pos[timer]=u;
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u]);
    for(auto v:adj[u])if(v!=hv[u])hld(v);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(dep[hd[u]]<dep[hd[v]])swap(u,v);
        u=par[hd[u]];
    }
    return dep[u]<dep[v]?u:v;
}

int jump(int u,int d){
    while(dep[hd[u]]>d)u=par[hd[u]];
    return pos[disc[u]-(dep[u]-d)];
}

ll query(int u,int v){
    ll res=sum[v];
    while(hd[v]!=hd[u]){
        int h=hd[v],p=par[h];
        res+=fw.query(disc[h],disc[v]-1);
        res+=sum[p]-dp[h];
        v=p;
    }
    res+=fw.query(disc[u],disc[v]-1);
    return res;
}

void dfs2(int u){
    for(auto v:adj[u])dfs2(v);
    dp[u]=sum[u];
    for(auto [v,vv,w]:qr1[u]){
        dp[u]=max(dp[u],sum[u]-dp[vv]+query(vv,v)+w);
    }
    for(auto [v1,v2,vv1,vv2,w]:qr2[u]){
        dp[u]=max(dp[u],sum[u]-dp[vv1]-dp[vv2]+query(vv1,v1)+query(vv2,v2)+w);
    }
    if(u==1)return;
    int p=par[u];
    if(u!=hv[p])fw.update(disc[p],dp[u]);
    sum[p]+=dp[u];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=2;i<=n;i++){
        cin >> par[i];
        adj[par[i]].emplace_back(i);
    }
    dfs(1);
    hld(1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        int x=lca(u,v);
        if(x==u){
            int vv=jump(v,dep[x]+1);
            qr1[u].emplace_back(v,vv,w);
        }else if(x==v){
            int uu=jump(u,dep[x]+1);
            qr1[v].emplace_back(u,uu,w);
        }else{
            int uu=jump(u,dep[x]+1);
            int vv=jump(v,dep[x]+1);
            qr2[x].emplace_back(u,v,uu,vv,w);
        }
    }
    dfs2(1);
    cout << dp[1] << "\n";
}