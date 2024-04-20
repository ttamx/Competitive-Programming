#include<bits/stdc++.h>

using namespace std;

const int N=505;

int n,m,q;
int a[N];
pair<int,int> dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]={a[i]+a[j],-2};
    for(int i=1,u,v,w;i<=m;i++){
        cin >> u >> v >> w;
        dp[u][v]=dp[v][u]=min(dp[u][v],{w,-2});
    }
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
        dp[i][j]=min(dp[i][j],{dp[i][k].first+dp[k][j].first,dp[i][k].second+dp[k][j].second});
    }
    for(int i=1,u,v;i<=q;i++){
        cin >> u >> v;
        cout << dp[u][v].first << ' ' << -dp[u][v].second << '\n';
    }
}