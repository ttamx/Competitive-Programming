#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    vector<mint> aux(n);
    aux[0]=k;
    for(int i=1;i<n;i++){
        aux[i]=aux[i-1]*(k+i);
    }
    auto b=a;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            b[j]+=a[i]*aux[j-i-1]*comb.ifac(j-i);
        }
    }
    for(auto x:b){
        cout << x << " ";
    }
    cout << "\n";
}