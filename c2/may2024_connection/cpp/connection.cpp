#include "connection.h"
#include <bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,m;
int h[N];
vector<int> adj[N];
int disc[N],low[N];
stack<int> s;
int timer;
bool bad[N];

void dfs(int u,int p=-1){
    disc[u]=low[u]=++timer;
    s.emplace(u);
    for(auto v:adj[u])if(v!=p){
        if(!disc[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=disc[u]){
                vector<int> comp{u};
                while(comp.back()!=v){
                    comp.emplace_back(s.top());
                    s.pop();
                }
                int mx=u;
                for(auto i:comp)if(h[i]>h[mx])mx=i;
                bad[mx]=true;
            }
        }else{
            low[u]=min(low[u],disc[v]);
        }
    }
}

int recommended_stations(int _n,int _m,vector<int> H,vector<int> A,vector<int> B){
    n=_n,m=_m;
    for(int i=0;i<n;i++)h[i]=H[i];
    for(int i=0;i<m;i++){
        adj[A[i]].emplace_back(B[i]);
        adj[B[i]].emplace_back(A[i]);
    }
    dfs(0);
    return n-accumulate(bad,bad+n,0);
}