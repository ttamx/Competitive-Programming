#include<bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937_64 rng(8714638);

const int N=1e5+20;
const int MOD=1e9+7;

int n,m,src,dst;
vector<pair<int,int>> adj[N];
uint32_t hsh[N];

struct Node;
using Ptr = Node*;
struct Node{
    uint32_t val;
    bool lz;
    Ptr l,r;
    Node():val(0),lz(false),l(),r(){}
};

Ptr root[N];
bool vis[N];
int par[N];
ll pw[N];

void apply(int l,int r,Ptr &t,Ptr o,bool f){
    t=new Node(*o);
    if(f){
        t->val^=hsh[r]-hsh[l-1];
        t->lz^=true;
    }
}

void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

ll calc(int l,int r,Ptr t,bool lz){
    lz^=t->lz;
    if(l==r)return lz?pw[l-1]:0LL;
    int m=(l+r)/2;
    return (calc(l,m,t->l,lz)+calc(m+1,r,t->r,lz))%MOD;
}

ll calc(Ptr t){
    return calc(1,N-1,t,false);
}

uint32_t update(int l,int r,Ptr &t,Ptr o,int x,int y){
    if(y<l||r<x)return 0U;
    t=new Node(*o);
    if(x<=l&&r<=y){
        t->lz^=true;
        return hsh[r]^hsh[l-1];
    }
    int m=(l+r)/2;
    uint32_t s=0;
    s^=update(l,m,t->l,o->l,x,y);
    s^=update(m+1,r,t->r,o->r,x,y);
    t->val^=s;
    return s;
}

int find(int l,int r,Ptr &t,int x,bool lz){
    lz^=t->lz;
    uint32_t s=hsh[r]^hsh[l-1];
    uint32_t val=t->val^(lz?s:0U);
    if(r<x||val==s)return -1;
    if(l==r)return l;
    int m=(l+r)/2;
    int k=find(l,m,t->l,x,lz);
    if(k!=-1)return k;
    return find(m+1,r,t->r,x,lz);
}

int compare(int l,int r,Ptr &u,Ptr &v,bool lz_u,bool lz_v){
    lz_u^=u->lz;
    lz_v^=v->lz;
    uint32_t s=hsh[r]^hsh[l-1];
    uint32_t val_u=u->val^(lz_u?s:0U);
    uint32_t val_v=v->val^(lz_v?s:0U);
    if(val_u==val_v)return 0;
    if(l==r)return val_v?-1:1;
    int m=(l+r)/2;
    int k=compare(m+1,r,u->r,v->r,lz_u,lz_v);
    if(k)return k;
    return compare(l,m,u->l,v->l,lz_u,lz_v);
}

int compare(Ptr &u,Ptr &v){
    return compare(1,N-1,u,v,false,false);
}

void add(Ptr &u,Ptr &v,int x){
    int k=find(1,N-1,u,x,false);
    update(1,N-1,v,u,x,k);
}

using P = pair<Ptr,int>;

struct Compare{
    bool operator()(P u,P v){
        return compare(u.first,v.first)==1;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<N;i++){
        hsh[i]=hsh[i-1]^rng();
        pw[i]=pw[i-1]*2%MOD;
    }
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,x;
        cin >> u >> v >> x;
        x++;
        adj[u].emplace_back(v,x);
        adj[v].emplace_back(u,x);
    }
    cin >> src >> dst;
    priority_queue<pair<Ptr,int>,vector<pair<Ptr,int>>,Compare> pq;
    build(1,N-1,root[src]);
    pq.emplace(root[src],src);
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            Ptr p;
            add(root[u],p,w);
            if(!root[v]||compare(p,root[v])==-1){
                pq.emplace(root[v]=p,v);
                par[v]=u;
            }
        }
    }
    if(!root[dst]){
        cout << -1 << "\n";
    }else{
        cout << calc(root[dst]) << "\n";
        vector<int> path;
        for(int u=dst;u;u=par[u])path.emplace_back(u);
        reverse(path.begin(),path.end());
        cout << path.size() << "\n";
        for(auto x:path)cout << x << " ";
        cout << "\n";
    }
}