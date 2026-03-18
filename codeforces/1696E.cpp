#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    mint ans=0;
    for(int i=0;i<=n;i++){
        int x;
        cin >> x;
        ans+=comb.C(x+i,x);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}