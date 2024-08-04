#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/2;

int n,q;
ll a[N];

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    ll query(int l,int r){
        return query(r)-query(l-1);
    }
}fw;

template<class T,class E,T (*tt)(T,T),E (*ee)(E,E),T (*te)(T,E),T (*tu)(),E (*eu)()>
struct LazySegTree{
    int n;
    T t[K];
    E lz[K];
    void apply(int i,E v){
        t[i]=te(t[i],v);
        lz[i]=ee(lz[i],v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=eu();
    }
    void pull(int i){
        t[i]=tt(t[i*2],t[i*2+1]);
    }
    template<class F>
    void build(int l,int r,int i,F f){
        if(l==r){
            t[i]=f();
            lz[i]=eu();
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2,f);
        build(m+1,r,i*2+1,f);
        pull(i);
    }
    template<class F>
    void build(int _n,F f){
        n=_n;
        build(1,n,1,f);
    }
    void build(int _n){
        build(_n,[](){return tu();});
    }
    void modify(int l,int r,int i,int x,T v){
        if(r<x||x<l)return;
        if(l==r)return void(t[i]=v);
        push(i);
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,T v){
        modify(1,n,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,E v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int l,int r,E v){
        update(1,n,1,l,r,v);
    }
    T query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return tu();
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return tt(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    T query(int l,int r){
        return query(1,n,1,l,r);
    }
    template<class F>
    int find_first(int l,int r,int i,int x,int y,F f){
        if(y<l||r<x||!f(t[i]))return n+1;
        if(l==r)return l;
        push(i);
        int m=(l+r)/2;
        int res=find_first(l,m,i*2,x,y,f);
        if(res!=n+1)return res;
        return find_first(m+1,r,i*2+1,x,y,f);
    }
    template<class F>
    int find_first(int l,int r,F f){
        return find_first(1,n,1,l,r,f);
    }
    template<class F>
    int find_last(int l,int r,int i,int x,int y,F f){
        if(y<l||r<x||!f(t[i]))return 0;
        if(l==r)return l;
        push(i);
        int m=(l+r)/2;
        int res=find_last(m+1,r,i*2+1,x,y,f);
        if(res!=0)return res;
        return find_last(l,m,i*2,x,y,f);
    }
    template<class F>
    int find_last(int l,int r,F f){
        return find_last(1,n,1,l,r,f);
    }
};

struct Info{
    int mn,cnt;
    Info():mn(INF),cnt(0){}
    Info(int _mn,int _cnt):mn(_mn),cnt(_cnt){}
};

namespace S1{
    Info merge_info(Info a,Info b){
        if(a.mn<b.mn)return a;
        if(b.mn<a.mn)return b;
        return Info(a.mn,a.cnt+b.cnt);
    }
    int merge_tag(int a,int b){return a+b;}
    Info apply(Info a,int b){return Info(a.mn+b,a.cnt);}
    Info unit_info(){return Info();}
    int unit_tag(){return 0;}
    LazySegTree<Info,int,merge_info,merge_tag,apply,unit_info,unit_tag> seg;
};
using S1::seg;

namespace S2{
    ll merge_info(ll a,ll b){return max(a,b);}
    ll merge_tag(ll a,ll b){return a+b;}
    ll apply(ll a,ll b){return a+b;}
    ll unit_info(){return -LINF;}
    ll unit_tag(){return 0;}
    LazySegTree<ll,ll,merge_info,merge_tag,apply,unit_info,unit_tag> seg_l,seg_r;
};
using S2::seg_l,S2::seg_r;

bool valid(int l,int r){
    if(l>r)return false;
    ll sum=fw.query(l,r);
    return sum<a[l-1]&&sum<a[r+1];
}

vector<pair<int,int>> find_ranges(int i){
    vector<pair<int,int>> res;
    vector<int> left{i+1},right{i-1};
    ll sum_l=fw.query(i),sum_r=fw.query(i-1);
    for(int l=i;l>=1;l=seg_l.find_last(1,l-1,[&](ll x){return x>sum_r;}))left.emplace_back(l);
    for(int r=i;r<=n;r=seg_r.find_first(r+1,n,[&](ll x){return x>-sum_l;}))right.emplace_back(r);
    for(int l:left)for(int r:right)if(valid(l,r))res.emplace_back(l,r);
    return res;
}

void update(int i,int v){
    int dif=v-a[i];
    a[i]=v;
    for(auto [l,r]:find_ranges(i)){
        cerr << l << " " << r << "\n";
        seg.update(l,r,-1);
    }
    cerr << "-----\n";
    fw.update(i,dif);
    seg_l.update(i+1,n,dif);
    seg_r.update(i,n,-dif);
    seg_l.modify(i+1,a[i]+fw.query(i));
    seg_r.modify(i-1,a[i]-fw.query(i-1));
    for(auto [l,r]:find_ranges(i))seg.update(l,r,1);
}

void init(){
    for(int i=1;i<=n;i++){
        a[i]=1;
        fw.update(i,1);
    }
    a[0]=a[n+1]=LINF;
    seg.build(n,[]{return Info(1,1);});
    seg_l.build(n);
    seg_r.build(n);
    for(int i=1;i<=n;i++){
        seg_l.modify(i,a[i-1]+i-1);
        seg_r.modify(i,a[i+1]-i);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    init();
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        update(i,x);
    }
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,y;
            cin >> x >> y;
            update(x,y);
        }else{
            int l,r;
            cin >> l >> r;
            ll sum_l=fw.query(l-1),sum_r=fw.query(r);
            int nl=max(l,seg_r.find_last(l,r-1,[&](ll x){return x>-sum_l;})+1);
            int nr=min(r,seg_l.find_first(l+1,r,[&](ll x){return x>sum_r;})-1);
            cout << seg.query(nl,nr).cnt << "\n";
        }
    }
}