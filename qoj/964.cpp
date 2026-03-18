#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int K=1<<20;
const int INF=INT_MAX/2;

int n,q;
int a[N];
struct Query{int l,r,i;}qr[N];

struct Segtree{
    pair<int,int> t[K];
    int cl[K],cr[K],lz[K];
    void apply(int i,int v){t[i].first+=v,lz[i]+=v;}
    void push(int i){apply(i*2,lz[i]),apply(i*2+1,lz[i]),lz[i]=0;}
    void build(int l,int r,int i){
        if(l==r)return t[i]={-INF,l},cl[i]=INF,cr[i]=-INF,void();
        int m=(l+r)/2;
        build(l,m,i*2),build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void modify(int l,int r,int i,int x){
        if(r<x||x<l)return;
        if(l==r)return t[i]={,l},cl[i]=INF,cr[i]=-INF,void();
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> qr[i].l >> qr[i].r,qr[i].i=i;
    sort(qr+1,qr+q+1);

}