#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=1<<18;

struct node{
    ll pre,suf,all,mx;
    node():pre(0),suf(0),all(0),mx(0){}
    node(ll x):pre(x),suf(x),all(x),mx(x){}
    node(ll pre,ll suf,ll all,ll mx):pre(pre),suf(suf),all(all),mx(mx){}
    friend node operator+(node l,node r){
        node res;
        res.pre=max(l.pre,l.all+r.pre);
        res.suf=max(r.suf,r.all+l.suf);
        res.all=l.all+r.all;
        res.mx=max({l.mx,r.mx,l.suf+r.pre});
        return res;
    }
};

int n,m;
ll a[N];

struct segtree{
    node t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int &x,ll &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,ll v){
        update(1,n,1,x,v);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build();
    cout << s.t[1].mx << '\n';
    while(m--){
        int x;
        ll y;
        cin >> x >> y;
        x++;
        s.update(x,y);
        cout << s.t[1].mx << '\n';
    }
}