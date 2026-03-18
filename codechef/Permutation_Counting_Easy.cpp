#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,k;
    cin >> n >> k;
    if(n<3){
        cout << 0 << "\n";
        return;
    }
    int a=(n+2)/3;
    int b=(n+1)/3;
    int c=n/3;
    mint ans=0;
    auto calc=[&](int s,int v){
        if(s<v)return mint(0);
        return comb.C(s-v+v-1,v-1);
    };
    for(int sa=0;sa<2;sa++){
        for(int ea=0;ea<2;ea++){
            for(int sb=0;sb<2;sb++){
                if(sa&&sb)continue;
                for(int eb=0;eb<2;eb++){
                    if(ea&&eb)continue;
                    for(int m=0;m<c;m++){
                        ans+=calc(a,m+sa+ea)*calc(b,c-1-m+sb+eb)*comb.C(c-1,m);
                    }
                }
            }
        }
    }
    cout << ans*comb.fac(a)*comb.fac(b)*comb.fac(c) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}