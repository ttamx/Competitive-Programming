#include<bits/stdc++.h>

using namespace std;

const int N=1e4+5;
const int K=1<<15;

int n;
int w[N];
int sz[N],lv[N],pa[N][20];
int idx;
int val[N],head[N],pos[N],posid[N];
vector<tuple<int,int,int>> adj[N];

struct segtree{
    int s[K];
    void build(int l,int r,int i){
        if(l==r)return void(s[i]=val[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        s[i]=max(s[i*2],s[i*2+1]);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r)return void(s[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        s[i]=max(s[i*2],s[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(r<x||y<l)return 0;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    sz[u]=1;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto [v,w,i]:adj[u]){
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
    int mxsz=0,mxv=-1,mxw,mxi;
    pos[u]=idx++;
    for(auto [v,w,i]:adj[u]){
        if(v==p)continue;
        if(sz[v]>mxsz){
            mxsz=sz[v];
            mxv=v;
            mxw=w;
            mxi=i;
        }
    }
    if(mxv!=-1){
        head[mxv]=head[u];
        hld(mxv,u);
        val[pos[mxv]]=mxw;
        posid[mxi]=pos[mxv];
    }
    for(auto [v,w,i]:adj[u]){
        if(v==p||v==mxv)continue;
        head[v]=v;
        hld(v,u);
        val[pos[v]]=w;
        posid[i]=pos[v];
    }
}

int queryup(int u,int v){
    int ret=0;
    while(head[u]!=head[v]){
        ret=max(ret,seg.query(1,n,1,pos[head[u]],pos[u]));
        u=pa[head[u]][0];
    }
    ret=max(ret,seg.query(1,n,1,pos[v]+1,pos[u]));
    return ret;
}

void runcase(){
    cin >> n;
    for(int i=1;i<=n;i++)adj[i].clear();
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w,i});
        adj[v].push_back({u,w,i});
    }
    idx=1;
    dfs(1,0);
    head[1]=1;
    hld(1,0);
    seg.build(1,n,1);
    while(true){
        string str;
        cin >> str;
        if(str=="DONE")break;
        int x,y;
        cin >> x >> y;
        if(str=="CHANGE"){
            seg.update(1,n,1,posid[x],y);
        }else{
            int l=lca(x,y);
            cout << max(queryup(x,l),queryup(y,l)) << '\n';
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();    
}