#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=55;
const int T=2505;

int n,t;
int a[N],b[N];
mint fac[N];
mint ways[N][N][N][3];
mint dp1[N][T],dp2[N][N][T];
mint ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
    }
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i;
    }
    ways[1][0][0][0]=1;
    ways[0][1][0][1]=1;
    ways[0][0][1][2]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                for(int p=0;p<3;p++){
                    if(p!=0)ways[i+1][j][k][0]+=ways[i][j][k][p];
                    if(p!=1)ways[i][j+1][k][1]+=ways[i][j][k][p];
                    if(p!=2)ways[i][j][k+1][2]+=ways[i][j][k][p];
                }
            }
        }
    }
    dp1[0][0]=1;
    for(int i=1;i<=n;i++){
        if(b[i]!=1)continue;
        for(int j=n;j>=1;j--){
            for(int k=a[i];k<=t;k++){
                dp1[j][k]+=dp1[j-1][k-a[i]];
            }
        }
    }
    dp2[0][0][0]=1;
    for(int i=1;i<=n;i++){
        if(b[i]==2){
            for(int j=n;j>=1;j--){
                for(int k=0;k<=n;k++){
                    for(int p=a[i];p<=t;p++){
                        dp2[j][k][p]+=dp2[j-1][k][p-a[i]];
                    }
                }
            }
        }
        if(b[i]==3){
            for(int j=0;j<=n;j++){
                for(int k=n;k>=1;k--){
                    for(int p=a[i];p<=t;p++){
                        dp2[j][k][p]+=dp2[j][k-1][p-a[i]];
                    }
                }
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                mint cur=0;
                for(int p=0;p<3;p++){
                    cur+=ways[i][j][k][p];
                }
                for(int p=0;p<=t;p++){
                    ans+=dp1[i][p]*dp2[j][k][t-p]*cur*fac[i]*fac[j]*fac[k];
                }
            }
        }
    }
    cout << ans << "\n";
}