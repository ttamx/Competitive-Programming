#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,m;
vector<int> adj[N];
int a[N];
bool b[N];
int tin[N],tout[N];
vector<pair<int,int>> ch[N];
int timer;
int l1[N],r1[N],l2[N],r2[N];
vector<tuple<int,int,int>> event[N];
int ans[N];

struct Segtree{
    int t[K];
    void build(int l,int r,int i){
        t[i]=0;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int v){
        t[i]=max(t[i],v);
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x,v);
        else update(m+1,r,i*2+1,x,v);
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
}segmn;

struct LazySegtree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(0,m,1,x,y-1,v);
    }
    int query(int l,int r,int i){
        if(l==r)return l;
        int m=(l+r)/2;
        push(i);
        if(t[i*2+1]==0)return query(m+1,r,i*2+1);
        else return query(l,m,i*2);
    }
    int query(){
        return query(0,m,1);
    }
}seg;

void dfs(int u,int p){
    tin[u]=++timer;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        ch[u].emplace_back(tout[v],tin[v]);
    }
    tout[u]=timer;
}

int getsub(int u,int v){
    if(u==v)return -1;
    int t=tin[v];
    if(t<tin[u]||tout[u]<t)return -2;
    return lower_bound(ch[u].begin(),ch[u].end(),make_pair(t,0))-ch[u].begin();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> m;
    for(int i=1;i<=m;i++){
        char c;
        cin >> c >> a[i];
        b[i]=c=='s';
    }
    dfs(1,0);
    for(int tt=0;tt<2;tt++){
        int *c1=(tt?r1:l1);
        int *c2=(tt?r2:l2);
        int last=0;
        for(int i=1;i<=m;i++){
            if(b[i])last=i;
            else c1[i]=last;
        }
        segmn.build();
        for(int i=1;i<=m;i++){
            int u=a[i];
            if(b[i]){
                segmn.update(tin[u],i);
            }else if(c1[i]){
                int v=a[c1[i]];
                int t=tin[v];
                if(u==v){
                    c2[i]=c1[i];
                }else if(tin[u]<=t&&t<=tout[u]){
                    auto it=lower_bound(ch[u].begin(),ch[u].end(),make_pair(t,0));
                    assert(it!=ch[u].end());
                    auto [r,l]=*it;
                    c2[i]=max(segmn.query(1,l-1),segmn.query(r+1,n));
                }else{
                    c2[i]=segmn.query(tin[u],tout[u]);
                }
            }else{
                c2[i]=0;
            }
        }
        reverse(a+1,a+m+1);
        reverse(b+1,b+m+1);
    }
    reverse(r1+1,r1+m+1);
    reverse(r2+1,r2+m+1);
    for(int i=1;i<=m;i++){
        r1[i]=m-r1[i]+1;
        r2[i]=m-r2[i]+1;
    }
    for(int i=1;i<=m;i++){
        if(b[i])continue;
        int u=a[i];
        int p;
        event[i].emplace_back(i,p=r2[i],+1);
        if(a[l1[i]]==u){
            event[l1[i]].emplace_back(i,p,-1);
        }else{
            if(getsub(u,a[l1[i]])!=getsub(u,a[r1[i]])){
                event[l1[i]].emplace_back(i,p,-1);
                event[l1[i]].emplace_back(i,p=r1[i],+1);
            }
            event[l2[i]].emplace_back(i,p,-1);
        }
    }
    for(int i=m;i>=1;i--){
        for(auto [l,r,v]:event[i]){
            seg.update(l,r,v);
        }
        ans[i]=seg.query();
    }
    for(int i=1;i<=m;i++){
        cout << ans[i]-i+1 << "\n";
    }
}