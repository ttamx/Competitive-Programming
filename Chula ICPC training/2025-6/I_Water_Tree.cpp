#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int K=1<<20;

int n,q;
vector<int> adj[N];
int par[N],tin[N],tout[N];
int timer=0;
int upd[N];

void dfs(int u){
    tin[u]=++timer;
    for(auto v:adj[u]){
        if(v==par[u])continue;
        par[v]=u;
        dfs(v);
    }
    tout[u]=timer;
}

struct Segtree{
    int t[K];
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        t[i]=max(t[i],v);
        if(l==r)return;
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

struct Segtree2{
    int t[K];
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return void(t[i]=max(t[i],v));
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x){
        if(x<l||r<x)return 0;
        if(l==r)return t[i];
        int m=(l+r)/2;
        return max({t[i],query(l,m,i*2,x),query(m+1,r,i*2+1,x)});
    }
    int query(int x){
        return query(1,n,1,x);
    }
}seg2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    cin >> q;
    for(int i=1;i<=q;i++){
        int op,u;
        cin >> op >> u;
        if(op==1){
            seg2.update(tin[u],tout[u],i);
        }else if(op==2){
            seg.update(tin[u],i);
        }else{
            cout << (seg.query(tin[u],tout[u])<seg2.query(tin[u])) << "\n";
        }
    }
}