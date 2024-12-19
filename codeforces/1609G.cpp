#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-add.hpp"
#include "group/monoid-action/add-count-add.hpp"


void runcase(){
    int n,m,q;
    cin >> n >> m >> q;
    vector<ll> a(n),b(m);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    ll base=a[0]+b[0];
    LazySegmentTree<AddCountAddAction<ll>> seg(m-1,[&](int i){return make_pair((b[i+1]-b[i])*(m-i-1),m-i-1);});
    LazySegmentTree<AddCountAddAction<ll>> seg2(m-1,[&](int i){return make_pair(b[i+1]-b[i],1LL);});
    LazySegmentTree<MinAddAction<ll>> smx(m-1,[&](int i){return b[i+1]-b[i];});
    for(int i=n-1;i>=1;i--){
        a[i]-=a[i-1];
    }
    for(int i=m-1;i>=1;i--){
        b[i]-=b[i-1];
    }
    while(q--){
        int op,k,d;
        cin >> op >> k >> d;
        if(op==1){
            k=n-k;
            if(k==0){
                base+=d;
                k++;
            }
            for(int i=k;i<n;i++){
                a[i]+=d;
            }
        }else{
            k=m-k;
            if(k==0)base+=d;
            else k--;
            seg.update(k,m-2,d);
            seg2.update(k,m-2,d);
            smx.update(k,m-2,d);
        }
        ll ans=base*(n+m-1)+seg.query(0,m-2).first;
        for(int i=1;i<n;i++){
            int idx=smx.findlast(0,m-2,[&](ll x){return x<a[i];});
            ans+=a[i]*(n-i+m-2-idx);
            if(idx!=-1){
                ans+=seg2.query(0,idx).first;
            }
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}