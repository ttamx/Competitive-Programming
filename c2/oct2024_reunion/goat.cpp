#include "reunion.h"
#include <bits/stdc++.h>

using namespace std;

namespace goat{

const int INF=INT_MAX;

int n;
int st;
vector<vector<pair<int,int>>> adj(n);
vector<int> dist,par;

int dijkstra(int s){
    for(int i=0;i<n;i++){
        dist[i]=INF;
        par[i]=i;
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.emplace(0,s);
    dist[s]=0;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                par[v]=u;
                pq.emplace(d+w,v);
            }
        }
    }
    return *max_element(dist.begin(),dist.end());
}

void goat_init(int _n,int m,vector<int> _u,vector<int> _v,vector<int> _w,int _st){
    n=_n,st=_st;
    adj.resize(n);
    dist.resize(n);
    par.resize(n);
    for(int i=0;i<m;i++){
        int u=_u[i],v=_v[i],w=_w[i];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    pair<int,int> mn(INF,-1);
    for(int i=0;i<n;i++){
        mn=min(mn,make_pair(dijkstra(i),i));
    }
    dijkstra(mn.second);
}

int goat_move(int u){
    return par[u];
}

}