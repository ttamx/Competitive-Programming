#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k1,k2,mxl;
long long ans;
bool used[N];
int sz[N];
vector<int> adj[N],dist[N];

struct fenwick{
    int f[N];
    void add(int i,int v){
        i++;
        while(i<N)f[i]+=v,i+=i&-i;
    }
    int read(int i){
        i++;
        int res=0;
        while(i)res+=f[i],i-=i&-i;
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
    dist[rt].emplace_back(d);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,rt,d+1,u);
}

void decom(int u){
    u=centroid(u,dfssz(u));
    used[u]=true;
    f.add(0,1);
    for(auto v:adj[u]){
        if(used[v])continue;
        dfs(v,v);
        for(auto d:dist[v]){
            if(k2>=d)ans+=f.read(k2-d);
            if(k1>=d)ans-=f.read(k1-d);
        }
        for(auto d:dist[v])f.add(d,1);
    }
    f.add(0,-1);
    for(auto v:adj[u]){
        if(used[v])continue;
        for(auto d:dist[v])f.add(d,-1);
        dist[v].clear();
    }
    for(auto v:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k1 >> k2;
    k1--;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    cout << ans;
}