#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,m;
bool vis[N];
vector<int> adj[N];
queue<pair<int,int>> q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        adj[i].emplace_back(i-1);
        adj[i-1].emplace_back(i);
    }
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        l--;
        adj[l].emplace_back(r);
        adj[r].emplace_back(l);
    }
    q.emplace(0,0);
    vis[0]=true;
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop();
        if(u==n){
            cout << d;
            return 0;
        }
        for(auto v:adj[u]){
            if(vis[v])continue;
            vis[v]=true;
            q.emplace(d+1,v);
        }
    }
}