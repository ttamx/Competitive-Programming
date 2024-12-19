#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

mint binpow(mint a,ll b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

void runcase(){
    int n,m,v;
    cin >> n >> m >> v;
    mint ans=0;
    for(int c=1;c<=v;c++){
        for(int i=1;i<=n;i++){
            mint col=binpow(v,n-i)*binpow(c,i);
            mint single=binpow(v-c+1,n-i);
            mint a=col-single,b=col;
            mint ways=single*(binpow(a,m)-binpow(b,m))/(a-b);
            ans+=(i%2==1?1:-1)*comb.C(n,i)*ways;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}