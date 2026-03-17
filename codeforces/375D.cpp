#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int a[N],c[N];
int sz[N],hv[N],tin[N],tout[N],node[N],ans[N];
vector<int> adj[N];
vector<pair<int,int>> qr[N];
int timer;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

void upd(int i,int v){
    if(c[a[i]])f.update(c[a[i]],-1);
    c[a[i]]+=v;
    if(c[a[i]])f.update(c[a[i]],+1);
}

void dfs(int u,int p){
    tin[u]=++timer;
    node[timer]=u;
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
    tout[u]=timer;
}

void sack(int u,int p,bool del){
    for(auto v:adj[u])if(v!=p&&v!=hv[u])sack(v,u,true);
    if(hv[u])sack(hv[u],u,false);
    upd(u,+1);
    for(auto v:adj[u])if(v!=p&&v!=hv[u])for(int i=tin[v];i<=tout[v];i++)upd(node[i],+1);
    for(auto [k,i]:qr[u]){
        ans[i]=f.query(n)-f.query(k-1);
    }
    if(del)for(int i=tin[u];i<=tout[u];i++)upd(node[i],-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=0;i<q;i++){
        int v,k;
        cin >> v >> k;
        qr[v].emplace_back(k,i);
    }
    dfs(1,0);
    sack(1,0,false);
    for(int i=0;i<q;i++)cout << ans[i] << "\n";
}