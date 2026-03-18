#include "template.hpp"
#include "data-structure/cartesian-tree.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    CartesianTree<int,false> ct(a);
    function<pair<mint,int>(int,bool,bool)> dfs=[&](int u,bool l,bool r)->pair<mint,int> {
        if(u==-1)return {1,0};
        auto [wl,sl]=dfs(ct.lch[u],l,true);
        auto [wr,sr]=dfs(ct.rch[u],true,r);
        mint ways=0;
        if(!l){
            ways+=comb.C(sl+sr+1,sl);
        }else if(!r){
            ways+=comb.C(sl+sr+1,sr);
        }else{
            ways+=comb.C(sl+sr+1,sr);
            ways+=comb.C(sl+sr+1,sl);
            ways-=comb.C(sl+sr,sl);
        }
        return {ways*wl*wr,sl+sr+1};
    };
    int root=ct.root;
    auto [wl,sl]=dfs(ct.lch[root],false,true);
    auto [wr,sr]=dfs(ct.rch[root],true,false);
    cout << wl*wr*comb.C(sl+sr,sl) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}