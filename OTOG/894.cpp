#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 rng(time(nullptr));

int n,q;
map<int,ll> mp;

struct treap{
    struct node{
        ll val,sum;
        int prio,sz;
        node *l,*r;
        node(ll val):val(val),prio(rng()),sz(1),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt;
    treap():rt(nullptr){}
    ll sum(pnode t){
        return t?t->sum:0ll;
    }
    int sz(pnode t){
        return t?t->sz:0;
    }
    void upd(pnode t){
        if(!t)return;
        t->sum=sum(t->l)+sum(t->r)+t->val;
        t->sz=sz(t->l)+sz(t->r)+1;
    }
    void merge(pnode &t,pnode l,pnode r){
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void splitkey(pnode t,pnode &l,pnode &r,ll key){
        if(!t)return void(l=r=t);
        if(t->val<=key)splitkey(t->r,t->r,r,key),l=t;
        else splitkey(t->l,l,t->l,key),r=t;
        upd(t);
    }
    void splitsz(pnode t,pnode &l,pnode &r,int key){
        if(!t)return void(l=r=t);
        if(sz(t->l)+1<=key)splitsz(t->r,t->r,r,key-sz(t->l)-1),l=t;
        else splitsz(t->l,l,t->l,key),r=t;
        upd(t);
    }
    void insert(ll val){
        pnode t1,t2;
        splitkey(rt,t1,t2,val);
        merge(rt,t1,new node(val));
        merge(rt,rt,t2);
    }
    void erase(ll val){
        pnode t1,t2,t3;
        splitkey(rt,t1,t2,val-1);
        splitsz(t2,t2,t3,1);
        delete t2;
        merge(rt,t1,t3);
    }
    ll query(ll l,ll r){
        pnode t1,t2,t3;
        splitkey(rt,t1,t2,l-1);
        splitkey(t2,t2,t3,r);
        ll res=sum(t2);
        merge(rt,t1,t2);
        merge(rt,rt,t3);
        return res;
    }
};

struct segtree{
    struct node{
        treap val;
        node *l,*r;
        node():val(),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt;
    segtree():rt(nullptr){}
    void update(int l,int r,pnode &t,int &x,ll &v){
        if(!t)t=new node();
        if(mp.find(x)!=mp.end())t->val.erase(mp[x]);
        t->val.insert(v);
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
    }
    void update(int x,ll v){
        update(1,n,rt,x,v);
        mp[x]=v;
    }
    ll query(int l,int r,pnode &t,int &x,int &y,ll &a,ll &b){
        if(y<l||r<x||!t)return 0ll;
        if(x<=l&&r<=y)return t->val.query(a,b);
        int m=(l+r)/2;
        return query(l,m,t->l,x,y,a,b)+query(m+1,r,t->r,x,y,a,b);
    }
    ll query(int x,int y,ll a,ll b){
        return query(1,n,rt,x,y,a,b);
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
            s.update(x,v);
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