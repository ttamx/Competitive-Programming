#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int l,w,n;
    cin >> l >> w >> n;
    vector<vector<int>> dp(l+2,vector<int>(w+2));
    for(int i=0;i<n;i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        a++,b++;
        dp[a][b]++;
        dp[a][d+1]--;
        dp[c+1][b]--;
        dp[c+1][d+1]++;
    }
    for(int i=1;i<=l;i++)for(int j=1;j<=w;j++)dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
    for(int i=1;i<=l;i++)for(int j=1;j<=w;j++)dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
    int ans=0;
    for(int i=3;i<=l;i++)for(int j=3;j<=w;j++)if(dp[i][j]-dp[i-3][j]-dp[i][j-3]+dp[i-3][j-3]==0)ans++;
    cout << ans;
}