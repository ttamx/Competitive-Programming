#pragma once
#include "Header.hpp"

/*
    Dinic's Algorithm
    Description: Fast max-flow algorithm.
    Time: $O(VE\log U)$ where $U = \max |\text{cap}|$
*/

struct Dinic{
    struct Edge{
        int to;
        ll flow,cap;
        Edge(int _to,ll _cap):to(_to),flow(0),cap(_cap){}
        ll rcap(){
            return cap-flow;
        }
    };
    int n;
    ll U;
    vector<Edge> e;
    vector<vi> adj;
    vi ptr,lvl;
    Dinic(int n=0){
        init(n);
    }
    void init(int _n){
        n=_n,U=0;
        e.clear();
        adj.assign(n,{});
    }
    void addEdge(int u,int v,ll cap){
        U=max(U,cap);
        adj[u].emplace_back(sz(e));
        e.emplace_back(v,cap);
        adj[v].emplace_back(sz(e));
        e.emplace_back(u,0);
    }
    ll dfs(int u,int t,ll f){
        if(u==t||!f)return f;
        for(int &i=ptr[u];i<sz(adj[u]);i++){
            int j=adj[u][i];
            if(lvl[e[j].to]==lvl[u]+1){
                if(ll p=dfs(e[j].to,t,min(f,e[j].rcap()))){
                    e[j].flow+=p;
                    e[j^1].flow-=p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll flow(int s,int t){
        ll flow=0;
        for(ll L=1ll<<(63-__builtin_clzll(U));L>0;L>>=1)do{
            lvl=ptr=vi(n);
            vi q{s};
            lvl[s]=1;
            for(int i=0;i<sz(q);i++){
                int u=q[i];
                for(auto j:adj[u])if(!lvl[e[j].to]&&e[j].rcap()>=L){
                    q.emplace_back(e[j].to);
                    lvl[e[j].to]=lvl[u]+1;
                }
            }
            while(ll p=dfs(s,t,LINF))flow+=p;
        }while(lvl[t]);
        return flow;
    }
};

