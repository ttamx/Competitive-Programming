#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    mint w1=0,wd1=0,w2=0,wd2=0;
    int n1=n/2;
    int n2=(n-1)/2;
    for(int i=0;i<=m;i++){
        mint w=comb.H(i,n1);
        w1+=w;
        wd1+=w*(m-i);
    }
    for(int i=0;i<=m;i++){
        mint w=comb.H(i,n2);
        w2+=w;
        wd2+=w*(m-i);
    }
    cout << w1*w2+w1*wd2+w2*wd1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}