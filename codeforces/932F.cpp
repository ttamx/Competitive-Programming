#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int R=1e5;
const ll inf=1e18;

int n;
ll a[N],b[N];
vector<int> adj[N];
int sz[N];
ll dp[N];

struct lichaotree{
    struct line{
        ll m,c;
        line():m(0),c(inf){}
        line(ll m,ll c):m(m),c(c){}
        ll get(ll x){
            return m*x+c;
        }
    };
    struct node;
    typedef node* pnode;
    struct node{
        line val;
        pnode l,r;
        node():val(),l(nullptr),r(nullptr){}
    };
    pnode rt=nullptr;
    void insert(int l,int r,pnode &t,line val){
        if(!t)t=new node();
        int m=(l+r)/2;
        if(val.get(m)<t->val.get(m))swap(val,t->val);
        if(val.get(l)<t->val.get(l))insert(l,m,t->l,val);
        if(val.get(r)<t->val.get(r))insert(m+1,r,t->r,val);
    }
    void insert(line l){
        insert(-R,R,rt,l);
    }
    void insert(ll m,ll c){
        insert(line(m,c));
    }
    ll query(int l,int r,pnode t,ll x){
        if(!t||x<l||r<x)return inf;
        ll res=t->val.get(x);
        if(l==r)return res;
        int m=(l+r)/2;
        return min({res,query(l,m,t->l,x),query(m+1,r,t->r,x)});
    }
    ll query(ll x){
        return query(-R,R,rt,x);
    }
    void del(pnode t){
        if(!t)return;
        del(t->l);
        del(t->r);
        delete t;
    }
    void del(){
        del(rt);
    }
    void merge(pnode t){
        if(!t)return;
        insert(t->val);
        merge(t->l);
        merge(t->r);
    }
    void merge(lichaotree &o){
        merge(o.rt);
        o.del();
    }
}lct[N];

void dfs(int u,int p=-1){
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        if(sz[u]>sz[v])swap(lct[u],lct[v]);
        lct[u].merge(lct[v]);
        sz[u]+=sz[v];
    }
    if(sz[u])dp[u]=lct[u].query(a[u]);
    lct[u].insert(b[u],dp[u]);
    sz[u]++;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++)cout << dp[i] << " \n"[i==n];
}