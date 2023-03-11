#include<bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> t3;

int n;
bool vis[150];
vector<pair<int,int>> adj[150];
priority_queue<t3,vector<t3>,greater<t3>> pq;

void dfs(int u){
    vis[u]=true;
    for(int i=1;i<=n;++i){
        if(vis[i])continue;
        cout << "?";
        for(int j=1;j<=n;++j){
            cout << " ";
            if(i==j)cout << 2;
            else if(j==u)cout << 1;
            else cout << 0;
        }
        cout << endl;
        int w;
        cin >> w;
        adj[u].emplace_back(i,w);
        adj[i].emplace_back(u,w);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    while(!pq.empty()){
        auto [d,u,p]=pq.top();
        pq.pop();
        if(vis[u])continue;

        dfs(u);
    }
}
