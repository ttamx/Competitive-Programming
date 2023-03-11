#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod=1;

struct Z{
    ll x;
    Z():x(0){}
    Z(ll x):x(x%mod){}
    Z& operator+=(Z o){x=(x+o.x)%mod;return *this;}
    Z& operator-=(Z o){x=(x+mod-o.x)%mod;return *this;}
    Z& operator*=(Z o){x=(x*o.x)%mod;return *this;}
    friend Z operator+(Z a,Z b){return a+=b;}
    friend Z operator-(Z a,Z b){return a-=b;}
    friend Z operator*(Z a,Z b){return a*=b;}
};

const int K=1<<18;

struct segtree{
    Z t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=1);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]*t[i*2+1];
    }
    void update(int l,int r,int i,int x,Z v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]*t[i*2+1];
    }
}s;

const int N=1e5+5;

int n;
int pa[N],mp[N];
Z dp[N],dp2[N];
vector<int> adj[N];

void dfs(int u,int p){
    pa[u]=p;
    dp[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[u]*=(dp[v]+1);
    }
}

void dfs2(int u,int p){
    int idx=0;
    for(auto v:adj[u])if(v!=p)mp[v]=++idx;
    if(idx==0)return;
    s.build(1,idx,1);
    vector<Z> vc;
    for(auto v:adj[u])if(v!=p)s.update(1,idx,1,mp[v],(dp[v]+1));
    for(auto v:adj[u]){
        if(v==p)continue;
        s.update(1,idx,1,mp[v],1);
        vc.push_back(s.t[1]);
        s.update(1,idx,1,mp[v],(dp[v]+1));
    }
    int cnt=0;
    for(auto v:adj[u]){
        if(v==p)continue;
        dp2[v]=dp2[u]*vc[cnt++]+1;
        dfs2(v,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> mod;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    dp2[1]=1;
    dfs2(1,0);
    for(int u=1;u<=n;u++)cout << (dp[u]*dp2[u]).x << '\n';
}