#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

using ll = long long;

const int N=505;

ll dp[N][N][3][3],ndp[N][N][3][3];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,a,b,c;
    cin >> n >> a >> b >> c;
    if(a>=2)dp[2][1][0][0]=2;
    if(b>=2)dp[1][2][1][1]=2;
    if(c>=2)dp[1][1][2][2]=2;
    for(int t=4;t<n;t++){
        for(int i=1;i<=a;i++){
            for(int j=1;j<=b;j++){
                if(t-i-j>c)continue;
                for(int x=0;x<3;x++){
                    for(int y=0;y<3;y++){
                        if(y!=0&&i+1<=a)ndp[i+1][j][x][0]+=dp[i][j][x][y];
                        if(y!=1&&j+1<=b)ndp[i][j+1][x][1]+=dp[i][j][x][y];
                        if(y!=2&&t+1-i-j<=c)ndp[i][j][x][2]+=dp[i][j][x][y];
                    }
                }
            }
        }
        for(int i=1;i<=a;i++){
            for(int j=1;j<=b;j++){
                for(int x=0;x<3;x++){
                    for(int y=0;y<3;y++){
                        dp[i][j][x][y]=ndp[i][j][x][y]%MOD;
                        ndp[i][j][x][y]=0;
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i!=j){
                ans=(ans+dp[a][b][i][j])%MOD;
            }
        }
    }
    cout << ans << "\n";
}