#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/monoid-base.hpp"

using i128 = __int128_t;

const int B=10;

struct Info{
    ll threshold,val1,val2;
    Info():threshold(0LL),val1(0LL),val2(0LL){}
    Info(ll t,ll v1,ll v2):threshold(t),val1(v1),val2(v2){}
};

Info combine(Info l,Info r){
    Info res;
    res.threshold=l.threshold;
    if(l.val1>=r.threshold){
        res.val1=res.val2=r.val2;
    }else if(l.val2>=r.threshold){
        res.val1=r.val1;
        res.val2=r.val2;
    }else{
        res.val1=res.val2=r.val1;
    }
    return res;
}

Info iden(){
    return Info();
}

using Monoid = MonoidBase<Info,combine,iden>;

ll sqr(ll x){
    ll l=0,r=INF;
    while(l<r){
        ll m=(l+r+1)/2;
        if(m*m<=x)l=m;
        else r=m-1;
    }
    return l;
}

void runcase(){
    int n,q;
    cin >> n >> q;
    int offset=(B-n%B)%B;
    n+=offset;
    vector<ll> a(n);
    for(int i=offset;i<n;i++){
        cin >> a[i];
    }
    int m=n/B;
    SegmentTree<Monoid> seg(m);
    auto calc=[&](int i){
        ll val=0;
        for(int j=0;j<B;j++){
            val=sqr(val+a[i*B+j]);
        }
        ll threshold=val+1;
        for(int j=B-1;j>=0;j--){
            threshold=min((i128)LINF,(i128)threshold*threshold-a[i*B+j]);
        }
        seg.modify(i,Info(threshold,val,val+1));
    };
    for(int i=0;i<m;i++){
        calc(i);
    }
    while(q--){
        int x;
        ll v;
        cin >> x >> v;
        x+=offset-1;
        a[x]=v;
        calc(x/B);
        cout << seg.query(0,m-1).val1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}