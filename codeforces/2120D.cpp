#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int a,b,k;
    cin >> a >> b >> k;
    mint n=mint(a-1)*mint(k)+1;
    mint m=1;
    for(int i=1;i<=a;i++){
        m*=(n-i+1)*comb.inv(i);
    }
    cout << n << " " << m*mint(b-1)*mint(k)+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}