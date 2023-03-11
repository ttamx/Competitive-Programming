#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
vector<int> adj[N];//{next_node,dist}
int dep[N];

void dfs(int u,int p){
    dep[u]=dep[p]+1;
    cout << u << '\n';
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(5,-1);
}