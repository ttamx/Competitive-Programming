#include<bits/stdc++.h>

using namespace std;

const int N=2e5;
const int K=1<<19;

struct segtree{
    pair<int,int> s[K],lz[K];
    void pushlz(int l,int r,int i){
        if(lz[i]==make_pair(0,0))return;
        if(l<r){
            lz[i*2]=lz[i];
            lz[i*2+1]=lz[i];
        }
        s[i]=lz[i];
        lz[i]={0,0};
    }
    pair<int,int> merge(pair<int,int> a,pair<int,int> b){
        return {min(a.first,b.first),max(a.second,b.second)};
    }
    void build(int l,int r,int i){
        if(l==r)return void(s[i]={l,l});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        s[i]=merge(s[i*2],s[i*2+1]);
    }
    void update(int l,int r,int i,int x,int y,pair<int,int> v){
        pushlz(l,r,i);
        if(r<x||y<l)return;
        if(x<=l&&r<=y){
            lz[i]=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        s[i]=merge(s[i*2],s[i*2+1]);
    }
    pair<int,int> query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(r<x||y<l)return;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)/2;
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

int n,m,k;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    s.build(1,n,1);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        pair<int,int> tmp=s.query(1,n,1,l,l);
    }
}