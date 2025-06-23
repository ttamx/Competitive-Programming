#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=1<<20;

struct Segtree{
    ll t[K],lz[K];
    void apply(int l,int r,int i,int v){
        t[i]+=v*(r-l+1);
        lz[i]+=v;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,int v){
        update(0,N,1,x,y,v);
    }
    int query(int l,int r,int i,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,m,r,i);
        if(k<=t[i*2])return query(l,m,i*2,k);
        else return query(m+1,r,i*2+1,k-t[i*2]);
    }
    int query(int k){
        return query(0,N,1,k);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.rbegin(),a.rend());
    int ans=N;
    seg.update(0,0,+1);
    for(auto x:a){
        int i=seg.query(1);
        seg.update(i,i,-1);
        seg.update(i+2,i+1+x/2,+1);
        seg.update(i+2,i+1+(x-1)/2,+1);
        ans=min(ans,seg.query(k));
    }
    cout << (ans<N?ans:-1) << "\n";
}