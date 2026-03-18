#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

const int N=3e5+5;
const int K=1<<20;

int n,q;
ll a[N];
ll ans[N];
vector<tuple<ll,int,int,int>> qr;
ll base=0;

struct Line{
    ll m,c;
    ll eval(ll x){
        return m*x+c;
    }
    bool operator<(const Line &o)const{
        return m<o.m||(m==o.m&&c<o.c);
    }
    Line operator+(const Line &o)const{
        return Line{m+o.m,c+o.c};
    }
    Line operator-(const Line &o)const{
        return Line{m-o.m,c-o.c};
    }
};

i128 cross(const Line &a,const Line &b){
    return i128(a.m)*b.c-i128(b.m)*a.c;
}

struct CHT{
    int p;
    vector<Line> dat;
    CHT():p(0),dat(){}
    bool bad(const Line &x,const Line &y,const Line &z){
        return i128(x.c-z.c)*(y.m-x.m)<=i128(x.c-y.c)*(z.m-x.m);
    }
    void insert(Line v){
        if(!dat.empty()&&dat.back().m==v.m){
            assert(dat.back().c<=v.c);
            dat.pop_back();
        }
        assert(dat.empty()||dat.back().m<v.m);
        while(dat.size()>=2&&bad(dat.end()[-2],dat.back(),v)){
            dat.pop_back();
        }
        dat.emplace_back(v);
    }
    ll query(ll x){
        while(p+1<dat.size()&&dat[p].eval(x)<dat[p+1].eval(x)){
            p++;
        }
        assert(p<dat.size());
        return dat[p].eval(x);
    }
};

CHT max(const CHT &a,const CHT &b){
    CHT c;
    for(int i=0,j=0;i<a.dat.size()||j<b.dat.size();){
        if(j==b.dat.size()||(i<a.dat.size()&&a.dat[i]<b.dat[j])){
            c.insert(a.dat[i++]);
        }else{
            c.insert(b.dat[j++]);
        }
    }
    return c;
}

CHT add(CHT a,Line v){
    for(auto &e:a.dat){
        e=e+v;
    }
    return a;
}

CHT add(const CHT &a,const CHT &b){
    assert(!a.dat.empty()&&!b.dat.empty());
    CHT c;
    Line p=a.dat[0]+b.dat[0];
    c.insert(p);
    auto get_a=[&](int i){return a.dat[i]-a.dat[i-1];};
    auto get_b=[&](int i){return b.dat[i]-b.dat[i-1];};
    for(int i=1,j=1;i<a.dat.size()||j<b.dat.size();){
        if(j==b.dat.size()||(i<a.dat.size()&&cross(get_a(i),get_b(j))<0)){
            p=p+get_a(i++);
        }else{
            p=p+get_b(j++);
        }
        c.insert(p);
    }
    return c;
}

struct Info{
    ll sum,pre,suf,ans;
    friend Info operator+(const Info &l,const Info &r){
        return Info{l.sum+r.sum,max(l.pre,r.pre+l.sum),max(r.suf,l.suf+r.sum),max({l.ans,r.ans,l.suf+r.pre})};
    }
};

struct Segtree{
    Line sum[K];
    CHT pre[K],suf[K],ans[K];
    void build(int l,int r,int i){
        if(l==r){
            sum[i]=Line{1,a[l]};
            pre[i].insert(Line{0,0});
            pre[i].insert(Line{1,a[l]});
            suf[i].insert(Line{0,0});
            suf[i].insert(Line{1,a[l]});
            ans[i].insert(Line{0,0});
            ans[i].insert(Line{1,a[l]});
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        sum[i]=sum[i*2]+sum[i*2+1];
        pre[i]=max(pre[i*2],add(pre[i*2+1],sum[i*2]));
        suf[i]=max(suf[i*2+1],add(suf[i*2],sum[i*2+1]));
        ans[i]=max(max(ans[i*2],ans[i*2+1]),add(suf[i*2],pre[i*2+1]));
    }
    void build(){
        build(1,n,1);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info{0,0,0,0};
        if(x<=l&&r<=y)return Info{sum[i].eval(base),pre[i].query(base),suf[i].query(base),ans[i].query(base)};
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Info query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    seg.build();
    int idx=0;
    while(q--){
        string op;
        cin >> op;
        if(op[0]=='S'){
            ll x;
            cin >> x;
            base+=x;
        }else{
            int l,r;
            cin >> l >> r;
            qr.emplace_back(base,l,r,++idx);
        }
    }
    sort(qr.begin(),qr.end());
    for(auto [v,l,r,i]:qr){
        base=v;
        ans[i]=seg.query(l,r).ans;
    }
    for(int i=1;i<=idx;i++){
        cout << ans[i] << "\n";
    }
}