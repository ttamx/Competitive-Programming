#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> dp(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++){
        int p,w;
        cin >> p >> w;
        for(int j=1;j<=m;j++){
            if(j<w)dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            else dp[i][j]=max({dp[i-1][j],dp[i][j-1],dp[i-1][j-w]+p});
        }
    }
    cout << dp[n][m];
}