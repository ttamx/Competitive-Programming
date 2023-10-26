#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int M=3005;
const int inf=1e9;

int n;
int t[N];
int dp[N][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> t[i];
    for(int i=1;i<=n;i++){
        dp[i][0]=inf;
        for(int j=1;j<=3000;j++)dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+(t[i]!=j));
    }
    int ans=inf;
    for(int i=1;i<=3000;i++)ans=min(ans,dp[n][i]);
    cout << ans;
}