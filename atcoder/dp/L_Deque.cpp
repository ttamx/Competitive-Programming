#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<vector<ll>>> dp(2,vector<vector<ll>>(n+1,vector<ll>(n+1)));
    for(int i=1;i<=n;i++)dp[0][i][i]=a[i];
    for(int i=1;i<=n;i++)dp[1][i][i]=-a[i];
    for(int sz=2;sz<=n;sz++){
        for(int l=1,r=l+sz-1;r<=n;l++,r++){
            dp[0][l][r]=max(dp[1][l][r-1]+a[r],dp[1][l+1][r]+a[l]);
            dp[1][l][r]=min(dp[0][l][r-1]-a[r],dp[0][l+1][r]-a[l]);
        }
    }
    cout << dp[0][1][n];
}