#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int sz[N];
vector<int> adj[N];

int dfssz(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p)sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&sz[v]*2>cnt)return centroid(v,cnt,u);
    return u;
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
    cout << centroid(1,dfssz(1));
}