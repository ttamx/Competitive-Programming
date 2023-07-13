#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int deg[N],dp[N];
vector<int> adj[N];
queue<int> q;
int ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        deg[v]++;
    }
    for(int i=1;i<=n;i++)if(deg[i]==0)q.emplace(i);
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        for(auto v:adj[u]){
            dp[v]=max(dp[v],dp[u]+1);
            if(--deg[v]==0)q.emplace(v);
        }
    }
    for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
    cout << ans;
}