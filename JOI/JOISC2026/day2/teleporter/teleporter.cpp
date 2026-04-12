#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=1e5+5;
const int K=1<<18;
const ll INF=1e18;

int n,m,k;
vector<pair<int,ll>> adj[N];

struct Segtree{
    P t[K];
    ll lz[K];
    void apply(int i,ll v){
        t[i].first+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void pull(int i){
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void build(int l,int r,int i){
        t[i]=P(INF,0);
        lz[i]=0;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(0,n,1);
    }
    void modify(int l,int r,int i,int x,P v){
        if(l==r)return void(t[i]=v);
        push(i);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,P v){
        modify(0,n,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,ll v){
        update(0,n,1,x,y,v);
    }
    P query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return P(INF,0);
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    P query(int x,int y){
        return query(0,n,1,x,y);
    }
}seg;

P calc(ll lambda){
    seg.build();
    seg.modify(0,P(0,0));
    for(int i=1;i<=n;i++){
        if(adj[i].empty())continue;
        P cur(INF,0);
        for(auto [x,c]:adj[i]){
            auto v=seg.query(0,x);
            v.first+=lambda;
            v.second++;
            cur=min(cur,v);
            seg.update(0,x,c);
        }
        seg.modify(i,cur);
    }
    return seg.query(0,n);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<m;i++){
        int l,r,c;
        cin >> l >> r >> c;
        adj[r].emplace_back(l,c);
    }
    for(int i=1;i<=n;i++){
        auto &a=adj[i];
        sort(a.rbegin(),a.rend());
        vector<pair<int,ll>> b;
        for(auto [x,c]:a){
            if(b.empty()||b.back().first!=x){
                b.emplace_back(x,c);
            }else{
                b.back().second+=c;
            }
        }
        a=move(b);
    }
    ll l=0,r=1e14+100;
    while(l<r){
        ll m=(l+r)/2;
        auto [v,c]=calc(m);
        if(c<=k)r=m;
        else l=m+1;
    }
    auto [v,c]=calc(l);
    cout << v-k*l << "\n";
}