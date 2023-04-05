#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n;
int a[N],deg[N],dp[N];
vector<int> adj[N];
queue<int> q;
int ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> deg[i];
        if(deg[i]==0)q.emplace(i);
        for(int j=0;j<deg[i];j++){
            int u;
            cin >> u;
            adj[u].emplace_back(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        dp[u]+=a[u];
        ans=max(ans,dp[u]);
        for(auto v:adj[u]){
            dp[v]=max(dp[v],dp[u]);
            if(--deg[v]==0)q.emplace(v);
        }
    }
    cout << ans;
}