#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"
#include "group/monoid-action/min-add.hpp"

const int X=200100;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    LazySegmentTree<MaxAddAction<int>> smx(X,0);
    LazySegmentTree<MinAddAction<int>> smn(X,0);
    auto add=[&](int x){
        if(smx.query(x,x)==0){
            smx.modify(x,1);
            smn.modify(x,1);
        }else{
            int id=smn.findfirst(x,X-1,[&](int v){return v==0;});
            smx.update(x,id-1,-1);
            smn.update(x,id-1,-1);
            smx.modify(id,1);
            smn.modify(id,1);
        }
    };
    auto del=[&](int x){
        if(smx.query(x,x)==1){
            smx.modify(x,0);
            smn.modify(x,0);
        }else{
            int id=smx.findfirst(x,X-1,[&](int v){return v==1;});
            smx.update(x,id-1,1);
            smn.update(x,id-1,1);
            smx.modify(id,0);
            smn.modify(id,0);
        }
    };
    for(auto x:a)add(x);
    while(q--){
        int i,x;
        cin >> i >> x;
        i--;
        del(a[i]);
        a[i]=x;
        add(a[i]);
        cout << smx.findlast(0,X-1,[&](int v){return v==1;}) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}