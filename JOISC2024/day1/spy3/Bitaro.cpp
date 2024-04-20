#include "Bitaro.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

namespace {

int variable_example = 0;

int function_example(int a,int b) { return a + b; }

}  // namespace

void bitaro(int n,int m,int q,int k,vector<int> A,vector<int> B,vector<long long> C,vector<int> T,vector<int> X,string s) {
	const ll INF=1e18;
	vector<int> seq;
	for(int i=0;i<s.size();i+=33){
		ll res=0;
		for(int j=0;j<33;j++)if(s[i+j]=='1')res|=1LL<<j;
		for(int j=0;j<4;j++){
			seq.emplace_back(res%301);
			res/=301;
		}
	}
	reverse(seq.begin(),seq.end());
	vector<int> par(k);
	int pos=0;
	for(int i=0;i<k;i++){
		par[i]=seq.back()-1;
		seq.pop_back();
	}
	for(int i=0;i<q;i++){
		vector<vector<tuple<int,ll,int>>> adj(n);
		auto NC=C;
		int st=seq.back();
		seq.pop_back();
		for(int u=st-1;u!=-1;u=par[u])NC[X[u]]=0;
		for(int i=0;i<m;i++){
			int u=A[i],v=B[i];
			ll w=NC[i];
			if(w>=0){
				adj[u].emplace_back(v,w,i);
				adj[v].emplace_back(u,w,i);
			}
		}
		using P = pair<ll,int>;
		priority_queue<P,vector<P>,greater<P>> pq;
		vector<pair<int,int>> pre(n,{-1,-1});
		vector<ll> dist(n,INF);
		vector<bool> vis(n);
		pq.emplace(0,0);
		pre[0]={-1,-1};
		dist[0]=0;
		while(!pq.empty()){
			auto [d,u]=pq.top();
			pq.pop();
			if(vis[u])continue;
			vis[u]=true;
			for(auto [v,w,i]:adj[u])if(d+w<dist[v]){
				dist[v]=d+w;
				pre[v]={u,i};
				pq.emplace(d+w,v);
			}
		}
		vector<int> ans;
		for(int u=T[i];u>0;u=pre[u].first)ans.emplace_back(pre[u].second);
		reverse(ans.begin(),ans.end());
		answer(ans);
	}
}
