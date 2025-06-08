#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=505;
const int M=1<<20;

int n,m;
int a[N][N];
bool good[N][N];
uint32_t hsh[N];
mint dp[N][N],dp2[N][N];
bool f[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int pos=0;
        for(int j=1;j<=n;j++){
            int x;
            cin >> x;
            a[i][x]=j;
            if(!pos)pos=x;
        }
        rotate(a[i]+1,a[i]+pos,a[i]+n+1);
    }
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            good[l][r]=true;
        }
    }
    for(int s=2;s<=n;s++){
        for(int i=2;i<=m;i++){
            for(int t=0;t<3;t++){
                for(int i=1;i<=n;i++)hsh[i]=rng()&(M-1);
                uint32_t sum=0;
                for(int j=1;j<s;j++)sum^=hsh[a[i][j]];
                for(int l=1,r=s;r<=n;l++,r++){
                    sum^=hsh[a[i][r]];
                    f[sum]=true;
                    sum^=hsh[a[i][l]];
                }
                sum=0;
                for(int j=1;j<s;j++)sum^=hsh[a[1][j]];
                for(int l=1,r=s;r<=n;l++,r++){
                    sum^=hsh[a[1][r]];
                    if(!f[sum]){
                        good[l][r]=false;
                    }
                    sum^=hsh[a[1][l]];
                }
                sum=0;
                for(int j=1;j<s;j++)sum^=hsh[a[i][j]];
                for(int l=1,r=s;r<=n;l++,r++){
                    sum^=hsh[a[i][r]];
                    f[sum]=false;
                    sum^=hsh[a[i][l]];
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        dp[i][i]=1;
        dp2[i][i]=1;
    }
    for(int s=2;s<=n;s++){
        for(int l=1,r=s;r<=n;l++,r++){
            if(good[l][r]){
                dp2[l][r]=dp[l][r-1]+dp[l+1][r];
                for(int m=l+1;m<r;m++){
                    dp2[l][r]+=dp[l][m-1]*dp[m+1][r];
                }
                dp[l][r]=dp2[l][r];
            }
            for(int m=l;m<r;m++){
                dp[l][r]+=dp[l][m]*dp2[m+1][r];
            }
        }
    }
    cout << dp[2][n] << "\n";
}