#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;

struct Segtree{
    ll t[K],lz[K];
    void apply(int l,int r,int i,ll v){
        t[i]+=v*(r-l+1);
        lz[i]+=v;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=0;
    }
    void build(int l,int r,int i){
        lz[i]=0,t[i]=0;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        seg.build(1,n,1);
        while(q--){
            int op,l,r;
            cin >> op >> l >> r;
            if(op==0){
                ll v;
                cin >> v;
                seg.update(1,n,1,l,r,v);
            }else{
                cout << seg.query(1,n,1,l,r) << "\n";
            }
        }
    }
}