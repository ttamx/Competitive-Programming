#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=205;
const int M=6005;

int n,m,k;
int dp[N][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    m=n*30;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=-1e9;
        }
    }
    dp[0][0]=0;
    for(int t=0;t<n;t++){
        ll x;
        cin >> x;
        int c2=0,c5=0;
        while(x%2==0){
            x/=2;
            c2++;
        }
        while(x%5==0){
            x/=5;
            c5++;
        }
        for(int i=k;i>=1;i--){
            for(int j=c5;j<=m;j++){
                dp[i][j]=max(dp[i][j],dp[i-1][j-c5]+c2);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,min(i,dp[k][i]));
    }
    cout << ans << "\n";
}