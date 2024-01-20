#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n;
int sz[N];
vector<int> adj[N],comp;

int dfssz(int u,int p=0){
    sz[u]=(adj[u].size()<2);
    for(auto v:adj[u])if(v!=p)sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,int p=0){
    if(adj[u].size()==1)comp.emplace_back(u);
    for(auto v:adj[u])if(v!=p)dfs(v,u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int c=centroid(1,dfssz(1));
    dfs(c);
    comp.emplace_back(c);
    int ans=comp.size()/2;
    cout << ans << "\n";
    for(int i=0;i<ans;i++)cout << comp[i] << " " << comp[i+ans] << "\n";
}