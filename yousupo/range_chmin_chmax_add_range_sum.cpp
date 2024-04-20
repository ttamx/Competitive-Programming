#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

const int N=2e5+5;
const int K=1<<19;

int n,q;
ll a[N];

struct SegTree{
    struct Node{
        ll sum,add;
        ll mn,mn2,fn;
        ll mx,mx2,fx;
        Node(){
            sum=add=fn=fx=0,mn=mn2=INF,mx=mx2=-INF;
        }
        Node(ll v){
            sum=mn=mx=v,add=0,mn2=INF,mx2=-INF,fn=fx=1;
        }
        friend Node operator+(const Node &l,const Node &r){
            Node res;
            res.sum=l.sum+r.sum;
            res.add=0;
            if(l.mx>r.mx){
                res.mx=l.mx,res.fx=l.fx;
                res.mx2=max(l.mx2,r.mx);
            }else if(r.mx>l.mx){
                res.mx=r.mx,res.fx=r.fx;
                res.mx2=max(r.mx2,l.mx);
            }else{
                res.mx=l.mx,res.fx=l.fx+r.fx;
                res.mx2=max(l.mx2,r.mx2);
            }
            if(l.mn<r.mn){
                res.mn=l.mn,res.fn=l.fn;
                res.mn2=min(l.mn2,r.mn);
            }else if(r.mn<l.mn){
                res.mn=r.mn,res.fn=r.fn;
                res.mn2=min(r.mn2,l.mn);
            }else{
                res.mn=l.mn,res.fn=l.fn+r.fn;
                res.mn2=min(l.mn2,r.mn2);
            }
            return res;
        }
        void apply(int l,int r,ll v){
            sum+=(r-l+1)*v;
            mx+=v,mx2+=v;
            mn+=v,mn2+=v;
            add+=v;
        }
        void chmin(ll v){
            if(v>=mx)return;
            sum+=(v-mx)*fx;
            if(mn==mx)mn=v;
            if(mn2==mx)mn2=v;
            mx=v;
        }
        void chmax(ll v){
            if(v<=mn)return;
            sum+=(v-mn)*fn;
            if(mx==mn)mx=v;
            if(mx2==mn)mx2=v;
            mn=v;
        }
    }t[K];
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void push(int l,int r,int i){
        int m=(l+r)/2;
        t[i*2].apply(l,m,t[i].add);
        t[i*2+1].apply(m+1,r,t[i].add);
        t[i*2].chmin(t[i].mx);
        t[i*2+1].chmin(t[i].mx);
        t[i*2].chmax(t[i].mn);
        t[i*2+1].chmax(t[i].mn);
        t[i].add=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(a[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(1,n,1);
    }
    void range_add(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return t[i].apply(l,r,v);
        int m=(l+r)/2;
        push(l,r,i);
        range_add(l,m,i*2,x,y,v);
        range_add(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_add(int x,int y,ll v){
        range_add(1,n,1,x,y,v);
    }
    void range_chmin(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x||t[i].mx<=v)return;
        if(x<=l&&r<=y&&t[i].mx2<v)return t[i].chmin(v);
        int m=(l+r)/2;
        push(l,r,i);
        range_chmin(l,m,i*2,x,y,v);
        range_chmin(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_chmin(int x,int y,ll v){
        range_chmin(1,n,1,x,y,v);
    }
    void range_chmax(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x||t[i].mn>=v)return;
        if(x<=l&&r<=y&&t[i].mn2>v)return t[i].chmax(v);
        int m=(l+r)/2;
        push(l,r,i);
        range_chmax(l,m,i*2,x,y,v);
        range_chmax(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void range_chmax(int x,int y,ll v){
        range_chmax(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i].sum;
        int m=(l+r)/2;
        push(l,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build();
    while(q--){
        int o,l,r;
        cin >> o >> l >> r;
        l++;
        if(o==3){
            cout << s.query(l,r) << "\n";
        }else{
            ll v;
            cin >> v;
            if(o==0){
                s.range_chmin(l,r,v);
            }else if(o==1){
                s.range_chmax(l,r,v);
            }else{
                s.range_add(l,r,v);
            }
        }
    }
}