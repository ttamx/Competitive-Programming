#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-add.hpp"

void runcase(){
    int X,Y;
    cin >> X >> Y;
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    auto calc=[&](int x,int y){
        return min(max(x-X,0)+max(y-Y,0),n);
    };
    LazySegmentTree<MinAddAction<int>> seg(n+1,[&](int i){return -i-1;});
    for(int i=0;i<n;i++){
        seg.update(calc(a[i],b[i]),n,+1);
    }
    int q;
    cin >> q;
    while(q--){
        int i,x,y;
        cin >> i >> x >> y;
        i--;
        seg.update(calc(a[i],b[i]),n,-1);
        a[i]=x;
        b[i]=y;
        seg.update(calc(a[i],b[i]),n,+1);
        cout << seg.findfirst(0,n,[&](int x){return x<0;}) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}