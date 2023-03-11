#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k1,k2,mxl;
long long ans;
bool used[N];
int sz[N],cnt[N];
vector<int> adj[N];

struct fenwick{
    int f[N];
    void add(int i,int v){
        i++;
        while(i<N)f[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        i++;
        while(i)res+=f[i],i-=i&-i;
        return res;
    }
}f;

void dfs(int u,int p){
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

void dfsans(int u,int p,int l){
    if(l>k2)return;
    ans+=f.read(k2-l)-f.read(max(-1,k1-l-1));
    mxl=max(mxl,l);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfsans(v,u,l+1);
    }
}

void dfscnt(int u,int p,int l){
    if(l>k2)return;
    f.add(l,1);
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
    for(int i=1;i<=mxl;i++)f.add(i,-cnt[i]),cnt[i]=0;
    for(auto v:adj[u])if(!used[v])sol(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k1 >> k2;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    f.add(0,1);
    sol(1);
    cout << ans;
}