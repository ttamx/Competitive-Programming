#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
bool cant;
int sz[N];
bool used[N];
char ans[N];
vector<int> adj[N];

void dfs(int u,int p){
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

int centroid(int u,int p,int cnt){
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        if(sz[v]*2>cnt)return centroid(v,u,cnt);
    }
    return u;
}

void sol(int u,int l){
    if(l>=26){
        cant=true;
        return;
    }
    dfs(u,-1);
    int c=centroid(u,-1,sz[u]);
    ans[c]='A'+l;
    used[c]=true;
    for(auto v:adj[c]){
        if(used[v])continue;
        sol(v,l+1);
    }
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
    sol(1,0);
    if(cant)cout << "Impossible!";
    else for(int i=1;i<=n;i++)cout << ans[i] << ' ';
}