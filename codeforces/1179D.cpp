#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;
const ll inf=1e18;

int n;
vector<int> adj[N];
int sz[N];
ll dp[N];
ll ans=inf;

bool querymode=false;

struct line{
    ll m,c;
    mutable ll p;
    line(ll p):p(p){}
    line(ll m,ll c):m(m),c(c){}
    bool operator<(const line &o)const{
        return querymode?p<o.p:m>o.m;
    }
};

struct linecontainer:multiset<line>{
    ll div(ll a,ll b){
        return a/b-((a^b)<0&&a%b);
    }
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=inf,false;
        if(x->m==y->m)x->p=x->c<=y->c?inf:-inf;
        else x->p=div(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void add(ll m,ll c){
        auto y=insert(line(m,c)),x=y++;
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll query(ll x){
        if(empty())return inf;
        querymode=true;
        auto l=lower_bound(x);
        querymode=false;
        return l->m*x+l->c;
    }
}cht;

ll calc(ll x){
    return x*(x-1);
}

ll pw2(ll x){
    return x*x;
}

int dfssz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p)sz[u]+=dfssz(v,u);
    return sz[u];
}

ll dfsdp(int u,int p=-1){
    dp[u]=calc(sz[u]);
    for(auto v:adj[u])if(v!=p)dp[u]=min(dp[u],dfsdp(v,u)+calc(sz[u]-sz[v]));
    return dp[u];
}

void dfs(int u,int p=-1){
    for(auto v:adj[u])if(v!=p)dfs(v,u);
    cht.clear();
    for(auto v:adj[u])if(v!=p){
        ans=min(ans,dp[v]+pw2(n)+pw2(sz[v])-2ll*n*sz[v]+sz[v]-n+cht.query(sz[v]));
        cht.add(2*sz[v],dp[v]+pw2(sz[v])-2ll*n*sz[v]+sz[v]);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    if(n==2)cout << 2,exit(0);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int rt=-1;
    for(int i=1;i<=n;i++)if(adj[i].size()>1)rt=i;
    dfssz(rt);
    dfsdp(rt);
    dfs(rt);
    cout << calc(n)-ans/2;
}