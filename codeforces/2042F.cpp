#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info{
    ll pre,suf,best;
    ll pre2,suf2,ans;
    ll presuf,sum;
    Info():pre(-LINF),suf(-LINF),best(-LINF),pre2(-LINF),suf2(-LINF),ans(-LINF),presuf(-LINF),sum(0LL){}
    Info(ll a,ll b):pre(a+b),suf(a+b),best(a+2*b),pre2(-LINF),suf2(-LINF),ans(-LINF),presuf(-LINF),sum(a){}
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        Info res;
        res.pre=max(l.pre,l.sum+r.pre);
        res.suf=max(r.suf,r.sum+l.suf);
        res.best=max({l.best,r.best,l.suf+r.pre});
        res.pre2=max({l.pre2,l.sum+r.pre2,l.pre+r.best,l.presuf+r.pre});
        res.suf2=max({r.suf2,r.sum+l.suf2,r.suf+l.best,r.presuf+l.suf});
        res.ans=max({l.ans,r.ans,l.suf2+r.pre,l.suf+r.pre2,l.best+r.best});
        res.presuf=max({l.presuf+r.sum,l.sum+r.presuf,l.pre+r.suf});
        res.sum=l.sum+r.sum;
        return res;
    }
    static Info unit(){
        return Info();
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    SegmentTree<Monoid> seg(n,[&](int i){return Info(a[i],b[i]);});
    int q;
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==3){
            int l,r;
            cin >> l >> r;
            l--,r--;
            cout << seg.query(l,r).ans << "\n";
        }else{
            int p,x;
            cin >> p >> x;
            p--;
            if(op==1)a[p]=x;
            else b[p]=x;
            seg.modify(p,Info(a[p],b[p]));
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}