#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int mod=1e9+7;

int n,m;
char a[N][N];
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> a[i][j];
    dp[0][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='#')continue;
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
            if(dp[i][j]>=mod)dp[i][j]-=mod;
        }
    }
    cout << dp[n][m];
}