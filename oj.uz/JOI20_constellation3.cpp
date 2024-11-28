#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;

int n,m;
int a[N];
set<tuple<int,int,int>> star[N];
ll sum;

struct MaxSegtree{
    pair<int,int> t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]={a[l],l});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    pair<int,int> query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return {0,0};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    pair<int,int> query(int x,int y){
        return query(1,n,1,x,y);
    }
}smx;

struct LazySegtree{
    ll t[K],lz[K];
    void push(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,ll v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

void merge(set<tuple<int,int,int>> &a,set<tuple<int,int,int>> &b){
    if(a.size()<b.size())swap(a,b);
    for(auto &e:b)a.emplace(e);
    b.clear();
}

pair<ll,int> solve(int l,int r,int h){
    auto [hh,mid]=smx.query(l,r);
    auto &s=star[mid];
    ll lmx=0,rmx=0;
    if(l<mid){
        auto [mx,id]=solve(l,mid-1,hh);
        merge(s,star[id]);
        lmx=mx;
    }
    if(mid<r){
        auto [mx,id]=solve(mid+1,r,hh);
        merge(s,star[id]);
        rmx=mx;
    }
    seg.update(l,mid,rmx);
    seg.update(mid,r,lmx);
    ll res=seg.query(l,r);
    for(auto it=s.begin();it!=s.end()&&get<0>(*it)<=h;it=s.erase(it)){
        auto [y,x,c]=*it;
        res=max(res,seg.query(x,x)+c);
    }
    return {res,mid};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    cin >> m;
    for(int i=1;i<=m;i++){
        int x,y,c;
        cin >> x >> y >> c;
        star[x].emplace(y,x,c);
        sum+=c;
    }
    smx.build();
    cout << sum-solve(1,n,n).first;
}