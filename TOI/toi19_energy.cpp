#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=305;
const int mod=1e9+7;
const int K=10;

int n,k,d;
int a[N],qs[N];
ll dp[K][N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> d;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)dp[0][i][j]=1;
    for(int i=1;i<k;i++){
        for(int l=1;l<=n;l++){
            for(int r=l+1;r<=n;r++){
                for(int m=l;m<r;m++){
                    if(abs((qs[r]-qs[m])-(qs[m]-qs[l-1]))<=d){
                        dp[i][l][r]+=dp[i-1][l][m]*dp[i-1][m+1][r];
                        dp[i][l][r]%=mod;
                    }
                }
            }
        }
    }
    cout << dp[k-1][1][n];
}