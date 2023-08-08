#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;

int n,k;
int c[N];
vector<int> adj[N];
int sz[N];
bool used[N];
vector<p2> add[N];
int ans[N];

struct fenwick{
    int t[N];
    void add(int i,int v){
        i++;
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        i++;
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int dfssz(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,int rt,int d=1,int p=0){
    add[rt].emplace_back(d,u);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,rt,d+1,u);
}

void decom(int u){
    u=centroid(u,dfssz(u));
    used[u]=true;
    f.add(0,c[u]);
    for(auto v:adj[u]){
        if(used[v])continue;
        dfs(v,v);
        for(auto [i,j]:add[v])f.add(i,c[j]);
    }
    ans[u]+=f.read(k);
    for(auto v:adj[u]){
        if(used[v])continue;
        for(auto [i,j]:add[v])f.add(i,-c[j]);
        for(auto [i,j]:add[v])if(k>=i)ans[j]+=f.read(k-i);
        for(auto [i,j]:add[v])f.add(i,c[j]);
    }
    f.add(0,-c[u]);
    for(auto v:adj[u]){
        if(used[v])continue;
        for(auto [i,j]:add[v])f.add(i,-c[j]);
        add[v].clear();
    }
    for(auto v:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)cin >> c[i];
    decom(1);
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}