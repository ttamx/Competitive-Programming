#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=(1<<19)+5;

int n,q;
int a[N];

struct segtree{
    struct node{
        int pre,suf,sum,mx;
        node(int x=0):pre(x),suf(x),sum(x),mx(x){}
        friend node operator+(node l,node r){
            node res;
            res.pre=max(l.pre,l.sum+r.pre);
            res.suf=max(l.suf+r.sum,r.suf);
            res.sum=l.sum+r.sum;
            res.mx=max({l.mx,r.mx,l.suf+r.pre});
            return res;
        }
    }t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(a[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return node(0);
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    int query(int x,int y){
        return query(1,n,1,x,y).mx;
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;++i)cin >> a[i];
    s.build();
    while(q--){
        int x,y;
        cin >> x >> y;
        x++,y++;
        cout << s.query(x,y) << "\n";
    }
}