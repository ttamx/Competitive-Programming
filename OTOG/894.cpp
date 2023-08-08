#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int inf=1e9;

int n,q;
map<ll,ll> mp;

struct segtree{
    struct node{
        ll val;
        node *l,*r;
        node():val(),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt;
    segtree():rt(nullptr){}
    void update(ll l,ll r,pnode &t,ll &x,ll &v){
        if(!t)t=new node();
        t->val+=v;
        if(l==r)return;
        ll m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
    }
    void update(ll x,ll v){
        update(1,inf,rt,x,v);
    }
    ll query(ll l,ll r,pnode &t,ll &x,ll &y){
        if(y<l||r<x||!t)return 0ll;
        if(x<=l&&r<=y)return t->val;
        ll m=(l+r)/2;
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    ll query(ll x,ll y){
        return query(1,inf,rt,x,y);
    }
};

struct segtree2d{
    struct node{
        segtree val;
        node *l,*r;
        node():val(),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt;
    segtree2d():rt(nullptr){}
    void update(ll l,ll r,pnode &t,ll &x,ll &y,ll &v){
        if(!t)t=new node();
        t->val.update(y,v);
        if(l==r)return;
        ll m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,y,v);
        else update(m+1,r,t->r,x,y,v);
    }
    void update(ll x,ll y,ll v){
        update(1,inf,rt,x,y,v);
    }
    ll query(ll l,ll r,pnode &t,ll &x,ll &y,ll &a,ll &b){
        if(y<l||r<x||!t)return 0ll;
        if(x<=l&&r<=y)return t->val.query(a,b);
        ll m=(l+r)/2;
        return query(l,m,t->l,x,y,a,b)+query(m+1,r,t->r,x,y,a,b);
    }
    ll query(ll x,ll y,ll a,ll b){
        return query(1,inf,rt,x,y,a,b);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    ll ans=-1;
    auto f=[&](ll x){
        return x==-1?0:abs((x-69)%min(420,n/8+1));
    };
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,v;
            cin >> x >> v;
            if(mp[x])s.update(x,mp[x],-mp[x]);
            s.update(x,v,v);
            mp[x]=v;
        }else{
            int x,y,a,b;
            cin >> x >> y >> a >> b;
            x+=f(ans);
            y+=f(ans);
            x=min(x,n);
            y=min(y,n);
            ans=s.query(x,y,a,b);
            cout << ans << "\n";
        }
    }
}