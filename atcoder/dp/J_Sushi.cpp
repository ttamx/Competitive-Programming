#include<bits/stdc++.h>

using namespace std;

typedef long double db;

const int N=305;

int n;
int cnt[4];
db dp[N][N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0,x;i<n;i++)cin >> x,cnt[x]++;
    for(int i=0;i<=n;i++){
        for(int j=0;i+j<=n;j++){
            for(int k=0;i+j+k<=n;k++){
                if(i==0&&j==0&&k==0)continue;
                db x=0,y=0,z=0;
                if(i>0)x=dp[k][j+1][i-1]*i/n;
                if(j>0)y=dp[k+1][j-1][i]*j/n;
                if(k>0)z=dp[k-1][j][i]*k/n;
                dp[k][j][i]=1.0*n*(x+y+z+1)/(i+j+k);
            }
        }
    }
    cout << setprecision(10) << dp[cnt[1]][cnt[2]][cnt[3]];
}