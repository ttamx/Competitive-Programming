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

template<class MonoidAction>
struct SparseSegmentTree{
    using InfoMonoid = typename MonoidAction::InfoMonoid;
    using TagMonoid = typename MonoidAction::TagMonoid;
    using Info = typename MonoidAction::Info;
    using Tag = typename MonoidAction::Tag;
    struct Node;
    using Ptr = Node*;
    struct Node{
        Info val;
        Tag lz;
        Ptr l,r;
        Node():val(InfoMonoid::unit()),lz(TagMonoid::unit()),l(nullptr),r(nullptr){}
        Node(Info v,Tag t):val(v),lz(t),l(nullptr),r(nullptr){}
    };
    ll lb,ub;
    Ptr rt;
    SparseSegmentTree(){}
    SparseSegmentTree(ll n){init(0,n-1);}
    SparseSegmentTree(ll lb,ll ub){init(lb,ub);}
    void init(ll _lb,ll _ub){
        lb=_lb,ub=_ub,rt=new Node();
    }
    Info val(Ptr t){
        return t?t->val:InfoMonoid::unit();
    }
    void pull(Ptr &t){
        t->val=InfoMonoid::op(val(t->l),val(t->r));
    }
    void apply(Ptr &t,const Tag &v){
        if(!t)t=new Node();
        t->val=MonoidAction::op(t->val,v);
        t->lz=TagMonoid::op(t->lz,v);
    }
    void push(Ptr &t){
        apply(t->l,t->lz);
        apply(t->r,t->lz);
        t->lz=TagMonoid::unit();
    }
    void modify(ll l,ll r,Ptr &t,ll x,const Info &v){
        if(x<l||r<x)return;
        if(l==r)return void(t->val=v);
        ll m=l+(r-l)/2;
        push(t);
        modify(l,m,t->l,x,v);
        modify(m+1,r,t->r,x,v);
        pull(t);
    }
    void modify(ll x,const Info &v){
        modify(lb,ub,rt,x,v);
    }
    void update(ll l,ll r,Ptr &t,ll x,ll y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(t,v);
        ll m=l+(r-l)/2;
        push(t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        pull(t);
    }
    void update(ll x,ll y,const Tag &v){
        update(lb,ub,rt,x,y,v);
    }
    Info query(ll l,ll r,Ptr &t,ll x,ll y){
        if(y<l||r<x)return InfoMonoid::unit();
        if(x<=l&&r<=y)return t->val;
        ll m=l+(r-l)/2;
        push(t);
        return InfoMonoid::op(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    Info query(ll x,ll y){
        return query(lb,ub,rt,x,y);
    }
    template<class F>
    ll findfirst(ll l,ll r,Ptr t,ll x,ll y,const F &f){
        if(y<l||r<x||!f(t->val))return -1;
        if(l==r)return l;
        ll m=l+(r-l)/2;
        push(t);
        ll res=findfirst(l,m,t->l,x,y,f);
        if(res==-1)res=findfirst(m+1,r,t->r,x,y,f);
        return res;
    }
    template<class F>
    ll findfirst(ll x,ll y,const F &f){
        return findfirst(lb,ub,rt,x,y,f);
    }
    template<class F>
    ll findlast(ll l,ll r,Ptr t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=l+(r-l)/2;
        push(t);
        ll res=findlast(m+1,r,t->r,x,y,f);
        if(res==-1)res=findlast(l,m,t->l,x,y,f);
        return res;
    }
    template<class F>
    ll findlast(ll x,ll y,const F &f){
        return findlast(lb,ub,rt,x,y,f);
    }
};

template<class T>
struct MaxMonoid{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return max(x,y);}
    static constexpr T unit(){return numeric_limits<T>::min();}
};

template<class Monoid>
struct DefaultAction{
    using InfoMonoid = Monoid;
    using TagMonoid = Monoid;
    using Info = typename Monoid::value_type;
    using Tag = typename Monoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return Monoid::op(a,b);
    }
};

void runcase(){
    ll n,m,k;
    cin >> n >> m >> k;
    vector<pll> a(k);
    for(auto &[x,y]:a)cin >> y >> x;
    auto c=a;
    sort(all(a));
    using T = tuple<ll,ll,ll>;
    vector<T> pre,suf,aux;
    vector<pll> pre2;
    pre.emplace_back(1,0,0);
    for(auto [x,y]:a){
        if(get<1>(pre.back())<=y){
            ll res=1LL*(n-get<1>(pre.back()))*(x-get<0>(pre.back()))+get<2>(pre.back());
            pre.emplace_back(x,y,res);
        }
    }
    pre2.emplace_back(1,0);
    for(auto [x,y]:a){
        while(get<1>(pre2.back())<y)pre2.pop_back();
        pre2.emplace_back(x,y);
    }
    ll ans=1LL*(n-get<1>(pre.back()))*(m-get<0>(pre.back())+1)+get<2>(pre.back());
    cout << ans << "\n";
    ll sum=0;
    reverse(all(a));
    SparseSegmentTree<DefaultAction<MaxMonoid<ll>>> st(m+2);
    aux.emplace_back(m+1,n,0);
    suf.emplace_back(m+1,n,0);
    st.modify(m+1,n);
    for(auto [x,y]:a){
        while(get<1>(aux.back())<y)aux.pop_back();
        ll res=1LL*(n-y)*(get<0>(aux.back())-x)+get<2>(aux.back());
        aux.emplace_back(x,y,res);
        suf.emplace_back(x,y,res);
        st.modify(x,y);
    }
    for(auto [x,y,res]:suf)cerr << x << " " << y << " " << res << "\n";
    reverse(all(suf));
    for(auto [x,y]:c){
        auto it=
        auto l=lower_bound(all(pre),T(x,y,0));
        l--;
        auto [x1,y1,res1]=*l;
        ll pos=st.findfirst(x+1,m+1,[&](ll val){return val>=y1;});
        auto r=lower_bound(all(suf),T(pos,0,0));
        auto [x2,y2,res2]=*r;
        ll res=res1+res2+1LL*(x2-x1)*(n-y1);
        cout << res-ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}