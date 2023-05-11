#include<bits/stdc++.h>

using namespace std;

const int N=405;

int n,m,ans;
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=1e9;
    for(int i=0;i<m;i++){
        int u,v,c;
        cin >> u >> v >> c;
        dp[u][v]=dp[v][u]=min(dp[u][v],c);
    }
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    for(int i=2;i<=n;i++)ans+=dp[i-1][i];
    cout << ans;
}