#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    if(n==m){
        cout << mint(n)*k << "\n";
        return;
    }
    mint ans=0;
    mint base=1;
    for(int i=1;i<=m;i++){
        ans+=i*base*comb.C(n-i-1,m-i);
        base*=2;
    }
    for(int i=1;i<n;i++)ans*=comb.inv(2);
    cout << ans*k << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}