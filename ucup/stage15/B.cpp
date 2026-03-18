#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<vector<ll>>> dp(n+1,vector<vector<ll>>(n+1,vector<ll>(n+1)));
    dp[0][0][0]=1;
    for(auto x:s){
        vector<vector<vector<ll>>> ndp(n+1,vector<vector<ll>>(n+1,vector<ll>(n+1)));
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                for(int k=0;k<=n;k++){
                    if(x=='u'||x=='?'){
                        if(j>=1&&k+1<=n){
                            ndp[i][j-1][k+1]=(ndp[i][j-1][k+1]+dp[i][j][k])%MOD;
                        }else if(i+1<=n){
                            ndp[i+1][j][k]=(ndp[i+1][j][k]+dp[i][j][k])%MOD;
                        }
                    }
                    if(x=='c'||x=='?'){
                        if(j+1<=n&&i>=1){
                            ndp[i-1][j+1][k]=(ndp[i-1][j+1][k]+dp[i][j][k])%MOD;
                        }else if(j+2<=n&&k>=1){
                            ndp[i][j+2][k-1]=(ndp[i][j+2][k-1]+dp[i][j][k])%MOD;
                        }
                    }
                    if(x=='p'||x=='?'){
                        if(k>=1){
                            ndp[i][j][k-1]=(ndp[i][j][k-1]+dp[i][j][k])%MOD;
                        }
                    }
                }
            }
        }
        dp=move(ndp);
    }
    cout << dp[0][0][0] << "\n";
}