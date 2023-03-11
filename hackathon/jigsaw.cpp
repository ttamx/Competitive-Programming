#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const int mod=1e9+7;

int n;
ll dp[N][7];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    dp[0][6]=1;
    for(int i=1;i<=n;i++){
        dp[i][0]=(dp[i-1][2]+dp[i-1][4])%mod;
        dp[i][1]=(dp[i-1][0]+dp[i-1][2]+dp[i-1][5])%mod;
        dp[i][2]=(dp[i-1][0]+dp[i-1][3])%mod;
        dp[i][3]=(dp[i-1][4]+dp[i-1][5]+dp[i-1][6])%mod;
        if(i>1)dp[i][3]=(dp[i][3]+dp[i-2][6])%mod;
        dp[i][4]=(dp[i-1][3]+dp[i-1][5]+dp[i-1][6])%mod;
        if(i>1)dp[i][4]=(dp[i][4]+dp[i-2][6])%mod;
        dp[i][5]=dp[i-1][1];
        if(i>1)dp[i][5]=(dp[i][5]+2*dp[i-2][6])%mod;
        dp[i][6]=(dp[i][0]+dp[i][2]+dp[i-1][0]+dp[i-1][2]+2*dp[i-1][1])%mod;
        if(i>1)dp[i][6]=(dp[i][6]+3*dp[i-2][6])%mod;
    }
    cout << dp[n][6];
}