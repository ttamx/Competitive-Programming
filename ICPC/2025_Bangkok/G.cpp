#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
ll a[N][3],dp[N][8];
vector<pair<int,int>> adj[N];
ll ans=0;

void dfs(int u,int p){
    for(int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            dp[u][i]+=a[u][j]*((i>>j&1)?1:-1);
        }
    }
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        for(int i=0;i<8;i++){
            ans=max(ans,dp[u][i]+dp[v][i^7]+w);
        }
        for(int i=0;i<8;i++){
            dp[u][i]=max(dp[u][i],dp[v][i]+w);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<3;j++){
            cin >> a[i][j];
        }
    }
    dfs(1,0);
    cout << ans << "\n";
}