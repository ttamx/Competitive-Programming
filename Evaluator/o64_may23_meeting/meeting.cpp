#include <bits/stdc++.h>
#include "meeting.h"

using namespace std;

const int N=1e5+5;
const int LG=17;

int n;
vector<pair<int,int>> adj[N];
int sz[N],par[N],disc[N],pos[N],hd[N],hv[N],dp[N],dep[N];
int timer=-1;

void dfs(int u,int p=-1){
	sz[u]=1;
	par[u]=p;
	hv[u]=-1;
	hd[u]=u;
	for(auto [v,w]:adj[u]){
		if(v!=p){
			dp[v]=dp[u]+w;
			dep[v]=dep[u]+1;
			dfs(v,u);
			sz[u]+=sz[v];
			if(hv[u]==-1||sz[v]>sz[hv[u]]){
				hv[u]=v;
			}
		}
	}
}

void hld(int u,int p=-1){
	disc[u]=++timer;
	pos[timer]=u;
	if(hv[u]!=-1){
		hd[hv[u]]=hd[u];
		hld(hv[u],u);
	}
	for(auto [v,w]:adj[u]){
		if(v!=p&&v!=hv[u]){
			hld(v,u);
		}
	}
}

int lca(int u,int v){
	while(hd[u]!=hd[v]){
		if(dep[hd[u]]<dep[hd[v]]){
			swap(u,v);
		}
		u=par[hd[u]];
	}
	return dep[u]<dep[v]?u:v;
}

int dist(int u,int v){
	return dp[u]+dp[v]-2*dp[lca(u,v)];
}

int dist2(int u,int v){
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}

int jump(int u,int v,int k){
	int w=lca(u,v);
	int d=dep[u]+dep[v]-2*dep[w];
	assert(k<=d);
	if(k>dep[u]-dep[w]){
		k=d-k;
		swap(u,v);
	}
	while(k>=dep[u]-dep[hd[u]]+1){
		k-=dep[u]-dep[hd[u]]+1;
		u=par[hd[u]];
	}
	return pos[disc[u]-k];
}

int centroid(int u,int v,int w){
	vector<int> a;
	a.emplace_back(lca(u,v));
	a.emplace_back(lca(u,w));
	a.emplace_back(lca(v,w));
	return *min_element(a.begin(),a.end(),[&](int i,int j){
		return dep[i]>dep[j];
	});
}

vector<int> best_meeting(int _n,int q,vector<vector<int>>& roads,vector<int>& lengths,vector<int>& a,vector<int>& b,vector<int>& c){
	n=_n;
	for(int i=0;i<n-1;i++){
		int u=roads[i][0],v=roads[i][1],w=lengths[i];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	dfs(0);
	hld(0);
	vector<int> ans;
	for(int i=0;i<q;i++){
		int u=a[i],v=b[i],w=c[i];
		int st=centroid(u,v,w);
		vector<pair<int,int>> d;
		d.emplace_back(dist(st,u),u);
		d.emplace_back(dist(st,v),v);
		d.emplace_back(dist(st,w),w);
		sort(d.rbegin(),d.rend());
		int ed=d[0].second;
		auto calc=[&](int k){
			int x=jump(st,ed,k);
			return max({dist(u,x),dist(v,x),dist(w,x)});
		};
		int l=0,r=dist2(st,ed);
		while(l<r){
			int m=(l+r)/2;
			if(calc(m+1)<calc(m))l=m+1;
			else r=m;
		}
		ans.emplace_back(calc(l));
	}
	return ans;
}
