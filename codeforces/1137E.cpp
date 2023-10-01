#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t lll;
typedef pair<ll,ll> p2;

const ll N=3e14+1e9;

ll n,m;

struct line{
    ll m,c,id;
    line(ll m,ll c,ll id):m(m),c(c),id(id){}
    ll get(ll x){
        return (ll)min(lll(1e18),lll(m)*x+c);
    }
};

struct lichaotree{
    struct node;
    typedef node* pnode;
    struct node{
        line val;
        ll lzm,lzc;
        pnode l,r;
        node(line val):val(val),lzm(0),lzc(0),l(nullptr),r(nullptr){}
    };
    pnode rt=nullptr;
    void init(){
        rt=nullptr;
    }
    void pushlz(ll l,ll r,pnode t){
        if(!t)return;
        t->val.c+=t->val.m*t->lzm+t->lzc;
        if(l<r){
            if(t->l){
                t->l->lzm+=t->lzm;
                t->l->lzc+=t->lzc;
            }
            if(t->r){
                t->r->lzm+=t->lzm;
                t->r->lzc+=t->lzc;
            }
        }
        t->lzm=t->lzc=0;
    }
    void update(ll l,ll r,pnode &t,line v){
        pushlz(l,r,t);
        if(!t)return void(t=new node(v));
        if(v.m==t->val.m&&v.c==t->val.c)return void(t->val.id=min(t->val.id,v.id));
        ll m=(l+r)/2;
        if(v.get(m)<t->val.get(m))swap(t->val,v);
        if(l==r)return;
        if(v.get(l)<t->val.get(l))update(l,m,t->l,v);
        if(v.get(r)<t->val.get(r))update(m+1,r,t->l,v);
    }
    void update(ll m,ll c,ll id){
        update(0,N,rt,line(m,c,id));
    }
    void add(ll m,ll c){
        rt->lzm+=m;
        rt->lzc+=c;
    }
    p2 query(ll l,ll r,pnode t,ll x){
        pushlz(l,r,t);
        p2 res=p2(t->val.get(x),t->val.id);
        if(l==r)return res;
        ll m=(l+r)/2;
        if(x<=m&&t->l)return min(res,query(l,m,t->l,x));
        if(x>m&&t->r)return min(res,query(m+1,r,t->r,x));
        return res;
    }
    p2 query(ll x){
        return query(0,N,rt,x);
    }
}lct;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    lct.init();
    lct.update(0,0,1);
    while(m--){
        int t;
        cin >> t;
        if(t==1){
            ll k;
            cin >> k;
            n+=k;
            lct.init();
            lct.update(0,0,1);
            auto [x,y]=lct.query(0);
            cout << y << " " << x << "\n";
        }else if(t==2){
            ll k;
            cin >> k;
            lct.update(n,0,n+1);
            n+=k;
            auto [x,y]=lct.query(0);
            cout << y << " " << x << "\n";
        }else{
            ll b,s;
            cin >> b >> s;
            auto [x,y]=lct.query(s);
            cout << y << " " << x+b << "\n";
            lct.add(s,b);
        }
    }
}