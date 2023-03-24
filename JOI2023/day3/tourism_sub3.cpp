#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,m,q;
int c[N];

struct node{
    int mn,mx;
    node():mn(2e9),mx(-2e9){}
    node(int mn,int mx):mn(mn),mx(mx){}
    friend node operator+(node a,node b){
        return node(min(a.mn,b.mn),max(a.mx,b.mx));
    }
};

struct segtree{
    node t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(c[l],c[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
    }
    for(int i=1;i<=m;i++)cin >> c[i];
    s.build(1,m,1);
    while(q--){
        int l,r;
        cin >> l >> r;
        auto res=s.query(1,m,1,l,r);
        cout << res.mx-res.mn+1 << '\n';
    }
}