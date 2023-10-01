#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,q;
vector<int> adj[N];
int l[N],r[N];
int t=0;

struct segtree{
    bool t[K],lz[K];
    void pushlz(int l,int r,int i){
        t[i]^=lz[i];
        if(l<r){
            lz[i*2]^=lz[i];
            lz[i*2+1]^=lz[i];
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
        t[i]=t[i*2]^t[i*2+1];
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    bool query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)^query(m+1,r,i*2+1,x,y);
    }
    bool query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

void dfs(int u,int p){
    l[u]=++t;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
    r[u]=t;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<n;++i){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,1);
    while(q--){
        int z,x;
        cin >> z >> x;
        if(z==1)s.update(l[x],r[x],1);
        if(z==2)cout << s.query(l[x],l[x]) << '\n';
    }
}
