#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "group/monoid-action/add-count-affine.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(m);
    for(auto &[l,r]:a){
        cin >> l >> r;
        l--,r--;
    }
    sort(a.begin(),a.end());
    LazySegmentTree<AddCountAffineAction<mint>> seg(n,{0,1});
    seg.modify(0,{1,1});
    for(auto [l,r]:a){
        seg.update(r,n-1,{2,0});
        seg.update(r,r,{1,seg.query(l,r-1).first});
        seg.update(0,l-1,{2,0});
    }
    cout << seg.query(n-1,n-1).first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}