#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]--;
        pos[a[i]].emplace_back(i);
    }
    LazySegmentTree<MaxAddAction<int>> seg_l(n,[&](int i){return n-i;});
    LazySegmentTree<MaxAddAction<int>> seg_r(n,[&](int i){return i+1;});
    SegmentTree<MinMonoid<int>> rmq(a);
    int ans=0;
    for(int v=0;v<n;v++){
        for(auto i:pos[v]){
            {
                int cur=seg_l.query(0,i)-seg_l.query(i,i)+1-seg_r.query(i,i);
                int p=seg_r.findlast(i,n-1,[&](int x){return x+cur>=0;});
                if(p>=i)ans=max(ans,v-rmq.query(i,p));
            }
            {
                int cur=seg_r.query(i,n-1)-seg_r.query(i,i)+1-seg_l.query(i,i);
                int p=seg_l.findfirst(0,i,[&](int x){return x+cur>=0;});
                if(p<=i)ans=max(ans,v-rmq.query(p,i));
            }
        }
        for(auto i:pos[v]){
            seg_l.update(0,i,-2);
            seg_r.update(i,n-1,-2);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}