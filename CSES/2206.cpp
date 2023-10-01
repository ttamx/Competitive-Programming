#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<19;

int n,q;

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=INT_MAX);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INT_MAX;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}sl,sr;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    sl.build();
    sr.build();
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        sl.update(i,x-i);
        sr.update(i,x+i);
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int k,x;
            cin >> k >> x;
            sl.update(k,x-k);
            sr.update(k,x+k);
        }else{
            int k;
            cin >> k;
            cout << min(sl.query(1,k)+k,sr.query(k,n)-k) << "\n";
        }
    }
}