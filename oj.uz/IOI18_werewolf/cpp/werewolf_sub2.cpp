#include "werewolf.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=3005;

int n,m,q;
vector<int> adj[N];
int vis[N],vis2[N];

void dfs(int u,int l){
    if(vis[u])return;
    vis[u]=true;
    for(auto v:adj[u]){
        if(v<l)continue;
        dfs(v,l);
    }
}

bool dfs2(int u,int r){
    if(vis2[u])return false;
    vis2[u]=true;
    if(vis[u])return true;
    for(auto v:adj[u]){
        if(r<v)continue;
        if(dfs2(v,r))return true;
    }
    return false;
}

vector<int> check_validity(int _n,vector<int> X,vector<int> Y,vector<int> S,vector<int> E,vector<int> L,vector<int> R) {
	n=_n;
	m=X.size();
	q=S.size();
	for(int i=0;i<m;i++){
		int u=X[i],v=Y[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
    vector<int> ans(q);
	for(int i=0;i<q;i++){
		int s=S[i],e=E[i],l=L[i],r=R[i];
        for(int i=0;i<n;i++)vis[i]=vis2[i]=false;
        dfs(s,l);
        ans[i]=dfs2(e,r);
	}
	return ans;
}