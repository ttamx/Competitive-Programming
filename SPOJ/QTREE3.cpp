#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,q;
int col[N];
vector<int> adj[N];
int pa[N],lv[N],sz[N],hv[N],hd[N],pos[N],pid;

struct segtree{
    pair<int,int> t[K];
    void build(int l,int r,int i){
        t[i]={2e9,-1};
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,pair<int,int> v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,pair<int,int> v){
        update(1,n,1,x,v);
    }
    pair<int,int> query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return {2e9,-1};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    pair<int,int> query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

void dfs(int u,int p=0){
    sz[u]=1;
    lv[u]=lv[p]+1;
    pa[u]=p;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p,int h){
    pos[u]=++pid;
    hd[u]=h;
    if(hv[u])hld(hv[u],u,h);
    for(auto v:adj[u]){
        if(v==hv[u]||v==p)continue;
        hld(v,u,v);
    }
}

int queryup(int st,int ed){
    pair<int,int> res={2e9,2e9};
    while(hd[st]!=hd[ed]){
        res=min(res,s.query(pos[hd[st]],pos[st]));
        st=pa[hd[st]];
    }
    res=min(res,s.query(pos[ed],pos[st]));
    return res.second;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1,0,1);
    s.build();
    while(q--){
        int o,x;
        cin >> o >> x;
        if(o==0){
            col[x]^=1;
            if(col[x])s.update(pos[x],{lv[x],x});
            else s.update(pos[x],{2e9,-1});
        }else{
            cout << queryup(x,1) << '\n';
        }
    }
}