#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

struct segtree{
    struct node{
        char l[2],r[2];
        int sz;
        bool ok;
        node():sz(0){}
        node(char c){
            l[0]=r[0]=c;
            sz=1;
            ok=true;
        }
        friend node operator+(node l,node r){
            if(l.sz==0)return r;
            if(r.sz==0)return l;
            node res;
            res.l[0]=l.l[0];
            res.r[0]=r.r[0];
            res.ok=l.ok&&r.ok;
            res.sz=l.sz+r.sz;
            if(l.sz==1)res.l[1]=r.l[0];
            else res.l[1]=l.l[1];
            if(r.sz==1)res.r[1]=l.r[0];
            else res.r[1]=r.r[1];
            if(l.r[0]==r.l[0])res.ok=false;
            if(l.sz>1&&l.r[1]==r.l[0])res.ok=false;
            if(r.sz>1&&r.l[1]==l.r[0])res.ok=false;
            return res;
        };
    }t[K];
    int lz[K];
    void rot(char &c,int x){
        c=(c-'a'+x)%26+'a';
    }
    void pushlz(int l,int r,int i){
        rot(t[i].l[0],lz[i]);
        rot(t[i].r[0],lz[i]);
        if(l<r){
            rot(t[i].l[1],lz[i]);
            rot(t[i].r[1],lz[i]);
            lz[i*2]+=lz[i],lz[i*2]%=26;
            lz[i*2+1]+=lz[i],lz[i*2+1]%=26;
        }
        lz[i]=0;
    }
    void build(int l,int r,int i,string &s){
        lz[i]=0;
        if(l==r)return t[i]=node(s[l-1]),void();
        int m=(l+r)/2;
        build(l,m,i*2,s);
        build(m+1,r,i*2+1,s);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    node query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}st;

void runcase(){
    int n,m;
    cin >> n >> m;
    string s;
    cin >> s;
    st.build(1,n,1,s);
    while(m--){
        int t;
        cin >> t;
        if(t==1){
            int l,r,x;
            cin >> l >> r >> x;
            st.update(1,n,1,l,r,x%26);
        }else{
            int l,r;
            cin >> l >> r;
            cout << (st.query(1,n,1,l,r).ok?"YES":"NO") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}