#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1];
    }
    auto vals=a;
    sort(vals.begin(),vals.end());
    for(auto &x:a){
        x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
    }
    SegmentTree<MaxMonoid<ll>> seg1(n+1,-LINF),seg2(n+1,-LINF);
    vector<ll> dp(n+1,-LINF);
    seg1.modify(a[0],0);
    seg2.modify(a[0],0);
    dp[a[0]]=0;
    for(int i=1;i<=n;i++){
        ll val=dp[a[i]];
        val=max(val,seg1.query(0,a[i]-1)+i);
        val=max(val,seg2.query(a[i]+1,n)-i);
        dp[a[i]]=val;
        seg1.update(a[i],val-i);
        seg2.update(a[i],val+i);
    }
    cout << dp[a[n]] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}