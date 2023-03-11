#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD=1e9+7;

int n,k;
ll dp[105][105];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
    	dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+min(k,i-1)+min(k,j-1))%MOD;
    	for(int m=1;m<=min(k,i-1);++m)dp[i][j]=(dp[i][j]+dp[i-m-1][j-1])%MOD;
    	for(int m=1;m<=min(k,j-1);++m)dp[i][j]=(dp[i][j]+dp[i-1][j-m-1])%MOD;
    }
    cout << dp[n][n];
}

