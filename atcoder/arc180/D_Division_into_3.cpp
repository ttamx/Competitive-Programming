#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid/max.hpp"
#include "group/monoid-action/min-add.hpp"

struct Info{
    int val,l,r;
    Info(int _val,int _l,int _r):val(_val),l(_l),r(_r){}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    SegmentTree<MaxMonoid<int>> seg(a);
    vector<vector<pair<int,int>>> ql(n),qr(n);
    vector<int> mx(q),ans(q);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        mx[i]=seg.query(l,r);
        int nl=seg.findfirst(l,r,[&](int x){return x>=mx[i];});
        int nr=seg.findlast(l,r,[&](int x){return x>=mx[i];});
        ans[i]=mx[i]*2;
        if(l<nl&&nr<r)ans[i]=min(ans[i],a[l]+a[r]);
        if(l<nr-1)ql[l].emplace_back(i,nr-1);
        if(nl+1<r)qr[r].emplace_back(i,nl+1);
    }
    {
        LazySegmentTree<MinAddAction<int>> seg2(n);
        stack<Info> s;
        for(int i=1;i<n;i++){
            Info cur(a[i],i-1,i-1);
            while(!s.empty()&&s.top().val<a[i]){
                auto x=s.top();
                s.pop();
                seg2.update(x.l,x.r,a[i]-x.val);
                cur.l=x.l;
            }
            s.emplace(cur);
            seg2.modify(i-1,a[i-1]+a[i]);
            for(auto [id,l]:qr[i]){
                ans[id]=min(ans[id],seg2.query(l,i-1));
            }
        }
    }
    {
        LazySegmentTree<MinAddAction<int>> seg2(n);
        stack<Info> s;
        for(int i=n-2;i>=0;i--){
            Info cur(a[i],i+1,i+1);
            while(!s.empty()&&s.top().val<a[i]){
                auto x=s.top();
                s.pop();
                seg2.update(x.l,x.r,a[i]-x.val);
                cur.r=x.r;
            }
            s.emplace(cur);
            seg2.modify(i+1,a[i+1]+a[i]);
            for(auto [id,r]:ql[i]){
                ans[id]=min(ans[id],seg2.query(i+1,r));
            }
        }
    }
    for(int i=0;i<q;i++)cout << ans[i]+mx[i] << "\n";
}