#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid/max-idx.hpp"
#include "group/monoid-action/add-count-add.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> ql(q),qr(q);
    vector<ll> ans(q);
    vector<vector<int>> queries(n);
    for(auto &x:ql){
        cin >> x;
        x--;
    }
    for(auto &x:qr){
        cin >> x;
        x--;
    }
    vector<int> cl(n,-1),cr(n,-1);
    int root=-1;
    {
        SegmentTree<MaxIdxMonoid<int>> seg_max(n,[&](int i){return make_pair(a[i],i);});
        for(int i=0;i<q;i++){
            queries[seg_max.query(ql[i],qr[i]).second].emplace_back(i);
        }
        function<int(int,int)> rec=[&](int l,int r)->int {
            if(l>r)return -1;
            int m=seg_max.query(l,r).second;
            cl[m]=rec(l,m-1);
            cr[m]=rec(m+1,r);
            return m;
        };
        root=rec(0,n-1);
    }
    {
        LazySegmentTree<AddCountAddAction<ll>> seg_l(n,make_pair(0LL,1LL));
        function<void(int,int,int)> rec=[&](int l,int r,int m){
            if(m==-1)return;
            rec(l,m-1,cl[m]);
            rec(m+1,r,cr[m]);
            for(auto i:queries[m]){
                ans[i]=qr[i]-ql[i]+1+seg_l.query(ql[i],m).first;
            }
            seg_l.update(m,m,r-m+1);
            if(l<m)seg_l.update(l,m-1,1);
        };
        rec(0,n-1,root);
    }
    {
        LazySegmentTree<AddCountAddAction<ll>> seg_r(n,make_pair(0LL,1LL));
        function<void(int,int,int)> rec=[&](int l,int r,int m){
            if(m==-1)return;
            rec(l,m-1,cl[m]);
            rec(m+1,r,cr[m]);
            for(auto i:queries[m]){
                ans[i]+=seg_r.query(m,qr[i]).first;
            }
            seg_r.update(m,m,m-l+1);
            if(r>m)seg_r.update(m+1,r,1);
        };
        rec(0,n-1,root);
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}