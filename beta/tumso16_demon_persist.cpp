#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m;
int a[N],mp[N];
long long ans[N];
vector<int> adj[N];
int ti;
int l[N],r[N];

struct persist{
    struct node{
        long long val;
        node *l,*r;
        node(long long val):val(val),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt[N];
    void build(int l,int r,pnode &t){
        t=new node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int ver){
        build(1,2e5,rt[ver]);
    }
    void update(int l,int r,pnode &t,pnode &k,int &x,int &v){
        t=new node(*k);
        t->val+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,v);
        else update(m+1,r,t->r,k->r,x,v);
    }
    void update(int x,int v,int pre,int cur){
        update(1,2e5,rt[cur],rt[pre],x,v);
    }
    long long query(int l,int r,pnode &t,int &x,int &y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    long long query(int l,int r,int ver){
        return query(1,2e5,rt[ver],l,r);
    }
}s;

void dfs(int u){
    l[u]=++ti;
    s.update(ti,a[u],ti-1,ti);
    if(mp[a[u]])s.update(mp[a[u]],-a[u],ti,ti);
    mp[a[u]]=ti;
    for(auto v:adj[u])dfs(v);
    r[u]=ti;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build(0);
    dfs(1);
    while(m--){
        int u;
        cin >> u;
        cout << ans[u] << '\n';
    }
}