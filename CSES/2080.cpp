#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k,mxl;
long long ans;
bool used[N];
int sz[N],cnt[N];
vector<int> adj[N];

void dfs(int u,int p){
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

void dfsans(int u,int p,int l){
    if(l>k)return;
    ans+=cnt[k-l];
    mxl=max(mxl,l);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfsans(v,u,l+1);
    }
}

void dfscnt(int u,int p,int l){
    if(l>k)return;
    cnt[l]++;
    mxl=max(mxl,l);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfscnt(v,u,l+1);
    }
}

int centroid(int u,int p,int cnt){
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        if(sz[v]*2>cnt)return centroid(v,u,cnt);
    }
    return u;
}

void sol(int u){
    dfs(u,-1);
    u=centroid(u,-1,sz[u]);
    used[u]=true;
    mxl=0;
    for(auto v:adj[u]){
        if(used[v])continue;
        dfsans(v,u,1);
        dfscnt(v,u,1);
    }
    for(int i=1;i<=mxl;i++)cnt[i]=0;
    for(auto v:adj[u])if(!used[v])sol(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cnt[0]=1;
    sol(1);
    cout << ans;
}