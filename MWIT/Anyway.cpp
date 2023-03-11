#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int mod=1e6;

int n,m,k;
int dp[N][N];
bool a[N][N];

int main(){
    cin >> n >> m >> k;
    while(k--){
        int x,y;
        cin >> x >> y;
        a[x][y]=true;
    }
    if(!a[0][0])dp[0][0]=1;
    for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)if(!a[i][j])dp[i+1][j]+=dp[i][j],dp[i+1][j]%=mod,dp[i][j+1]+=dp[i][j],dp[i][j+1]%=mod;
    if(a[n][m])dp[n][m]=0;
    cout << dp[n][m];
}