#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
vector<int> adj[N];//{next_node,dist}
bool vis[N];
int dep[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<int> q;
    q.push(5);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(vis[u]==true)continue;
        vis[u]=true;
        for(auto v:adj[u]){
            q.push(v);
            dep[v]=dep[u]+1;
        }
        cout << u << '\n';
    }
}