#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int MOD=1e9+7;

int n;
ll k;
ll dp[N][3][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    dp[1][1][1]=k;
    dp[2][2][1]=k*k%MOD;
    dp[3][0][0]=k;
    for(int i=4;i<=n;i++){
        for(int j=0;j<3;j++){
            dp[i][j][0]=(dp[i-3][j][0]+dp[i-3][j][1])*(k-1)%MOD;
            if(j>0){
                dp[i][j][1]=(dp[i-1][j-1][0]*(k-1)+dp[i-1][j-1][1]*k)%MOD;
            }
        }
    }
    cout << (dp[n][n%3][0]+dp[n][n%3][1])%MOD;
}