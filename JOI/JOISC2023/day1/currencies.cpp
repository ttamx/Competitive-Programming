#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const bool dbg=false;
const int N=1e5+5;

struct node{
    ll val;
    int freq;
    node *l,*r;
    node():val(0),freq(0),l(nullptr),r(nullptr){}
    node(int val,int freq):val(val),freq(freq),l(nullptr),r(nullptr){}
    node(int val,int freq,node *l,node *r):val(val),freq(freq),l(l),r(r){}
};

typedef node* nodeptr;

void build(int l,int r,nodeptr &t){
    t=new node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,nodeptr &t,nodeptr k,int x,ll val){
    t=new node(*k);
    t->val+=val;
    t->freq++;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,k->l,x,val);
    else update(m+1,r,t->r,k->r,x,val);
}

int query(int l,int r,vector<pair<nodeptr,nodeptr>> t,ll val){
    if(l==r){
        int res=0;
        for(auto [tl,tr]:t)if(tr->val-tl->val<=val)res+=tr->freq-tl->freq;
        return res;
    }
    int m=(l+r)/2;
    ll sum=0;
    for(auto [tl,tr]:t)sum+=tr->l->val-tl->l->val;
    int freq=0;
    for(auto [tl,tr]:t)freq+=tr->l->freq-tl->l->freq;
    if(sum<=val){
        for(auto &[tl,tr]:t)tl=tl->r,tr=tr->r;
        return freq+query(m+1,r,t,val-sum);
    }
    for(auto &[tl,tr]:t)tl=tl->l,tr=tr->l;
    return query(l,m,t,val);
}

int n,m,q;
int cost[N];
pair<int,int> edge[N];
nodeptr rt[N];
int mp[N];
vector<pair<int,int>> v;
vector<int> vec[N];
vector<int> adj[N];
int sz[N],heavy[N],chain[N],head[N],pos[N],nodeat[N];
int chainid=1,posid;
int pa[N][20],lv[N];
int belong[N];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[heavy[u]])heavy[u]=v;
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
    pos[u]=++posid;
    nodeat[posid]=u;
    chain[u]=chainid;
    if(heavy[u])hld(heavy[u],u);
    for(auto v:adj[u]){
        if(v==p||v==heavy[u])continue;
        head[++chainid]=v;
        hld(v,u);
    }
}

vector<pair<int,int>> queryup(int st,int ed){
    vector<pair<int,int>> res;
    int u=st;
    while(chain[u]!=chain[ed]){
        res.emplace_back(pos[head[chain[u]]],pos[u]);
        u=pa[head[chain[u]]][0];
    }
    if(ed!=u)res.emplace_back(pos[ed]+1,pos[u]);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<n;i++){
        auto &[u,v]=edge[i];
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    head[1]=1;
    hld(1,0);
    for(int i=1;i<=n;i++){
        auto [u,v]=edge[i];
        if(lv[u]<lv[v])swap(u,v);
        belong[i]=u;
    }
    for(int i=1;i<=m;i++){
        int x,y;
        cin >> x >> cost[i];
        vec[belong[x]].emplace_back(i);
        v.emplace_back(cost[i],i);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<m;i++)mp[v[i].second]=i+1;
    build(1,m,rt[0]);
    for(int i=1;i<=n;i++){
        rt[i]=rt[i-1];
        for(auto j:vec[nodeat[i]])update(1,m,rt[i],rt[i],mp[j],cost[j]);
    }
    if(dbg){
        for(int i=1;i<=n;i++)cerr << "(" << nodeat[i] << "," << chain[nodeat[i]] << ") ";
        cerr << '\n';
        for(int i=1;i<=chainid;i++)cerr << "(" << i << "," << head[i] << ") ";
    }
    while(q--){
        int u,v,x;
        ll y;
        cin >> u >> v >> x >> y;
        int LCA=lca(u,v);
        vector<pair<nodeptr,nodeptr>> res;
        auto q1=queryup(u,LCA);
        auto q2=queryup(v,LCA);
        for(auto [l,r]:q1)res.emplace_back(rt[l-1],rt[r]);
        for(auto [l,r]:q2)res.emplace_back(rt[l-1],rt[r]);
        int all=0;
        for(auto [tl,tr]:res)all+=tr->freq-tl->freq;
        int cnt=query(1,m,res,y);
        cout << max(-1,x-(all-cnt)) << '\n';
    }
}