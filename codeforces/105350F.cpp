#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int K=1<<19;

struct SegTree{
    int n;
    struct Node{
        ll sum,add;
        ll mn,mn2,fn;
        ll mx,mx2,fx;
        Node(){
            sum=add=fn=fx=0,mn=mn2=INF,mx=mx2=-INF;
        }
        Node(ll v){
            sum=mn=mx=v,add=0,mn2=INF,mx2=-INF,fn=fx=1;
        }
        friend Node operator+(const Node &l,const Node &r){
            Node res;
            res.sum=l.sum+r.sum;
            res.add=0;
            if(l.mx>r.mx){
                res.mx=l.mx,res.fx=l.fx;
                res.mx2=max(l.mx2,r.mx);
            }else if(r.mx>l.mx){
                res.mx=r.mx,res.fx=r.fx;
                res.mx2=max(r.mx2,l.mx);
            }else{
                res.mx=l.mx,res.fx=l.fx+r.fx;
                res.mx2=max(l.mx2,r.mx2);
            }
            if(l.mn<r.mn){
                res.mn=l.mn,res.fn=l.fn;
                res.mn2=min(l.mn2,r.mn);
            }else if(r.mn<l.mn){
                res.mn=r.mn,res.fn=r.fn;
                res.mn2=min(r.mn2,l.mn);
            }else{
                res.mn=l.mn,res.fn=l.fn+r.fn;
                res.mn2=min(l.mn2,r.mn2);
            }
            return res;
        }
        void apply(int l,int r,ll v){
            sum+=(r-l+1)*v;
            mx+=v,mx2+=v;
            mn+=v,mn2+=v;
            add+=v;
        }
        void chmin(ll v){
            if(v>=mx)return;
            sum+=(v-mx)*fx;
            if(mn==mx)mn=v;
            if(mn2==mx)mn2=v;
            mx=v;
        }
        void chmax(ll v){
            if(v<=mn)return;
            sum+=(v-mn)*fn;
            if(mx==mn)mx=v;
            if(mx2==mn)mx2=v;
            mn=v;
        }
    }t[K];
    void init(int _n){
        n=_n;
        build();
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void push(int l,int r,int i){
        int m=(l+r)/2;
        t[i*2].apply(l,m,t[i].add);
        t[i*2+1].apply(m+1,r,t[i].add);
        t[i*2].chmin(t[i].mx);
        t[i*2+1].chmin(t[i].mx);
        t[i*2].chmax(t[i].mn);
        t[i*2+1].chmax(t[i].mn);
        t[i].add=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(0));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(0,n-1,1);
    }
    void range_add(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return t[i].apply(l,r,v);
        int m=(l+r)/2;
        push(l,r,i);
        range_add(l,m,i*2,x,y,v);
        range_add(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_add(int x,int y,ll v){
        range_add(0,n-1,1,x,y,v);
    }
    void range_chmin(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x||t[i].mx<=v)return;
        if(x<=l&&r<=y&&t[i].mx2<v)return t[i].chmin(v);
        int m=(l+r)/2;
        push(l,r,i);
        range_chmin(l,m,i*2,x,y,v);
        range_chmin(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_chmin(int x,int y,ll v){
        range_chmin(0,n-1,1,x,y,v);
    }
    void range_chmax(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x||t[i].mn>=v)return;
        if(x<=l&&r<=y&&t[i].mn2>v)return t[i].chmax(v);
        int m=(l+r)/2;
        push(l,r,i);
        range_chmax(l,m,i*2,x,y,v);
        range_chmax(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_chmax(int x,int y,ll v){
        range_chmax(0,n-1,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i].sum;
        int m=(l+r)/2;
        push(l,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(0,n-1,1,x,y);
    }
}seg;

void runcase(){
    int n;
    cin >> n;
    map<int,int> pos;
    ll ans=0;
    seg.init(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(pos.count(x)){
            seg.range_chmax(0,pos[x],x);
        }
        ans+=seg.query(0,i);
        pos[x]=i;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}