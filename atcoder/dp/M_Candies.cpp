#include<bits/stdc++.h>

using namespace std;

const int N=105;
const int K=1e5+5;
const int mod=1e9+7;

int n,k;
int a[N],dp[N][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=0;j<=k;j++){
            sum+=dp[i-1][j];
            if(sum>=mod)sum-=mod;
            if(j>a[i]){
                sum-=dp[i-1][j-a[i]-1];
                if(sum<0)sum+=mod;
            }
            dp[i][j]=sum;
        }
    }
    cout << dp[n][k];
}