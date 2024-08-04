#include "template.hpp"
#include "modular-arithmetic/modint.hpp"
#include "group/monoid/add.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"

using mint = mint32;

struct Monoid{
    using value_type = mint;
    static constexpr mint op(const mint &a,const mint &b){return a*b;}
    static constexpr mint unit(){return 1;}
};

struct Action{
    using InfoMonoid = AddMonoid<mint>;
    using TagMonoid = Monoid;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return a*b;
    }
};


void runcase(){
    int n,k,mod;
    cin >> n >> k >> mod;
    mint::set_mod(mod);
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    LazySegmentTree<Action> seg(n,mint(0));
    mint ans=0;
    for(int i=0;i<n;i++){
        mint mul=1;
        seg.modify(i,1);
        seg.update(0,i,a[i]);
        ans+=seg.query(max(0,i-k+1),i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}