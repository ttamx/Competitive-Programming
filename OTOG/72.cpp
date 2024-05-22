#include<bits/stdc++.h>

using namespace std;

const int N=105;

int n,m;
vector<pair<int,int>> adj[N];
int dp[N][N],mem[N];

void dfs(int u,int p){
    for(auto [v,w]:adj[u])if(v!=p){
        dfs(v,u);
        for(int i=0;i<=m;i++)mem[i]=dp[u][i];
        for(int i=1;i<=m;i++){
            for(int j=0;j<i;j++){
                dp[u][i]=max(dp[u][i],dp[v][j]+mem[i-j-1]+w);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(1,0);
    cout << dp[1][m];
}