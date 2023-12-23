#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k;
vector<int> adj[N];
int sz[N];
bool used[N];
long long ans=0;
int cnt[N];
vector<int> res[N];

int dfssz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,vector<int> &vec,int d=1,int p=-1){
    if(d>k)return;
    vec.emplace_back(d);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,vec,d+1,u);
}

void decom(int u){
    u=centroid(u,dfssz(u));
    used[u]=true;
    cnt[0]=1;
    for(auto v:adj[u]){
        if(used[v])continue;
        dfs(v,res[v]);
        for(auto d:res[v])ans+=cnt[k-d];
        for(auto d:res[v])cnt[d]++;
    }
    for(auto v:adj[u]){
        if(used[v])continue;
        for(auto d:res[v])cnt[d]--;
        res[v].clear();
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
    decom(1);
    cout << ans;
}