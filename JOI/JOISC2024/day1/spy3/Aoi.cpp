#include "Aoi.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

namespace {

int variable_example = 0;

int function_example(int a,int b) { return a + b; }

}  // namespace

string aoi(int n,int m,int q,int k,vector<int> A,vector<int> B,vector<long long> C,vector<int> T,vector<int> X) {
	const ll INF=1e18;
	vector<int> seq;
	string s="";
	vector<vector<tuple<int,ll,int>>> adj(n);
	for(int i=0;i<m;i++){
		int u=A[i],v=B[i];
		ll w=C[i];
		adj[u].emplace_back(v,w,i);
		adj[v].emplace_back(u,w,i);
	}
	using P = pair<ll,int>;
	priority_queue<P,vector<P>,greater<P>> pq;
	vector<pair<int,int>> pre(n);
	vector<ll> dist(n,INF);
	pq.emplace(0,0);
	pre[0]={-1,-1};
	dist[0]=0;
	while(!pq.empty()){
		auto [d,u]=pq.top();
		pq.pop();
		if(d>dist[u])continue;
		for(auto [v,w,i]:adj[u])if(d+w<dist[v]){
			dist[v]=d+w;
			pre[v]={u,i};
			pq.emplace(d+w,v);
		}
	}
	vector<int> inv(m,-1);
	for(int i=0;i<k;i++)inv[X[i]]=i;
	vector<vector<int>> adj2(n);
	for(int i=1;i<n;i++){
		adj2[pre[i].first].emplace_back(i);
	}
	vector<int> par(k,-1);
	function<void(int,int)> dfs=[&](int u,int p){
		if(u>0&&inv[pre[u].second]!=-1){
			int x=inv[pre[u].second];
			if(p!=-1)adj3[p].emplace_back(x);
			par[x]=p;
			p=x;
		}
		for(auto v:adj2[u])dfs(v,p);
	};
	dfs(0,-1);
	for(int i=0;i<k;i++)seq.emplace_back(par[i]+1);
	vector<vector<int>> adj3(k);
	vector<int> leaf;
	for(int i=0;i<q;i++){
		int res=-1;
		for(int u=T[i];u>0;u=pre[u].first){
			int x=inv[pre[u].second];
			if(x!=-1){
				res=x;
				break;
			}
		}
		seq.emplace_back(res+1);
	}
	reverse(seq.begin(),seq.end());
	while(!seq.empty()){
		ll res=0,base=1;
		for(int i=0;i<4;i++)if(!seq.empty()){
			res+=base*seq.back();
			base*=301;
			seq.pop_back();
		}
		for(int i=0;i<33;i++)s.push_back("01"[res>>i&1]);
	}
	return s;
}