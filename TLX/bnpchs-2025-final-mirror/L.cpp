#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        n--,k--;
        if(k==0||k==n){
            cout << n+1 << "\n";
        }else{
            cout << comb.C(n+2,k+1)-comb.C(n,k) << "\n";
        }
    }
}