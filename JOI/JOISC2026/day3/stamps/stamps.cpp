#include<bits/stdc++.h>

using namespace std;

const int N=4e5+5;

int n,k;
int a[N];
vector<int> adj[N];
int sz[N];
bool vis[N];
int ans[N],b[N],c[N];
int max_dep;

int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!vis[v])sz[u]+=dfs_sz(v,u);
    return sz[u];
}

int centroid(int u,int p,int c){
    for(auto v:adj[u])if(v!=p&&!vis[v]&&sz[v]*2>c)return centroid(v,u,c);
    return u;
}

int dfs_dep(int u,int p){
    int res=0;
    for(auto v:adj[u])if(v!=p&&!vis[v])res=max(res,1+dfs_dep(v,u));
    return res;
}

void dfs_fill(int u,int p,int d,int t){
    t=min(t,max(0,a[u]-d));
    int l=t,r=k-d;
    if(l<=r&&l<=max_dep){
        b[l]++;
        if(r<max_dep)b[r+1]--;
    }
    c[d]++;
    for(auto v:adj[u])if(v!=p&&!vis[v])dfs_fill(v,u,d+1,t);
}

void dfs_ans(int u,int p,int d,int t){
    t=min(t,d+a[u]);
    if(t>d){
        ans[u]+=b[d];
    }else if(k-d>=0){
        ans[u]+=c[min(k-d,max_dep)];
    }
    for(auto v:adj[u])if(v!=p&&!vis[v])dfs_ans(v,u,d+1,t);
}

void decom(int u){
    u=centroid(u,0,dfs_sz(u,0));
    vis[u]=true;
    max_dep=dfs_dep(u,0);
    dfs_fill(u,0,0,n);
    for(int i=1;i<=max_dep;i++)b[i]+=b[i-1];
    for(int i=1;i<=max_dep;i++)c[i]+=c[i-1];
    dfs_ans(u,0,0,n);
    for(int i=0;i<=max_dep;i++)b[i]=0;
    for(int i=0;i<=max_dep;i++)c[i]=0;
    for(auto v:adj[u])if(!vis[v]){
        max_dep=dfs_dep(v,0)+1;
        dfs_fill(v,0,1,a[u]);
        for(int i=1;i<=max_dep;i++)b[i]+=b[i-1];
        for(int i=1;i<=max_dep;i++)c[i]+=c[i-1];
        for(int i=0;i<=max_dep;i++)b[i]=-b[i];
        for(int i=0;i<=max_dep;i++)c[i]=-c[i];
        dfs_ans(v,0,1,n);
        for(int i=0;i<=max_dep;i++)b[i]=0;
        for(int i=0;i<=max_dep;i++)c[i]=0;
    }
    for(auto v:adj[u])if(!vis[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]>k)a[i]=n;
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}