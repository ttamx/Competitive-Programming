#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,f,k;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;++i){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> f;
    vector<int> p(f+1);
    for(int i=1;i<=f;++i){
        cin >> p[i];
    }
    vector<bool> car(n+1,true);
    cin >> k;
    for(int i=1;i<=k;++i){
        int x;
        cin >> x;
        car[x]=false;
    }
    vector<int> dist(n+1);
    queue<int> q;
    q.emplace(1);
    dist[1]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u])if(!dist[v]){
            dist[v]=dist[u]+1;
            q.emplace(v);
        }
    }
    for(auto i:dist)cout << i << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}