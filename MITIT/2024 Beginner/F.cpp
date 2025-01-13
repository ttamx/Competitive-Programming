#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=52;
const int D=4005;
const int OFFSET=2002;

int n;
int a[N],b[N];
mint dp[N][N][D];
mint aux[D];

void update(int l,int r,mint val){
    assert(l<=r);
    aux[l]+=val;
    aux[r+1]-=val;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
    }
    if(n==1){
        cout << b[1]-a[1]+1 << "\n";
        exit(0);
    }
    for(int i=a[1];i<=b[1];i++){
        dp[1][n+1][OFFSET-i]=1;
    }
    for(int sz=n;sz>=2;sz--){
        for(int l=1,r=sz;r<=n;l++,r++){
            for(int d=0;d<D;d++){
                aux[d]=0;
            }
            for(int d=0;d<D;d++){
                int diff=d-OFFSET;
                if(diff>0){
                    update(d-b[l],d-a[l],dp[l-1][r][d]);
                }else if(diff<0){
                    update(d+a[r],d+b[r],dp[l][r+1][d]);
                }
            }
            for(int d=1;d<D;d++){
                aux[d]+=aux[d-1];
                dp[l][r][d]=aux[d];
            }
        }
    }
    mint ans=0;
    for(int l=1;l+1<=n;l++){
        for(int d=0;d<D;d++){
            if(d!=OFFSET){
                ans+=dp[l][l+1][d];
            }
        }
    }
    cout << ans << "\n";
}