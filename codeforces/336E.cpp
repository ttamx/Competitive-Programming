#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

// so tough...

const int N=205;

int n,k;
mint dp[N][16];
mint ans=0;

void work1(){
    // big one
    for(int d=0;d<4;d++){
        int mask=1<<d;
        for(int i=k;i>=0;i--){
            for(int j=0;j<16;j++){
                if(j&mask)continue;
                dp[i+1][j|mask]+=dp[i][j];
            }
        }
    }
    for(int d=0;d<4;d++){
        int mask=(1<<d)|(1<<((d+1)%4));
        for(int i=k;i>=0;i--){
            for(int j=0;j<16;j++){
                if(j&mask)continue;
                dp[i+1][j|mask]+=dp[i][j];
            }
        }
    }
}

void work2(){
    // inner
    for(int d=0;d<4;d++){
        int mask=1<<d;
        for(int i=k;i>=0;i--){
            for(int j=0;j<16;j++){
                dp[i+1][j|mask]+=dp[i][j];
            }
        }
    }
    // outer
    for(int d=0;d<4;d++){
        int mask1=1<<d;
        int mask2=1<<((d+1)%4);
        for(int i=k;i>=0;i--){
            for(int j=0;j<16;j++){
                dp[i+1][j|mask1]+=dp[i][j];
                dp[i+1][j|mask2]+=dp[i][j];
                dp[i+1][j|mask1|mask2]+=dp[i][j];
                dp[i+2][j|mask1|mask2]+=dp[i][j];
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    dp[0][0]=1;
    work1();
    for(int t=0;t<n;t++){
        work2();
        work1();
    }
    for(int i=0;i<16;i++)ans+=dp[k][i];
    for(int i=1;i<=k;i++)ans*=i;
    cout << ans << "\n";
}