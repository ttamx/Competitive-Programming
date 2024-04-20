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

template<class Node,class Tag>
struct LazySegTree{
    int n;
    vector<Node> t;
    vector<Tag> lz;
    LazySegTree(){}
    LazySegTree(int n,Node v=Node()){init(n,v);}
    template<class T>
    LazySegTree(const vector<T> &a){init(a);}
    void init(int n,Node v=Node()){init(vector<Node>(n,v));}
    template<class T>
    void init(const vector<T> &a){
        n=sz(a);
        t.assign(4<<31-__builtin_clz(n),Node());
        lz.assign(4<<31-__builtin_clz(n),Tag());
        function<void(int,int,int)> build=[&](int l,int r,int i){
            if(l==r)return void(t[i]=a[l]);
            int m=(l+r)/2;
            build(l,m,i*2);
            build(m+1,r,i*2+1);
            pull(i);
        };
        build(0,n-1,1);
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void apply(int l,int r,int i,const Tag &v){
        t[i].apply(l,r,v);
        lz[i].apply(l,r,v);
    }
    void push(int l,int r,int i){
        int m=(l+r)/2;
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=Tag();
    }
    void modify(int l,int r,int i,int x,const Node &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        push(l,r,i);
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,const Node &v){
        modify(0,n-1,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,const Tag &v){
        update(0,n-1,1,x,y,v);
    }
    Node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(0,n-1,1,x,y);
    }
    template<class F>
    int findfirst(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,r,i);
        int res=findfirst(l,m,i*2,x,y,f);
        if(res==-1)res=findfirst(m+1,r,i*2+1,x,y,f);
        return res;
    }
    template<class F>
    int findfirst(int x,int y,const F &f){
        return findfirst(0,n-1,1,x,y,f);
    }
    template<class F>
    int findlast(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,r,i);
        int res=findlast(m+1,r,i*2+1,x,y,f);
        if(res==-1)res=findlast(l,m,i*2,x,y,f);
        return res;
    }
    template<class F>
    int findlast(int x,int y,const F &f){
        return findlast(0,n-1,1,x,y,f);
    }
};
struct AddTag{
    ll val;
    AddTag():val(0){}
    AddTag(ll v):val(v){}
    void apply(int l,int r,const AddTag &v){
        val+=v.val;
    }
};
struct MaxNode{
    ll val,id;
    MaxNode():val(-LINF),id(-1){}
    MaxNode(ll x,int i):val(x),id(i){}
    void apply(int l,int r,const AddTag &v){
        val+=v.val;
    }
    friend MaxNode operator+(const MaxNode &lhs,const MaxNode &rhs){
        return lhs.val<rhs.val?rhs:lhs;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vl a(n),b(n),id(n),inv(n);
    vector<pll> v;
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
        v.emplace_back(b[i],i);
    }
    auto c=b;
    sort(all(v));
    sort(all(c));
    for(int i=0;i<n;i++){
        id[v[i].second]=i;
        inv[i]=v[i].second;
    }
    LazySegTree<MaxNode,AddTag> s(n);
    vector<bool> used(n);
    for(int i=0;i<n;i++)s.modify(id[i],MaxNode(a[i]-b[i],id[i]));
    auto tmp=s.query(0,n-1);
    int p=0;
    ll ans=tmp.val;
    int mx=lower_bound(all(c),b[inv[tmp.id]])-c.begin();
    used[tmp.id]=true;
    for(;p<mx;p++)if(!used[p])s.modify(p,MaxNode(a[inv[p]],p));
    s.modify(tmp.id,MaxNode());
    cout << ans << "\n";
    for(int i=1;i<n;i++){
        auto l=s.query(0,mx-1),r=s.query(mx,n-1);
        r.val+=c[mx];
        tmp=l+r;
        ans+=tmp.val;
        mx=max(mx,int(lower_bound(all(c),b[inv[tmp.id]])-c.begin()));
        used[tmp.id]=true;
        for(;p<mx;p++)if(!used[p])s.modify(p,MaxNode(a[inv[p]],p));
        s.modify(tmp.id,MaxNode());
        cout << ans << "\n";
    }
}