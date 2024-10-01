#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b;
    b.emplace_back(0);
    for(auto &x:a){
        cin >> x;
        b.emplace_back(x);
        b.emplace_back(x+1);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int m=b.size();
    for(auto &x:a)x=lower_bound(b.begin(),b.end(),x)-b.begin();
    vector<pair<int,int>> event(n);
    vector<int> lds(n),lis(n);
    LazySegmentTree<MaxAddAction<int>> s(m,0);
    for(int i=n-1;i>=0;i--){
        auto it=lower_bound(lds.begin(),lds.end(),-a[i]);
        auto &[l,r]=event[i];
        r=a[i]-1;
        if(it==lds.end()){
            lds.emplace_back(-a[i]);
            l=0;
        }else{
            l=-*it;
            *it=-a[i];
        }
        if(l<=r)s.update(l,r,1);
    }
    int ans=0;
    for(int i=0;i<n;i++){
        auto [l,r]=event[i];
        if(l<=r)s.update(l,r,-1);
        ans=max(ans,s.query(0,m-1)+1);
        auto it=lower_bound(lis.begin(),lis.end(),a[i]);
        l=a[i]+1;
        if(it==lis.end()){
            lis.emplace_back(a[i]);
            r=m-1;
        }else{
            r=*it;
            *it=a[i];
        }
        if(l<=r)s.update(l,r,1);
    }
    cout << ans << "\n";
}