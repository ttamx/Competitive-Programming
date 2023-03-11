#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=(1<<19)+5;

struct node{
    int s,l,r,m;
}t[M];

node sum(node l,node r){
    node ret;
    ret.s=l.s+r.s;
    ret.l=max(l.l,l.s+r.l);
    ret.r=max(r.r,l.r+r.s);
    ret.m=max({l.m,r.m,l.r+r.l});
    return ret;
}

int n,q;
int a[N];

void build(int l,int r,int i){
    if(l==r){
        t[i]={a[l],a[l],a[l],a[l]};
        return;
    }
    int m=(l+r)/2;
    build(l,m,i*2);
    build(m+1,r,i*2+1);
    t[i]=sum(t[i*2],t[i*2+1]);
    return;
}

node query(int l,int r,int i,int ql,int qr){
    if(qr<l || ql>r)return {0,0,0,0};
    if(ql<=l && r<=qr)return t[i];
    int m=(l+r)/2;
    return sum(query(l,m,i*2,ql,qr),query(m+1,r,i*2+1,ql,qr));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;++i){
        cin >> a[i];
    }
    build(1,n,1);
    while(q--){
        int x,y;
        cin >> x >> y;
        cout << query(1,n,1,++x,++y).m << '\n';
    }
}

