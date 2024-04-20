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

template<uint32_t mod>
struct MontgomeryModInt{
    using mint = MontgomeryModInt;
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    static constexpr u32 get_r(){
        u32 res=1;
        for(i32 i=0;i<5;i++)res*=2-mod*res;
        return res;
    }

    static const u32 r=get_r();
    static const u32 n2=-u64(mod)%mod;
    static_assert(mod<(1<<30));
    static_assert((mod&1)==1);
    static_assert(r*mod==1);

    u32 x;

    constexpr MontgomeryModInt():x(0){}
    constexpr MontgomeryModInt(const int64_t &v):x(reduce(u64(v%mod+mod)*n2)){}

    static constexpr u32 get_mod(){return mod;}

    static constexpr u32 reduce(const u64 &v){
        return (v+u64(u32(v)*u32(-r))*mod)>>32;
    }

    constexpr u32 val()const{
        u32 res=reduce(x);
        return res>=mod?res-mod:res;
    }

    constexpr mint inv()const{
        int a=val(),b=mod,u=1,v=0,q;
        while(b>0){
            q=a/b;
            a-=q*b;
            u-=q*v;
            swap(a,b);
            swap(u,v);
        }
        return mint(u);
    }

    constexpr mint &operator+=(const mint &rhs){
        if(i32(x+=rhs.x-2*mod)<0)x+=2*mod;
        return *this;
    }
    constexpr mint &operator-=(const mint &rhs){
        if(i32(x-=rhs.x)<0)x+=2*mod;
        return *this;
    }
    constexpr mint &operator*=(const mint &rhs){
        x=reduce(u64(x)*rhs.x);
        return *this;
    }
    constexpr mint &operator/=(const mint &rhs){
        return *this*=rhs.inv();
    }

    constexpr mint &operator++(){return this+=mint(1);}
    constexpr mint &operator--(){return this-=mint(1);}
    constexpr mint operator++(int){
        mint res=*this;
        return this+=mint(1),res;
    }
    constexpr mint operator--(int){
        mint res=*this;
        return this-=mint(1),res;
    }

    constexpr mint operator-()const{return mint()-mint(*this);};
    constexpr mint operator+()const{return mint(*this);};

    friend constexpr mint operator+(const mint &lhs,const mint &rhs){return mint(lhs)+=rhs;}
    friend constexpr mint operator-(const mint &lhs,const mint &rhs){return mint(lhs)-=rhs;}
    friend constexpr mint operator*(const mint &lhs,const mint &rhs){return mint(lhs)*=rhs;}
    friend constexpr mint operator/(const mint &lhs,const mint &rhs){return mint(lhs)/=rhs;}
    friend constexpr bool operator==(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)==(rhs.x>=mod?rhs.x-mod:rhs.x);
    }
    friend constexpr bool operator!=(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)!=(rhs.x>=mod?rhs.x-mod:rhs.x);
    }
    friend constexpr bool operator<(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)<(rhs.x>=mod?rhs.x-mod:rhs.x); // for std::map
    }

    friend istream &operator>>(istream &is,mint &o){
        int64_t v;
        is >> v;
        o=mint(v);
        return is;
    }
    friend ostream &operator<<(ostream &os,const mint &o){
        return os << o.val();
    }
};
using mint = MontgomeryModInt<MOD>;
using vm = vector<mint>;

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
struct Tag{
    mint mul,add;
    Tag():mul(1),add(0){}
    Tag(mint m,mint a):mul(m),add(a){}
    void apply(int l,int r,const Tag &v){
        mul*=v.mul;
        add=add*v.mul+v.add;
    }
};
struct Node{
    mint val;
    Node():val(0){}
    Node(mint v):val(v){}
    void apply(int l,int r,const Tag &v){
        val=val*v.mul+v.add*(r-l+1);
    }
    friend Node operator+(const Node &lhs,const Node &rhs){
        return Node(lhs.val+rhs.val);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vm a(n);
    for(auto &x:a)cin >> x;
    LazySegTree<Node,Tag> s(a);
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        r--;
        if(t==0){
            mint b,c;
            cin >> b >> c;
            s.update(l,r,Tag(b,c));
        }else{
            cout << s.query(l,r).val << "\n";
        }
    }
}