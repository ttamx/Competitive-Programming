#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-add.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    vector<int> good,bad;
    ll total=0,base=0;
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
        if(a[i]<=b[i]){
            good.emplace_back(i);
        }else{
            bad.emplace_back(i);
        }
        total+=b[i]-a[i];
        base+=a[i];
    }
    sort(good.begin(),good.end(),[&](int i,int j){return a[i]<a[j];});
    sort(bad.begin(),bad.end(),[&](int i,int j){return b[i]>b[j];});
    auto seq=good;
    seq.insert(seq.end(),bad.begin(),bad.end());
    vector<int> pos(n);
    for(int i=0;i<n;i++){
        pos[seq[i]]=i;
    }
    LazySegmentTree<MinAddAction<ll>> seg(n*2,0LL);
    for(int i=0;i<n;i++){
        int p=pos[i];
        seg.update(p*2,n*2-1,-a[i]);
        seg.update(p*2+1,n*2-1,+b[i]);
    }
    ll ans=LINF;
    for(int i=0;i<n;i++){
        int p=pos[i];
        seg.update(p*2,n*2-1,+a[i]);
        seg.update(p*2+1,n*2-1,-b[i]);
        ll exc=-seg.query(0,n*2-1);
        ll cur=total+a[i]-b[i]+exc;
        if(cur>=a[i]+exc){
            ans=min(ans,base+exc);
        }
        seg.update(p*2,n*2-1,-a[i]);
        seg.update(p*2+1,n*2-1,+b[i]);
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}