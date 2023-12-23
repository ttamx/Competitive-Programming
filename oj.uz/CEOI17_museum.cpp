#include<bits/stdc++.h>

using namespace std;

const int N=10005;
const int inf=1e9;

int n,k,x;
vector<pair<int,int>> adj[N];
int dp[2][N][N];
int sz[N];

void dfs(int u,int p=-1){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p){
        dfs(v,u);
        for(int i=sz[u];i>=0;i--){
            for(int j=sz[v];j>=0;j--){
                dp[0][u][i+j]=min(dp[0][u][i+j],dp[0][u][i]+dp[0][v][j]+w*2);
                dp[1][u][i+j]=min(dp[1][u][i+j],dp[1][u][i]+dp[0][v][j]+w*2);
                dp[1][u][i+j]=min(dp[1][u][i+j],dp[0][u][i]+dp[1][v][j]+w);
            }
        }
        sz[u]+=sz[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> x;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=1;i<=n;i++)for(int j=2;j<=n;j++)dp[0][i][j]=dp[1][i][j]=inf;
    dfs(x);
    cout << dp[1][x][k];
}