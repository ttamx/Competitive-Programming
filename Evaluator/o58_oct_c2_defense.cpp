#include<bits/stdc++.h>

using namespace std;

int n,k;
int a[3005];
int dp[3005][3005];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;++i)cin >> a[i];
    for(int i=0;i<=k;++i)dp[k][i]=2e9;
    for(int i=1;i<=n;++i)for(int j=i+1;j<=k;++j)dp[k][k-j]=min(dp[k][k-j],a[i]+a[j]);
    for(int i=0;i<k-1;++i)for(int j=1;j+i<k-1&&k+j<=n;++j)dp[k+j][j+i]=dp[k][i];
    for(int i=k+1;i<=n+1;++i){
        dp[i][0]=2e9;
        for(int j=0;j<k-1;++j)dp[i][0]=min(dp[i][0],dp[i-1][j]);
        dp[i][0]+=a[i];
        for(int j=1;j<k-1&&i+j<=n;++j)dp[i+j][j]=dp[i][0];
    }
    cout << dp[n+1][0];
}