#include "updown.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

vector<int> adj[2*N];

int sz[2*N],rt[2*N];
bool vis[2*N];

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
    assert(n<=2000);
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
    for(int i=0;i<n;i++)if(rt[i]==rt[i+n])sz[rt[i]]--;
    for(int i=0;i<n;i++){
        ans[i]=-1;
        for(int j=0;j<n;j++)if(rt[i]==rt[j]||rt[i]==rt[j+n]||rt[i+n]==rt[j]||rt[i+n]==rt[j+n])ans[i]++;
    }
    return ans;
}