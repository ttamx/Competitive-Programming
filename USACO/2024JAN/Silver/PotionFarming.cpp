#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,leaf;
int p[N];
vector<int> adj[N];
int cnt[N],lf[N];

void dfs(int u,int p=0){
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        lf[u]+=lf[v];
        cnt[u]+=cnt[v];
    }
    if(!lf[u])lf[u]=1;
    cnt[u]=min(cnt[u],lf[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=2;i<=n;i++)if(adj[i].size()==1)leaf++;
    for(int i=1;i<=leaf;i++)cnt[p[i]]++;
    dfs(1);
    cout << cnt[1];
}