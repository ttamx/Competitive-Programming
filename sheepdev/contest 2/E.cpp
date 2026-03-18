#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=1<<20;
const ll INF=1e18;

int n,q;

struct Segtree{
    struct Node{
        ll ans,mx,mx2,add,addhist,add2,addhist2;
        Node():ans(0LL),mx(0LL),mx2(-INF),add(0LL),addhist(0LL),add2(0LL),addhist2(0LL){}
        void push_add(ll v,ll vh,ll v2,ll vh2){
            ans=max({ans,mx+vh,mx2+vh2});
            addhist=max(addhist,add+vh);
            addhist2=max(addhist2,add2+vh2);
            add+=v;
            add2+=v2;
            mx+=v;
            mx2+=v2;
        }
    }t[K];
    void push(int i){
        ll mx=t[i].mx-t[i].add;
        t[i*2].push_add(mx==t[i*2].mx?t[i].add:t[i].add2,mx==t[i*2].mx?t[i].addhist:t[i].addhist2,t[i].add2,t[i].addhist2);
        t[i*2+1].push_add(mx==t[i*2+1].mx?t[i].add:t[i].add2,mx==t[i*2+1].mx?t[i].addhist:t[i].addhist2,t[i].add2,t[i].addhist2);
        t[i].add=t[i].addhist=t[i].add2=t[i].addhist2=0;
    }
    void pull(int i){
        Node &p=t[i],l=t[i*2],r=t[i*2+1];
        p.ans=max(l.ans,r.ans);
        if(l.mx>r.mx){
            p.mx=l.mx;
            p.mx2=max(l.mx2,r.mx);
        }else if(r.mx>l.mx){
            p.mx=r.mx;
            p.mx2=max(l.mx,r.mx2);
        }else{
            p.mx=l.mx;
            p.mx2=max(l.mx2,r.mx2);
        }
    }
    void build(int l,int r,int i){
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void range_add(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return t[i].push_add(v,max(v,0LL),v,max(v,0LL));
        push(i);
        int m=(l+r)/2;
        range_add(l,m,i*2,x,y,v);
        range_add(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_chmin(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x||t[i].mx<=v)return;
        if(x<=l&&r<=y&&t[i].mx2<v)return t[i].push_add(v-t[i].mx,0,0,0);
        push(i);
        int m=(l+r)/2;
        range_chmin(l,m,i*2,x,y,v);
        range_chmin(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i].ans;
        push(i);
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    seg.build(1,n,1);
    while(q--){
        int op,l,r,v;
        cin >> op >> l >> r;
        if(op==1){
            cin >> v;
            seg.range_add(1,n,1,l,r,v);
        }else if(op==2){
            cin >> v;
            seg.range_chmin(1,n,1,l,r,v);
        }else{
            cout << seg.query(1,n,1,l,r) << "\n";
        }
    }
}