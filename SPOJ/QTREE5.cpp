#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int sz[N],pc[N],lv[N],pa[N][20];
bool used[N],col[N];
vector<int> adj[N];
set<pair<int,int>> ms[N];

void pre(int u=1,int p=0){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u])if(v!=p)pre(v,u);
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int dist(int u,int v){
    return lv[u]+lv[v]-2*lv[lca(u,v)];
}

int dfs(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
    return sz[u];
}

int centroid(int u,int req,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>req)return centroid(v,req,u);
    return u;
}

void build(int u=1,int p=0){
    u=centroid(u,dfs(u));
    used[u]=true;
    pc[u]=p;
    for(auto v:adj[u])if(!used[v])build(v,u);
}

void add(int st,int u){
    if(u==0)return;
    ms[u].insert({dist(st,u),st});
    add(st,pc[u]);
}

void del(int st,int u){
    if(u==0)return;
    ms[u].erase({dist(st,u),st});
    del(st,pc[u]);
}

int query(int st,int u){
    if(u==0)return n;
    int res;
    if(ms[u].empty())res=n;
    else res=ms[u].begin()->first+dist(st,u);
    return min(res,query(st,pc[u]));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pre();
    build();
    cin >> q;
    while(q--){
        int o,x;
        cin >> o >> x;
        if(o){
            int ans=query(x,x);
            if(ans>=n)ans=-1;
            cout << ans << '\n';
        }else{
            col[x]^=1;
            if(col[x])add(x,x);
            else del(x,x);
        }
    }
}