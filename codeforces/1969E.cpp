#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-add.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> pos(n,-1),pre(n);
    for(int i=0;i<n;i++){
        pre[i]=pos[a[i]];
        pos[a[i]]=i;
    }
    LazySegmentTree<MinAddAction<int>> seg(n,0);
    int ans=0;
    for(int i=0,p=0;i<n;i++){
        if(pre[i]!=-1&&pre[pre[i]]!=-1){
            seg.update(0,pre[pre[i]],+1);
        }
        if(pre[i]!=-1){
            seg.update(0,pre[i],-2);
        }
        seg.update(0,i,+1);
        if(seg.query(p,i)==0){
            ans++;
            p=i+1;
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