#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=1<<21;
const int INF=INT_MAX/2;

int n,m,b,p;
vector<tuple<int,int,int>> add[N],del[N];

namespace SUB2{

struct SegTree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v,lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void build(int l,int r,int i){
        t[i]=0,lz[i]=0;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
}seg;

bool check(int k){
    seg.build();
    seg.update(1,k-1,INF);
    for(int i=1;i<k;i++)for(auto [l,r,v]:add[i])seg.update(l,r+k-1,v);
    for(int i=k;i<=m;i++){
        for(auto [l,r,v]:add[i])seg.update(l,r+k-1,v);
        for(auto [l,r,v]:del[i-k])seg.update(l,r+k-1,-v);
        if(seg.t[1]<=b)return true;
    }
    return false;
}

inline void solve(){
    int l=0,r=min(n,m);
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l;
}

}

namespace SUB3{

struct Block{
    int val,sz;
    bool operator<(const Block &b)const{
        return val<b.val||(val==b.val&&sz>b.sz);
    }
};

struct Info{
    int sz;
    Block mn,pre,suf;
    Info():sz(0),mn({INF,0}),pre({INF,0}),suf({INF,0}){}
    static Info single(){
        Info res;
        res.sz=1;
        res.mn=res.pre=res.suf={0,1};
        return res;
    }
    void apply(int v){
        mn.val+=v;
        pre.val+=v;
        suf.val+=v;
    }
    friend Info operator+(const Info &a,const Info &b){
        Info res;
        res.mn=min(a.mn,b.mn);
        if(a.suf.val==b.pre.val)res.mn=min(res.mn,{a.suf.val,a.suf.sz+b.pre.sz});
        res.pre=a.pre;
        if(a.pre.val==b.pre.val&&a.pre.sz==a.sz)res.pre.sz+=b.pre.sz;
        res.suf=b.suf;
        if(a.suf.val==b.suf.val&&b.suf.sz==b.sz)res.suf.sz+=a.suf.sz;
        res.sz=a.sz+b.sz;
        return res;
    }
};

struct SegTree{
    Info t[K];
    int lz[K];
    void apply(int i,int v){
        t[i].apply(v);
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(int l,int r,int i){
        lz[i]=0;
        if(l==r)return t[i]=Info::single(),void();
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
}seg;

inline void solve(){
    seg.build();
    int top=0,bot=0,ans=0;
    while(bot<=m){
        auto x=seg.t[1].mn;
        int h=bot-top,w=x.val==0?x.sz:0;
        ans=max(ans,min(h,w));
        if(h<=w){
            bot++;
            for(auto [l,r,v]:add[bot])seg.update(l,r,v);
        }else{
            top++;
            for(auto [l,r,v]:del[top])seg.update(l,r,-v);
        }
    }
    cout << ans << "\n";
}

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> b >> p;
    for(int i=0;i<p;i++){
        int x1,y1,x2,y2,c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        add[x1].emplace_back(y1,y2,c);
        del[x2].emplace_back(y1,y2,c);
    }
    if(b>0)SUB2::solve();
    else SUB3::solve();
}