#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

int n,q;
int a[N];
vector<int> adj[N];
int lv[N],sz[N],hv[N],hd[N],pos[N],idx,pa[N];

struct segtree{
    int t[K];
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

void dfs(int u,int p=0){
    pa[u]=p;
    lv[u]=lv[p]+1;
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p,int h){
    pos[u]=++idx;
    hd[u]=h;
    if(hv[u])hld(hv[u],u,h);
    for(auto v:adj[u]){
        if(v==p||v==hv[u])continue;
        hld(v,u,v);
    }
}

int queryup(int u,int v){
    int res=0;
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        res=max(res,s.query(1,n,1,pos[hd[u]],pos[u]));
        u=pa[hd[u]];
    }
    if(lv[u]>lv[v])swap(v,u);
    res=max(res,s.query(1,n,1,pos[u],pos[v]));
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1,0,1);
    for(int i=1;i<=n;i++)s.update(1,n,1,pos[i],a[i]);
    while(q--){
        int o,x,y;
        cin >> o >> x >> y;
        if(o==1)s.update(1,n,1,pos[x],y);
        else cout << queryup(x,y) << ' ';
    }
}