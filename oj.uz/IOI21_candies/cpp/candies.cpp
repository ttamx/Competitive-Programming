#include "candies.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int inf=1e9;
const ll inf2=1e18;

typedef pair<ll,int> p2;

const int N=2e5+5;
const int K=1<<19;

int n,q;
vector<p2> qr[N];

struct segtree{
    struct node{
        p2 mn,mx;
        node(ll val=0,int id=0):mn(val,id),mx(val,id){}
        node(ll mn,ll mx,int id):mn(mn,id),mx(mx,id){}
        node& operator+=(const ll &o){
            mn.first+=o;
            mx.first+=o;
            return *this;
        }
        friend node operator+(node a,node b){
            node c;
            c.mn=min(a.mn,b.mn);
            c.mx=max(a.mx,b.mx);
            return c;
        }
    }t[K];
    ll lz[K];
    void pushlz(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(0,l));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,q,1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,q,1,x,y,v);
    }
    node query(int l,int r,int i,ll c,node res){
        if(l==r)return t[i]+res;
        int m=(l+r)/2;
        pushlz(l,m,i*2);
        pushlz(m+1,r,i*2+1);
        auto res2=res+t[i*2+1];
        if(res2.mx.first-res2.mn.first>=c)return query(m+1,r,i*2+1,c,res);
        return query(l,m,i*2,c,res2);
    }
    node query(ll c){
        return query(1,q,1,c,node(inf2,-inf2,0));
    }
}s;

vector<int> distribute_candies(vector<int> c,vector<int> l,vector<int> r,vector<int> v) {
    n=c.size();
    q=l.size()+2;
    vector<int> ans(n);
    ll sum=0;
    s.build();
    s.update(1,q,inf);
    s.update(2,q,-inf);
    for(int i=0;i<q-2;i++){
        qr[l[i]].emplace_back(v[i],i+3);
        qr[r[i]+1].emplace_back(-v[i],i+3);
    }
    for(int i=0;i<n;i++){
        for(auto [val,id]:qr[i]){
            sum+=val;
            s.update(id,q,val);
        }
        auto tmp=s.query(c[i]);
        if(tmp.mx.second>tmp.mn.second)ans[i]=sum-(tmp.mx.first-c[i]);
        else ans[i]=sum-tmp.mn.first;
    }
    return ans;
}
