#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    void update(int l,int r,ll v){
        update(l,v);
        update(r+1,-v);
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    ll query(int l,int r){
        return query(r)-query(l-1);
    }
}f,f2;

int n,q;
vector<int> adj[N];
int sz[N],hv[N],dep[N],hd[N],disc[N],par[N];
int u[N],v[N],w[N];
int timer=0;

void dfs(int u,int p){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p){
        par[v]=u;
        dep[v]=dep[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p){
    disc[u]=++timer;
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
}

void update(int i,ll val){
    f.update(1,val*sz[v[i]]);
    f.update(disc[v[i]],disc[v[i]]+sz[v[i]]-1,val*(n-2*sz[v[i]]));
    f2.update(disc[v[i]],val*sz[v[i]]);
}

ll query(int u,int v){
    ll res=0;
    while(hd[u]!=hd[v]){
        if(dep[hd[u]]<dep[hd[v]])swap(u,v);
        res-=f2.query(disc[hd[u]],disc[u]);
        u=par[hd[u]];
    }
    if(u!=v){
        if(dep[u]>dep[v])swap(u,v);
        res-=f2.query(disc[u]+1,disc[v]);
    }
    res+=f.query(disc[u]);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n-1;i++){
        cin >> u[i] >> v[i] >> w[i];
        adj[u[i]].emplace_back(v[i]);
        adj[v[i]].emplace_back(u[i]);
    }
    dfs(1,0);
    hld(1,0);
    for(int i=1;i<=n-1;i++){
        if(dep[u[i]]>dep[v[i]]){
            swap(u[i],v[i]);
        }
        update(i,w[i]);
    }
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int i,x;
            cin >> i >> x;
            update(i,x-w[i]);
            w[i]=x;
        }else{
            int u,v;
            cin >> u >> v;
            cout << query(u,v) << "\n";
        }
    }
}