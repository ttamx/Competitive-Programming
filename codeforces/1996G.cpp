#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-count-add.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(2*n);
    LazySegmentTree<MinCountAddAction<int>> seg(2*n,pair<int,int>(0,1));
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        a[l].emplace_back(r);
        seg.update(l,r-1,1);
    }
    auto get=[&](int x){
        auto [val,freq]=seg.query(x,x+n-2);
        if(val>0)return n-1;
        return n-1-freq;
    };
    int ans=n-1;
    for(int i=0;i<n;i++){
        ans=min(ans,get(i));
        for(auto j:a[i]){
            seg.update(i,j-1,-1);
            seg.update(j,i+n-1,1);
            a[j].emplace_back(i+n);
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