#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int K=(1<<19)+5;

int n,m;
vector<pair<int,int>> vec[N];

struct segtree{
    ll t[K],lz[K];
    void pushlz(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]+=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,ll v){
        update(0,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return -1e18;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(0,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int l,r,w;
        cin >> l >> r >> w;
        vec[r].emplace_back(l,w);
    }
    for(int i=1;i<=n;i++){
        s.update(i,i,s.query(0,i-1));
        for(auto [l,w]:vec[i])s.update(l,i,w);
    }
    cout << s.query(0,n);
}