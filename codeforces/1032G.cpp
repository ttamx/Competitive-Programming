#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/minmax.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    if(n==1){
        cout << 0 << "\n";
        return;
    }
    vector<int> l(2*n),r(2*n);
    int lg=1;
    while((1<<lg)<n)lg++;
    vector<SegmentTree<MinMaxMonoid<int>>> seg(lg);
    seg[0].init(2*n,[&](int i){
        return make_pair(max(i-a[i%n],0),min(i+a[i%n],2*n-1));
    });
    for(int i=1;i<lg;i++){
        seg[i].init(2*n,[&](int j){
            auto [l,r]=seg[i-1].query(j,j);
            return seg[i-1].query(l,r);
        });
    }
    vector<int> ans(n,INF);
    for(int i=0;i<2*n;i++){
        int l=i,r=i;
        int res=1;
        for(int j=lg-1;j>=0;j--){
            auto [nl,nr]=seg[j].query(l,r);
            if(nr-nl+1<n){
                l=nl,r=nr;
                res+=1<<j;
            }
        }
        ans[i%n]=min(ans[i%n],res);
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