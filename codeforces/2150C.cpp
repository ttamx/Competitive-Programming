#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> c(n),a(n),b(n);
    for(auto &x:c){
        cin >> x;
    }
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        b[x-1]=i;
    }
    LazySegmentTree<MaxAddAction<ll>> seg(n,-LINF);
    reverse(a.begin(),a.end());
    for(auto i:a){
        ll cur=max(seg.query(b[i],n-1),0LL)+c[i];
        seg.update(0,b[i],c[i]);
        seg.modify(b[i],cur);
    }
    cout << max(seg.query(0,n-1),0LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}