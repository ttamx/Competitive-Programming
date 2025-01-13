#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info{
    ll mn,mx,mn2,mx2,best;
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        return {min(l.mn,r.mn),max(l.mx,r.mx),min(l.mn2,r.mn2),max(l.mx2,r.mx2),max({l.best,r.best,r.mx-l.mn,l.mx2-r.mn2})};
    }
    static Info unit(){
        return {LINF,-LINF,LINF,-LINF,-LINF};
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    SegmentTree<Monoid> seg(n,[&](int i){
        return Info{a[i]-i,a[i]-i,a[i]+i,a[i]+i,0LL};
    });
    cout << seg.query(0,n-1).best << "\n";
    while(q--){
        int i;
        ll x;
        cin >> i >> x;
        i--;
        seg.modify(i,Info{x-i,x-i,x+i,x+i,0LL});
        cout << seg.query(0,n-1).best << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}