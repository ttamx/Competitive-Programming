#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int K=1<<20;

int n,q;
string s;

struct segtree{
    struct node{
        int wpre,bpre,wsuf,bsuf,wans,bans,sz;
        node(){
            wpre=bpre=wsuf=bsuf=wans=bans=sz=0;
        }
        node(int x){
            wpre=wsuf=wans=x;
            bpre=bsuf=bans=x^1;
            sz=1;
        }
        void flip(){
            swap(wpre,bpre);
            swap(wsuf,bsuf);
            swap(wans,bans);
        }
        friend node operator+(node l,node r){
            node res;
            res.wpre=l.wpre<l.sz?l.wpre:l.sz+r.wpre;
            res.bpre=l.bpre<l.sz?l.bpre:l.sz+r.bpre;
            res.wsuf=r.wsuf<r.sz?r.wsuf:r.sz+l.wsuf;
            res.bsuf=r.bsuf<r.sz?r.bsuf:r.sz+l.bsuf;
            res.wans=max({l.wans,r.wans,l.wsuf+r.wpre});
            res.bans=max({l.bans,r.bans,l.bsuf+r.bpre});
            res.sz=l.sz+r.sz;
            return res;
        }
    }t[K];
    bool lz[K];
    void pushlz(int l,int r,int i){
        if(!lz[i])return;
        t[i].flip();
        if(l<r){
            lz[i*2]^=true;
            lz[i*2+1]^=true;
        }
        lz[i]=false;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(s[l-1]-'0'));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=true,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y);
        update(m+1,r,i*2+1,x,y);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y){
        update(1,n,1,x,y);
    }
    node query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    node query(int x,int y){
        return query(1,n,1,x,y);
    }
}st;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    st.build();
    while(q--){
        int c,l,r;
        cin >> c >> l >> r;
        if(c==1){
            st.update(l,r);
        }else{
            cout << st.query(l,r).wans << "\n";
        }
    }
}