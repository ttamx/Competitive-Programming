#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int cp[N],sz[N],lv[N],mn[N];
int pa[N][20];
bool used[N];
vector<int> adj[N];

void predfs(int u,int p=0){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<=17;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u])if(v!=p)predfs(v,u);
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=17;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=17;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int dist(int a,int b){
    return lv[a]+lv[b]-2*lv[lca(a,b)];
}

int dfs(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
    return sz[u];
}

int getcentroid(int u,int req,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>req)return getcentroid(v,req,u);
    return u;
}

void buildcentroid(int u,int p=0){
    u=getcentroid(u,dfs(u));
    used[u]=true;
    cp[u]=p;
    for(auto v:adj[u])if(!used[v])buildcentroid(v,u);
}

void updateup(int st){
    int u=st;
    while(u){
        mn[u]=min(mn[u],dist(u,st));
        u=cp[u];
    }
}

int queryup(int st){
    int res=n,u=st;
    while(u){
        res=min(res,mn[u]+dist(st,u));
        u=cp[u];
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    predfs(1);
    buildcentroid(1);
    for(int i=1;i<=n;i++)mn[i]=n;
    updateup(1);
    while(m--){
        int t,v;
        cin >> t >> v;
        if(t==1)updateup(v);
        else cout << queryup(v) << '\n';
    }
}