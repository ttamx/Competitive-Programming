#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;
const int B=17;

int n,q;
int a[N];

struct Node{
    int l,r,v,lz;
}pool[40000000];

int buf;

struct Segtree{
    int root;
    Segtree():root(++buf){}
    void apply(int l,int r,int &i,int v){
        if(!i)i=++buf;
        pool[i].v+=v*(r-l+1);
        pool[i].lz+=v;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,pool[i].l,pool[i].lz);
        apply(m+1,r,pool[i].r,pool[i].lz);
        pool[i].lz=0;
    }
    void pull(int i){
        pool[i].v=pool[pool[i].l].v+pool[pool[i].r].v;
    }
    void update(int l,int r,int &i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,pool[i].l,x,y,v);
        update(m+1,r,pool[i].r,x,y,v);
        pull(i);
    }
    void update(int x,int y,int v){
        update(0,N,root,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x||!i)return 0;
        if(x<=l&&r<=y)return pool[i].v;
        int m=(l+r)/2;
        push(l,m,r,i);
        return query(l,m,pool[i].l,x,y)+query(m+1,r,pool[i].r,x,y);
    }
    int query(int x,int y){
        return query(0,N,root,x,y);
    }
};

struct Wavelet{
    Segtree t[K];
    void update(int l,int r,int v,int d){
        int i=1;
        for(int b=B-1;b>=0;b--){
            if(v>>b&1){
                i=i*2+1;
            }else{
                t[i].update(l,r,d);
                i=i*2;
            }
        }
    }
    int query(int l,int r,int k){
        int res=0,i=1;
        for(int b=B-1;b>=0;b--){
            int cnt=t[i].query(l,r);
            if(k>cnt){
                k-=cnt;
                i=i*2+1;
                res|=1<<b;
            }else{
                i=i*2;
            }
        }
        return res;
    }
}seg;

map<int,pair<int,int>> dat;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    seg.update(0,n-1,0,+1);
    dat[n-1]={0,0};
    while(q--){
        int op,l,r,k;
        cin >> op >> l >> r >> k;
        if(op==1){
            auto it=dat.lower_bound(l);
            {
                auto &[p,v]=it->second;
                if(p<l){
                    dat[l-1]={p,v};
                    p=l;
                }
            }
            for(;it!=dat.end()&&it->first<=r;it=dat.erase(it)){
                auto [cl,v]=it->second;
                int cr=it->first;
                seg.update(cl,cr,v,-1);
            }
            if(it!=dat.end()){
                auto &[p,v]=it->second;
                if(p<=r){
                    seg.update(p,r,v,-1);
                    p=r+1;
                }
            }
            dat[r]={l,k};
            seg.update(l,r,k,+1);
        }else{
            cout << seg.query(l,r,k) << "\n";
        }
    }
}