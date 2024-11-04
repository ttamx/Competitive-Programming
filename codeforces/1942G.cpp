#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int a,b,c;
    cin >> a >> b >> c;
    int n=min(a,c)+4;
    mint ans=0;
    mint tot=comb.C(a+c+5,c);
    for(int i=4;i<=n;i++){
        mint ways=comb.C(2*i-4,i)-comb.C(2*i-4,i+1);
        ways*=comb.C(a+c-2*i+8,c-i+4);
        tot-=ways;
        ans+=ways*comb.C(i+1,5);
    }
    if(c>a){
        mint ways=comb.C(a+c+5,c)-comb.C(a+c+5,a);
        ans+=tot*comb.C(a+5,5);
    }
    ans*=comb.C(a+b+c+5,b);
    ans*=comb.fac(a);
    ans*=comb.fac(b);
    ans*=comb.fac(c);
    ans*=120;
    ans*=comb.ifac(a+b+c+5);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}