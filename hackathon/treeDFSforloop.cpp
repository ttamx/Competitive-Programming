#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
vector<int> adj[N];//{next_node,dist}
bool vis[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    stack<int> s;
    s.push(5);
    while(!s.empty()){
        int u=s.top();
        s.pop();
        if(vis[u]==true)continue;
        vis[u]=true;
        for(auto v:adj[u]){
            s.push(v);
        }
    }
}