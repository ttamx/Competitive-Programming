#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll p,b,d;
ll a[N];
ll ans=1e18;
map<ll,ll> mp;

struct segtree{
    struct node;
    typedef node* pnode;
    struct node{
        ll val,lz;
        pnode l,r;
        node(ll val=1e18):val(val),lz(0),l(nullptr),r(nullptr){}
    };
    pnode rt;
    segtree():rt(new node()){}
    void pushlz(ll l,ll r,pnode &t){
        t->val+=t->lz;
        if(l<r){
            if(!(t->l))t->l=new node();
            if(!(t->r))t->r=new node();
            t->l->lz+=t->lz;
            t->r->lz+=t->lz;
        }
        t->lz=0;
    }
    void setval(ll l,ll r,pnode &t,ll x,ll v){
        pushlz(l,r,t);
        if(x<l||r<x)return;
        if(l==r)return void(t->val=v);
        ll m=(l+r)/2;
        setval(l,m,t->l,x,v);
        setval(m+1,r,t->r,x,v);
        t->val=min(t->l->val,t->r->val);
    }
    void setval(ll x,ll v){
        setval(0,n+1,rt,x,v);
    }
    void update(ll l,ll r,pnode &t,ll x,ll y,ll v){
        pushlz(l,r,t);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return t->lz+=v,pushlz(l,r,t),void();
        ll m=(l+r)/2;
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        t->val=min(t->l->val,t->r->val);
    }
    void update(ll x,ll y,ll v){
        if(x>y)return;
        update(0,n+1,rt,x,y,v);
    }
    ll query(ll l,ll r,pnode &t,ll x,ll y){
        pushlz(l,r,t);
        if(y<l||r<x)return 1e18;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return min(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    ll query(ll x,ll y){
        if(x>y)return 1e18;
        return query(0,n+1,rt,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> b >> p >> d >> n;
    for(int i=1;i<=n;i++)cin >> a[i],mp[a[i]%p];
    mp[0],mp[b%p];
    ll idx=0;
    for(auto &[x,y]:mp)y=idx++;
    s.setval(0,0);
    a[n+1]=b;
    for(int i=1;i<=n+1;i++){
        ll dif=a[i]-a[i-1];
        ll dmg=(dif-1)/p*d;
        s.update(0,n+1,dmg);
        ll st=a[i-1]%p,ed=a[i]%p;
        if(st<ed){
            s.update(mp[st]+1,mp[ed]-1,d);
        }else{
            s.update(mp[st]+1,n+1,d);
            s.update(0,mp[ed]-1,d);
        }
        if(i>n)break;
        ll res=min(s.query(mp[ed],n+1)-ed,s.query(0,mp[ed]-1)+p-ed);
        s.setval(mp[ed],res+ed);
    }
    for(int i=0;i<=n+1;i++){
        ll pos=a[i]%p;
        ans=min(ans,s.query(mp[pos],mp[pos])-pos);
    }
    cout << ans+b;
}