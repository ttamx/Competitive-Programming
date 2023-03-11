#include<bits/stdc++.h>

using namespace std;

const int M=1e6+6;
const int N=1005;
const int K=1<<21;

int n,m,p;
vector<pair<int,int>> v[N];

struct segtree{
    int t[K],lz[K];
    void pushlz(int l,int r,int i){
        t[i]=max(t[i],lz[i]);
        if(l<r){
            lz[i*2]=max(lz[i*2],lz[i]);
            lz[i*2+1]=max(lz[i*2+1],lz[i]);
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            lz[i]=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,int i){
        update(1,m,1,x,y,i);
    }
    int query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,m,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> p;
    for(int i=0;i<p;i++){
        int x,y,z;
        cin >> x >> y >> z;
        v[y].emplace_back(x,z);
    }
    for(int i=1;i<=n;i++){
        vector<pair<int,int>> res;
        for(auto [x,y]:v[i]){
            res.emplace_back(s.query())
        }
    }
}