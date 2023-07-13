#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=1<<18;

int n,q;
int a[N];

struct segtree{
    struct lazy{
        ll add,dif;
        bool rst;
        lazy(ll add=0,ll dif=0,bool rst=false):add(add),dif(dif),rst(rst){}
        void clear(){
            *this=lazy();
        }
        ll calc(int l,int r,int i){
            ll sz=r-l+1;
            return add*sz+dif*sz*(sz-1)/2;
        }
        lazy& operator+=(lazy rhs){
            add+=rhs.add;
            dif+=rhs.dif;
            rst|=rhs.rst;
            return *this;
        }
    }lz[K];
    ll t[K];
    void pushlz(int l,int r,int i){
        if(lz[i].rst){
            t[i]=lz[i].calc(l,r,i);
            if(l<r){
                lz[i*2]=lz[i*2+1]=lz[i];
                int m=(l+r)/2;
                lz[i*2+1].add+=lz[i].dif*(m-l+1);
            }
        }else{
            t[i]+=lz[i].calc(l,r,i);
            if(l<r){
                lz[i*2]+=lz[i];
                lz[i*2+1]+=lz[i];
                int m=(l+r)/2;
                lz[i*2+1].add+=lz[i].dif*(m-l+1);
            }
        }
        lz[i].clear();
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,ll add,ll dif){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=lazy(add+(l-x)*dif,dif),pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,add,dif);
        update(m+1,r,i*2+1,x,y,add,dif);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll add,ll dif=0ll){
        update(1,n,1,x,y,add,dif);
    }
    void resetval(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=lazy(0,0,true),pushlz(l,r,i),void();
        int m=(l+r)/2;
        resetval(l,m,i*2,x,y);
        resetval(m+1,r,i*2+1,x,y);
        t[i]=t[i*2]+t[i*2+1];
    }
    void resetval(int x,int y){
        resetval(1,n,1,x,y);
    }
    ll query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0ll;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build();
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r,w;
            cin >> l >> r >> w;
            int st=max(1,l-w+1);
            int ed=min(r+w-1,n);
            int val=w-(l-st);
            s.update(st,l-1,val,1);
            s.update(l,r-1,w);
            s.update(r,ed,w,-1);
        }else{
            int x;
            cin >> x;
            cout << s.query(x,x) << "\n";
            s.resetval(x,x);
        }
    }
}