#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    ll tot=0;
    for(auto &x:a){
        cin >> x;
        tot+=x;
    }
    tot-=m;
    if(tot<=0){
        cout << comb.fac(n) << "\n";
        return;
    }
    if(tot>n*(n-1)/2){
        cout << 0 << "\n";
        return;
    }
    vector<vector<mint>> dp(n+1,vector<mint>(tot+1));
    for(int i=0;i<n;i++){
        
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}