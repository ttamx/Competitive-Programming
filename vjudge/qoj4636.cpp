#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int M=1e6;
const int K=1<<21;

int n,m;
ll v[N],l[N],r[N];

struct segtree{
    struct node{
        ll l,vl;
        node():l(0),vl(0){}
        node(ll l,ll vl):l(l),vl(vl){}
        friend node operator+(node l,node r){
            return node(l.l+r.l,l.vl+r.vl);
        }
    }t[K];
    void update(int l,int r,int i,int x,node v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=t[i]+v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,ll l,ll vl){
        update(0,M,1,x,node(l,vl));
    }
    pair<ll,ll> query(int l,int r,int i,node v){
        if(l==r)return {v.vl,v.l};
        int m=(l+r)/2;
        if(v.vl+t[i*2+1].vl-(m+1)*(v.l+t[i*2+1].l)>0)
            return query(m+1,r,i*2+1,v);
        return query(l,m,i*2,v+node(t[i*2+1].l,t[i*2+1].vl));
    }
    pair<ll,ll> query(){
        return query(0,M,1,node(r[0],0));
    }
}s;

void upd(int i,int mul){
    s.update(v[i],l[i]*mul,v[i]*l[i]*mul);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> v[i];
    for(int i=0;i<=n;i++)cin >> l[i];
    for(int i=0;i<=n;i++)cin >> r[i];
    for(int i=1;i<=n;i++)upd(i,1);
    auto [x,y]=s.query();
    ll g=gcd(x,y);
    cout << x/g << "/" << y/g << "\n";
    while(m--){
        int t;
        cin >> t;
        if(t==1){
            int i,x,y;
            cin >> i >> x >> y;
            if(i)upd(i,-1);
            l[i]=x,r[i]=y;
            if(i)upd(i,1);
        }else{
            int i,x;
            cin >> i >> x;
            upd(i,-1);
            v[i]=x;
            upd(i,1);
        }
        auto [x,y]=s.query();
        if(x==0)y=1;
        ll g=gcd(x,y);
        cout << x/g << "/" << y/g << "\n";
    }
}