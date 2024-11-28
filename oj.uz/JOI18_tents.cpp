#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3005;
const int MOD=1e9+7;

int h,w;
ll dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> h >> w;
    for(int i=0;i<=h;i++){
        dp[i][0]=1;
    }
    for(int i=0;i<=w;i++){
        dp[0][i]=1;
    }
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            dp[i][j]+=dp[i-1][j];
            dp[i][j]+=dp[i-1][j-1]*j*4;
            if(i>=2){
                dp[i][j]+=dp[i-2][j-1]*(i-1)*j;
            }
            if(j>=2){
                dp[i][j]+=dp[i-1][j-2]*(1LL*j*(j-1)/2);
            }
            dp[i][j]%=MOD;
        }
    }
    cout << (dp[h][w]-1+MOD)%MOD;
}