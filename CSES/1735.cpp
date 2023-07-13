#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int K=1<<19;

int n,q;
int a[N];

struct segtree{
    ll t[K],lz[K],lz2[K];
    void pushlz(int l,int r,int i){
        int sz=r-l+1;
        if(lz2[i]){
            t[i]=(lz[i]+lz2[i])*sz;
            if(l<r){
                lz[i*2]=lz[i*2+1]=lz[i];
                lz2[i*2]=lz2[i*2+1]=lz2[i];
            }
            lz[i]=lz2[i]=0;
        }else{
            t[i]+=lz[i]*sz;
            if(l<r){    
                lz[i*2]+=lz[i];
                lz[i*2+1]+=lz[i];
            }
            lz[i]=0;
        }
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
    void addval(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        addval(l,m,i*2,x,y,v);
        addval(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void addval(int x,int y,int v){
        addval(1,n,1,x,y,v);
    }
    void setval(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz2[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        setval(l,m,i*2,x,y,v);
        setval(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void setval(int x,int y,int v){
        setval(1,n,1,x,y,v);
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
            int a,b,x;
            cin >> a >> b >> x;
            s.addval(a,b,x);
        }else if(t==2){
            int a,b,x;
            cin >> a >> b >> x;
            s.setval(a,b,x);
        }else{
            int a,b;
            cin >> a >> b;
            cout << s.query(a,b) << "\n";
        }
    }
}