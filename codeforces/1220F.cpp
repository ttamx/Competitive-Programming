#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"
#include "data-structure/cartesian-tree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    a.insert(a.end(),a.begin(),a.end());
    CartesianTree<int,true> ct(a);
    LazySegmentTree<MaxAddAction<int>> seg(2*n,0);
    auto upd=[&](int i,int v){
        auto [l,r]=ct.range[i];
        seg.update(l,r,v);
    };
    for(int i=0;i<n;i++){
        upd(i,+1);
    }
    int ans=INF,ans2=-1;
    for(int i=0;i<n;i++){
        int res=seg.query(0,2*n-1);
        if(res<ans){
            ans=res;
            ans2=i;
        }
        upd(i,-1);
        upd(i+n,+1);
    }
    cout << ans << " " << ans2 << "\n";
}