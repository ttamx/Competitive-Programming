#include<bits/stdc++.h>

using namespace std;

const int N=505;

int n,m,d;
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)dp[i][j]=1e9+1;
    for(int i=0;i<n;i++)dp[i][i]=0;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        dp[u][v]=min(dp[u][v],w);
        dp[v][u]=min(dp[v][u],w);
    }
    cin >> d;
    for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    int cnt=0,all=0;
    for(int i=0;i<n;i++)for(int j=0;j<i;j++){
        all++;
        if(dp[i][j]<=d)cnt++;
    }
    if(cnt==0){
        cout << "0/1";
        return 0;
    }
    int div=gcd(cnt,all);
    cout << cnt/div << '/' << all/div;
}