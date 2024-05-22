#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n;
char a[N],b[N];
int dp[N][3][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> (a+1) >> (b+1);
    for(int i=0;i<=n;i++)for(int j=0;j<3;j++)for(int k=0;k<2;k++)dp[i][j][k]=2*n;
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++)for(int j=0;j<3;j++)for(int k=0;k<3;k++)for(int tl=0;tl<2;tl++)for(int tr=0;tr<2;tr++){
        int v=a[i]-'0';
        if(k)v=k-1;
        if(tr)v^=1;
        if(v!=b[i]-'0')continue;
        dp[i][k][tr]=min(dp[i][k][tr],dp[i-1][j][tl]+(k&&j!=k)+(tl<tr));
    }
    int ans=n*2;
    for(int i=0;i<3;i++)for(int j=0;j<2;j++)ans=min(ans,dp[n][i][j]);
    cout << ans;
}