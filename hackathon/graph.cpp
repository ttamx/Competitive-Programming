#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m;
vector<pair<int,int>> adj[N];//{next_node,dist}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
}