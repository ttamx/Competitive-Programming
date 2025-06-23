#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s,st;
    cin >> n >> s >> st;
    if(n==1){
        cout << n << "\n";
        exit(0);
    }
    mint ans=0,den=0;
    for(int v=st;v<=s;v++){
        den+=comb.C(s-v+n-2,n-2);
        for(int i=1;i<=n;i++){
            int t=s-v*i;
            if(t<0)break;
            mint inv=comb.inv(i);
            int m=n-i;
            if(m==0){
                if(t==0){
                    ans+=inv;
                }
                continue;
            }
            mint cur=0;
            for(int j=0;j<=m&&j*v<=t;j++){
                mint w=comb.C(m,j)*comb.C(t-j*v+m-1,m-1);
                if(j&1)cur-=w;
                else cur+=w;
            }
            ans+=cur*inv*comb.C(n-1,i-1);
        }
    }
    cout << ans/den << "\n";
}