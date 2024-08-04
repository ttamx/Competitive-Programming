#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,q;

struct Segtree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    template<class F>
    int findfirst(int l,int r,int i,int x,int y,F f){
        if(y<l||r<x||!f(t[i]))return n+1;
        if(l==r)return l;
        push(i);
        int m=(l+r)/2;
        int res=findfirst(l,m,i*2,x,y,f);
        if(res==n+1)res=findfirst(m+1,r,i*2+1,x,y,f);
        return res;
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==2){
            int x;
            cin >> x;
            cout << s.findfirst(0,n-1,1,x,n-1,[](int v){return v<1;}) << "\n";
        }else{
            int x,y;
            cin >> x >> y;
            s.update(0,n-1,1,x,y-1,t==1?1:-1);
        }
    }
}