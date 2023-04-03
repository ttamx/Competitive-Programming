#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int a[N],mp[N];
vector<int> adj[N];
vector<int> vec;
int lv[N],pa[N][20];

struct node{
    int freq;
    node *l,*r;
    node():freq(0),l(nullptr),r(nullptr){}
    node(int freq):freq(freq),l(nullptr),r(nullptr){}
    node(int freq,node *l,node *r):freq(freq),l(l),r(r){}
};
typedef node* nodeptr;

nodeptr rt[N];

void build(int l,int r,nodeptr &t){
    t=new node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,nodeptr &t,nodeptr k,int x,int v){
    t=new node(*k);
    t->freq+=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,k->l,x,v);
    else update(m+1,r,t->r,k->r,x,v);
}

int query(int l,int r,nodeptr tu, nodeptr tv,nodeptr tl,int v,int idx){
    if(l==r)return l;
    int freq=tu->l->freq+tv->l->freq-2*tl->l->freq;
    int m=(l+r)/2;
    if(l<=idx&&idx<=m)freq++;
    if(freq<v)return query(m+1,r,tu->r,tv->r,tl->r,v-freq,idx);
    return query(l,m,tu->l,tv->l,tl->l,v,idx);
}

void dfs(int u,int p=0){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    update(1,n,rt[u],rt[p],mp[u],1);
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    vec.emplace_back(-1e18);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        vec.emplace_back(a[i]);
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    sort(vec.begin(),vec.end());
    for(int i=1;i<=n;i++)mp[i]=lower_bound(vec.begin(),vec.end(),a[i])-vec.begin();
    build(1,n,rt[0]);
    dfs(1);
    while(m--){
        int u,v,k;
        cin >> u >> v >> k;
        int LCA=lca(u,v);
        cout << vec[query(1,n,rt[u],rt[v],rt[LCA],k,mp[LCA])] << '\n';
    }
}