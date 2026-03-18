#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    SegmentTree<MinMonoid<int>> seg(a);
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int i,v;
            cin >> i >> v;
            i--;
            seg.modify(i,v);
        }else{
            int l,r;
            cin >> l >> r;
            l--,r--;
            auto calc=[&](int d){
                return seg.query(l,l+d)-d;
            };
            int lo=0,hi=r-l;
            while(lo<hi){
                int m=(lo+hi)/2;
                if(calc(m)<=0)hi=m;
                else lo=m+1;
            }
            cout << (calc(lo)==0) << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}