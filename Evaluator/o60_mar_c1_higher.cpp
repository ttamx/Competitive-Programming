#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=1<<21;

int n,k;

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=0);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
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
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int queryleft(int l,int r,int i,int x,int v){
        if(x<l||t[i]<v)return 0;
        if(r<=x){
            while(l<r){
                int m=(l+r)/2;
                if(t[i*2+1]>=v)l=m+1,i=i*2+1;
                else r=m,i=i*2;
            }
            return l;
        }
        int m=(l+r)/2;
        return max(queryleft(l,m,i*2,x,v),queryleft(m+1,r,i*2+1,x,v));
    }
    int queryleft(int x,int v){
        return queryleft(1,n,1,x,v);
    }
    int queryright(int l,int r,int i,int x,int v){
        if(r<x||t[i]<v)return 0;
        if(x<=l){
            while(l<r){
                int m=(l+r)/2;
                if(t[i*2]>=v)r=m,i=i*2;
                else l=m+1,i=i*2+1;
            }
            return l;
        }
        int m=(l+r)/2;
        return max(queryright(l,m,i*2,x,v),queryright(m+1,r,i*2+1,x,v));
    }
    int queryright(int x,int v){
        return queryright(1,n,1,x,v);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    while(k--){
        int x,h;
        cin >> x >> h;
        x++;
    }
}