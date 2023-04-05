#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k,n;
    cin >> k >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    a.emplace_back(-2e9);
    sort(a.begin(),a.end());
    vector<vector<int>> dp(n+1,vector<int>(k+1));
    for(int i=0;i<2;i++)for(int j=1;j<=k;j++)dp[i][j]=2e9;
    for(int i=2;i<=n;i++)for(int j=1;j<=k;j++)dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+a[i]-a[i-1]);
    cout << dp[n][k];
}