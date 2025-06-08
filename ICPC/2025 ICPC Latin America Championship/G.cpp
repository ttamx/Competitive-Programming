#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll L=2e18;

struct Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll mn,mx,lz;
        Ptr l,r;
        Node():mn(0),mx(0),lz(0),l(),r(){}
    };
    Ptr root=new Node();
    void apply(Ptr &t,ll v){
        if(!t)t=new Node();
        t->mn+=v;
        t->mx+=v;
        t->lz+=v;
    }
    void push(Ptr t){
        apply(t->l,t->lz);
        apply(t->r,t->lz);
        t->lz=0;
    }
    void pull(Ptr t){
        t->mn=min(t->l->mn,t->r->mn);
        t->mx=max(t->l->mx,t->r->mx);
    }
    void update(ll l,ll r,Ptr &t,ll x,ll y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(t,v);
        ll m=(l+r)/2;
        push(t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        pull(t);
    }
    void update(ll x,ll y,ll v){
        update(1,L,root,x,y,v);
    }
    pair<ll,ll> query(ll l,ll r,Ptr &t,ll x,ll y){
        if(y<l||r<x)return {L,0LL};
        if(x<=l&&r<=y)return {t->mn,t->mx};
        ll m=(l+r)/2;
        push(t);
        auto [mn1,mx1]=query(l,m,t->l,x,y);
        auto [mn2,mx2]=query(m+1,r,t->r,x,y);
        return {min(mn1,mn2),max(mx1,mx2)};
    }
    pair<ll,ll> query(ll x,ll y){
        return query(1,L,root,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        char c;
        ll x,len;
        cin >> c >> len >> x;
        if(c=='|'){
            seg.update(x,x,len);
            cout << "S";
        }else{
            auto [mn,mx]=seg.query(x,x+len-1);
            if(mn==mx){
                seg.update(x,x+len-1,+1);
                cout << "S";
            }else{
                cout << "U";
            }
        }
    }
}