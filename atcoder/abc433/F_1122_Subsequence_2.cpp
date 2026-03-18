#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    string s;
    cin >> s;
    array<int,10> c1{},c2{};
    for(auto x:s){
        c2[x-'0']++;
    }
    mint ans=0;
    for(auto x:s){
        int v=x-'0';
        if(v>0){
            ans+=comb.C(c1[v-1]+c2[v]-1,c2[v]);
        }
        c1[v]++;
        c2[v]--;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}