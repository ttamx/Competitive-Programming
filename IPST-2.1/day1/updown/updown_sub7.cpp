#include "updown.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

vector<int> adj[2*N];

int sz[2*N],rt[2*N];
bool vis[2*N];
map<long long,int> mp;

mt19937 rng(time(0));

void dfs(int u,int r){
    vis[u]=true;
    sz[u]=1;
    rt[u]=r;
    for(auto v:adj[u]){
        if(vis[v])continue;
        dfs(v,r);
        sz[u]+=sz[v];
    }
}

vector<int> updown(int n, int m, vector<int> U, vector<int> V) {
	for(int i=0;i<m;i++){
        int u=U[i],v=V[i];
        if(u>v)swap(u,v);
        u+=n;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
	}
    for(int i=0;i<2*n;i++){
        if(vis[i])continue;
        dfs(i,i);
    }
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        int x=rt[i],y=rt[i+n];
        if(x==y){
            sz[x]--;
        }else{
            if(x>y)swap(x,y);
            mp[1ll*x*n+y]++;
        }
    }
    for(int i=0;i<n;i++){
        int x=rt[i],y=rt[i+n];
        if(x==y){
            ans[i]=sz[x]-1;
        }else{
            if(x>y)swap(x,y);
            ans[i]=sz[rt[i]]+sz[rt[i+n]]-mp[1ll*x*n+y]-1;
        }
    }
    return ans;
}