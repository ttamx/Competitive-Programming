#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,q;
int w[N];
int sz[N],lv[N],pa[N][20];
int idx=1;
int val[N],head[N],pos[N];
vector<int> adj[N];

struct segtree{
    int s[K];
    void build(int l,int r,int i){
        if(l==r)return void(s[i]=val[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        s[i]=s[i*2]+s[i*2+1];
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r)return void(s[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        s[i]=s[i*2]+s[i*2+1];
    }
    int query(int l,int r,int i,int x,int y){
        if(r<x||y<l)return 0;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}seg;

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

void hld(int u,int p){
    int mxsz=0,mxid=-1;
    val[idx]=w[u];
    pos[u]=idx++;
    for(auto v:adj[u]){
        if(v==p)continue;
        if(sz[v]>mxsz){
            mxsz=sz[v];
            mxid=v;
        }
    }
    if(mxid!=-1){
        head[mxid]=head[u];
        hld(mxid,u);
    }
    for(auto v:adj[u]){
        if(v==p||v==mxid)continue;
        head[v]=v;
        hld(v,u);
    }
}

int queryup(int u,int v){
    int ret=0;
    while(head[u]!=head[v]){
        ret+=seg.query(1,n,1,pos[head[u]],pos[u]);
        u=pa[head[u]][0];
    }
    ret+=seg.query(1,n,1,pos[v],pos[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)pa[j][i]=pa[pa[j][i-1]][i-1];
    head[1]=1;
    hld(1,0);
    seg.build(1,n,1);
    while(q--){
        int o,x,y;
        cin >> o >> x >> y;
        if(o==1){
            seg.update(1,n,1,x,y);
        }else{
            int l=lca(x,y);
            cout << queryup(x,l)+queryup(y,l)-w[l];
        }
    }
}