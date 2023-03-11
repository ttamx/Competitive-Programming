#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<int,int,int> t3;

const int N=5e5+5;
const int K=1<<20;

int n,q,cnt;
int v[N],a[N];
int idx=1;
int w[N];

struct node{
    int l,r,p,sz,hd,pos;
}t[N];

struct segtree{
    int t[K],lz[K],mn[K];
    void pushlz(int l,int r,int i){
        if(lz[i]==0)return;
        t[i]=min(t[i],mn[i]-lz[i]);
        if(l<r){
            lz[i*2]=max(lz[i*2],lz[i]);
            lz[i*2+1]=max(lz[i*2+1],lz[i]);
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r){
            t[i]=2e9;
            mn[i]=w[l];
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=2e9;
        mn[i]=min(mn[i*2],mn[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            lz[i]+=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}s[1];

void dfs(int u){
    t[u].sz=1;
    if(t[u].l){
        dfs(t[u].l);
        t[u].sz+=t[t[u].l].sz;
    }
    if(t[u].r){
        dfs(t[u].r);
        t[u].sz+=t[t[u].r].sz;
    }
}

void hld(int u){
    w[idx]=v[u];
    t[u].pos=idx++;
    if(t[u].l==0&&t[u].r==0)return;
    if(t[t[u].l].sz>t[t[u].r].sz){
        t[t[u].l].hd=t[u].hd;
        hld(t[u].l);
        if(t[u].r){
            t[t[u].r].hd=t[u].r;
            hld(t[u].r);
        }
    }else{
        t[t[u].r].hd=t[u].hd;
        hld(t[u].r);
        if(t[u].l){
            t[t[u].l].hd=t[u].l;
            hld(t[u].l);
        }
    }
}

void updateup(int i,int u,int v,int val){
    while(t[u].hd!=t[v].hd){
        s[i].update(t[t[u].hd].pos,t[u].pos,val);
        u=t[t[u].hd].p;
    }
    s[i].update(t[v].pos,t[u].pos,val);
}

int queryup(int i,int u,int v){
    int res=2e9;
    while(t[u].hd!=t[v].hd){
        res=min(res,s[i].query(t[t[u].hd].pos,t[u].pos));
        u=t[t[u].hd].p;
    }
    res=min(res,s[i].query(t[v].pos,t[u].pos));
    if(res>1e9)res=-1;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> v[i];
    for(int i=1;i<=n;i++)cin >> a[i],a[i]=min(a[i],v[i]/2);
    int root=1,leaf=1;
    for(int i=2;i<=n;i++){
        while(leaf&&v[i]>v[leaf])leaf=t[leaf].p;
        if(leaf==0){
            t[i].l=root;
            t[root].p=i;
            root=i;
        }else{
            t[i].l=t[leaf].r;
            t[t[leaf].r].p=i;
            t[leaf].r=i;
            t[i].p=leaf;
        }
        leaf=i;
    }
    dfs(root);
    t[root].hd=root;
    hld(root);
    s[0].build();
    bool ok=false;
    while(q--){
        int o,x,y;
        cin >> o >> x >> y;
        if(o==1){
            updateup(0,x,root,a[x]);
        }else{
            cout << queryup(0,x,root) << '\n';
        }
    }
}