#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const ll INF=1e18;

int n,m,q;
vector<pair<int,int>> upd[N];
vector<tuple<int,int,int>> qr[N];
ll ans[N];

struct Node{
    ll pre,suf,sum,ans;
    Node():pre(-INF),suf(-INF),sum(0),ans(-INF){}
    Node(ll x):pre(x),suf(x),sum(x),ans(x){}
    void update(ll x){
        pre+=x,suf+=x,sum+=x,ans+=x;
    }
    friend Node operator+(const Node &l,const Node &r){
        Node res;
        res.ans=max({l.ans,r.ans,l.suf+r.pre});
        res.pre=max(l.pre,l.sum+r.pre);
        res.suf=max(r.suf,l.suf+r.sum);
        res.sum=l.sum+r.sum;
        return res;
    };
};

struct SegTree{
    Node t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(0LL));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,m,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return t[i].update(v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int v){
        update(1,m,1,x,v);
    }
    Node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(1,m,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int l,r,x;
        cin >> l >> r >> x;
        upd[l].emplace_back(i,x);
        upd[r+1].emplace_back(i,-x);
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int x,l,r;
        cin >> x >> l >> r;
        qr[x].emplace_back(l,r,i);
    }
    seg.build();
    for(int i=1;i<=n;i++){
        for(auto [j,x]:upd[i]){
            seg.update(j,x);
        }
        for(auto [l,r,j]:qr[i]){
            ans[j]=seg.query(l,r).ans;
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}