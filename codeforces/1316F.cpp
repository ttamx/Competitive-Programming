#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "group/monoid/add.hpp"

using mint = mint107;

struct Info{
    mint ans,pre,suf,all;
    Info(){}
    Info(mint _ans,mint _pre,mint _suf,mint _all):ans(_ans),pre(_pre),suf(_suf),all(_all){}
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        Info res;
        res.ans=l.ans+r.ans+l.suf*r.pre;
        res.pre=l.pre+l.all*r.pre;
        res.suf=r.suf+l.suf*r.all;
        res.all=l.all*r.all;
        return res;
    }
    static Info unit(){return Info(0,0,0,1);}
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    auto b=a;
    int q;
    cin >> q;
    vector<pair<int,int>> qr(q);
    for(auto &[x,v]:qr){
        cin >> x >> v;
        x--;
        b.emplace_back(v);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int m=b.size();
    for(auto &x:a)x=lower_bound(b.begin(),b.end(),x)-b.begin();
    for(auto &[x,v]:qr)v=lower_bound(b.begin(),b.end(),v)-b.begin();
    vector<int> cnt(m);
    for(auto x:a)cnt[x]++;
    vector<mint> fac(n+1),ifac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    ifac[n]=fac[n].inv();
    for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i;
    auto C=[&](int n,int r){
        if(n<0||r<0||n<r)return mint(0);
        return fac[n]*ifac[n-r]*ifac[r];
    };
    vector<mint> pw(n+1),dp(n+1),ipw(n+1);
    pw[0]=ipw[0]=1;
    mint inv2=mint(2).inv();
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    for(int i=1;i<=n;i++)ipw[i]=ipw[i-1]*inv2;
    for(int i=2;i<=n;i++)dp[i]=(pw[i-1]*i-pw[i]+1)/pw[i];
    auto make=[&](int x){
        Info res;
        res.ans=dp[cnt[x]]*b[x]*b[x];
        res.pre=res.suf=(1-ipw[cnt[x]])*b[x];
        res.all=ipw[cnt[x]];
        return res;
    };
    SegmentTree<Monoid> seg(m,[&](int i){return make(i);});
    cout << seg.query(0,m-1).ans << "\n";
    for(auto [x,v]:qr){
        cnt[a[x]]--;
        seg.modify(a[x],make(a[x]));
        a[x]=v;
        cnt[a[x]]++;
        seg.modify(a[x],make(a[x]));
        cout << seg.query(0,m-1).ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}