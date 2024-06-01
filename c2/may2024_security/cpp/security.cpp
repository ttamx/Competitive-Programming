#include"security.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int N=8e5+5;

int n,m;
int deg[N];
vector<int> adj[N];
priority_queue<P,vector<P>,greater<P>> pq;
vector<int> a;
bool vis[N];

struct ConvexHullTrick{
    struct Line{
        ll m,c;
        Line(ll _m,ll _c):m(_m),c(_c){}
        ll eval(ll x){
            return m*x+c;
        }
    };
    vector<Line> hull;
    bool bad(Line x,Line y,Line z){
        return (x.c-z.c)*(y.m-x.m)<=(x.c-y.c)*(z.m-x.m);
    }
    void insert(ll m,ll c){
        Line l(m,c);
        while(hull.size()>1&&bad(hull.end()[-2],hull.back(),l))hull.pop_back();
        hull.emplace_back(l);
    }
    ll query(ll x){
        int l=0,r=hull.size()-1;
        while(l<r){
            int m=(l+r)/2;
            if(hull[m].eval(x)>=hull[m+1].eval(x))r=m;
            else l=m+1;
        }
        return hull[l].eval(x);
    }
}cht;

void kingdom(int _n,int _m,int Q,vector<int> _u,vector<int> _v,vector<int> s){
    n=_n,m=_m;
    for(int i=0;i<m;i++){
        int u=_u[i],v=_v[i];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    for(int i=0;i<n;i++)if(deg[i]<2){
        vis[i]=true;
        pq.emplace(s[i],i);
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        a.emplace_back(d);
        for(auto v:adj[u])if(--deg[v]<2&&!vis[v]){
            vis[v]=true;
            pq.emplace(s[v],v);
        }
    }
    if(a.size()<n)return;
    for(int i=n-1;i>=0;i--)cht.insert(-i-1,a[i]);
}

ll answer_query(int x){
    if(a.size()<n)return -1LL;
    return max(0LL,cht.query(x));
}