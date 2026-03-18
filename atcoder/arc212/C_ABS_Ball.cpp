#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    mint ans=0;
    for(int a=0;a*2<=n;a++){
        int b=n-a;
        int c=b-a;
        if(c<m)continue;
        ans+=comb.H(a,m)*comb.H(c-m,2*m);
    }
    for(int i=0;i<m;i++)ans*=2;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}