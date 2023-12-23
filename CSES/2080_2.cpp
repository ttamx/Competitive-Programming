#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k;
vector<int> adj[N];
int sz[N];
bool used[N];
int cnt[N];
long long ans;
vector<int> vec[N];

int dfssz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,int d,int p,int rt){
    vec[rt].emplace_back(d);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,d+1,u,rt);
}

void decom(int u){
    u=centroid(u,dfssz(u));
    used[u]=true;
    cnt[0]++;
    for(auto v:adj[u])if(!used[v]){
        dfs(v,1,u,v);
        for(auto d:vec[v])if(d<=k)ans+=cnt[k-d];
        for(auto d:vec[v])cnt[d]++;
    }
    cnt[0]--;
    for(auto v:adj[u])if(!used[v]){
        for(auto d:vec[v])cnt[d]--;
        vec[v].clear();
    }
    for(auto v:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin  >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    cout << ans;
}