#include<bits/stdc++.h>

using namespace std;

const int N=5005;
const int MOD=2553;

int n,k,ans;
int dp[2][N];

int pw3(int x){
    return x*x%MOD*x%MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=0;j<=n;j++){
            dp[i&1][j]=sum;
            sum+=dp[i&1^1][j];
            if(sum>=MOD)sum-=MOD;
            if(j>=k)sum-=dp[i&1^1][j-k];
            if(sum<0)sum+=MOD;
        }
        ans+=pw3(dp[i&1][n]);
        if(ans>=MOD)ans-=MOD;
    }
    cout << ans;
}