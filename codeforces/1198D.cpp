#include<bits/stdc++.h>

using namespace std;

const int N=55;

int n;
int a[N][N],b[N][N];
int dp[N][N][N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=1;j<=n;j++){
            a[i][j]=b[i][j]=(s[j-1]=='#');
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]+=a[i][j-1];
            b[i][j]+=b[i-1][j];
        }
    }
    for(int sx=1;sx<=n;sx++){
        for(int xl=1,xr=sx;xr<=n;xl++,xr++){
            for(int sy=1;sy<=n;sy++){
                for(int yl=1,yr=sy;yr<=n;yl++,yr++){
                    dp[xl][xr][yl][yr]=max(xr-xl,yr-yl)+1;
                    for(int i=xl;i<=xr;i++){
                        if(a[i][yr]-a[i][yl-1]==0){
                            dp[xl][xr][yl][yr]=min(dp[xl][xr][yl][yr],dp[xl][i-1][yl][yr]+dp[i+1][xr][yl][yr]);
                        }
                    }
                    for(int i=yl;i<=yr;i++){
                        if(b[xr][i]-b[xl-1][i]==0){
                            dp[xl][xr][yl][yr]=min(dp[xl][xr][yl][yr],dp[xl][xr][yl][i-1]+dp[xl][xr][i+1][yr]);
                        }
                    }
                }
            }
        }
    }
    cout << dp[1][n][1][n];
}