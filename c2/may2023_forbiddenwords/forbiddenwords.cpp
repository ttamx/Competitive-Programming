#include "forbiddenwords.h"
#include<bits/stdc++.h>

using namespace std;

using pi = pair<int,int>;
using ll = long long;
using ull = unsigned long long;

vector<pi> alice(int M, int N, int K, ll X, vector<pi> F){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	const int S=M;
	vector<ll> dp(S+1,0LL);
	dp[0]=dp[1]=1;
	for(int i=2;i<=S;i++){
		for(int j=0;j<i-j-1;j++){
			dp[i]+=dp[j]*dp[i-j-1];
		}
		if(i&1){
			int j=i/2;
			dp[i]+=dp[j]*(dp[j]+1)/2;
		}
	}
	int V=2;
	while(X>=dp[V])X-=dp[V++];
	vector<pi> edges{{0,1},{0,2},{1,2}};
	int id=2;
	auto search=[&](ll x,ll b){
		ll l=0,r=b-1;
		while(l<r){
			ll m=(l+r+1)/2;
			ll tmp=m*(m+1)/2;
			if(tmp<=x)l=m;
			else r=m-1;
		}
		return l;
	};
	function<void(int,ll)> solve=[&](int n,ll x){
		for(int i=0;i<=n-i-1;i++){
			int j=n-i-1;
			ll l=dp[i],r=dp[j];
			if(i<j){
				ll cnt=l*r;
				if(cnt>x){
					int u=id;
					if(i){
						edges.emplace_back(u,++id);
						solve(i,x/r);
					}
					if(j){
						edges.emplace_back(u,++id);
						solve(j,x%r);
					}
					return;
				}else{
					x-=cnt;
				}
			}else{
				int u=id;
				ll tmp=search(x,l);
				if(i){
					edges.emplace_back(u,++id);
					solve(i,tmp);
				}
				if(j){
					edges.emplace_back(u,++id);
					solve(j,x-(tmp*(tmp+1)/2));
				}
			}
		}
	};
	solve(V,X);
	assert(V==id-1);
	V=id+1;
	vector<int> p(M,0);
	iota(p.begin(),p.end(),0);
	vector<vector<bool>> ban(M,vector<bool>(M,false));
	for(auto [u,v]:F)ban[u][v]=ban[v][u]=true;
	int score=0;
	vector<vector<int>> adj(M,vector<int>());
	for(auto [u,v]:edges){
		u=p[u],v=p[v];
		if(ban[u][v])score++;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	auto rand_double=[&](){
		double res=1;
		for(int i=0;i<3;i++)res*=1.0*(rng()%1024)/1024.0;
		return res;
	};
	while(score>0){
		int idx1=rng()%V;
		int idx2=rng()%M;
		int new_score=score;
		for(auto u:adj[idx1])if(ban[p[idx1]][p[u]])new_score--;
		for(auto u:adj[idx2])if(ban[p[idx2]][p[u]])new_score--;
		swap(p[idx1],p[idx2]);
		for(auto u:adj[idx1])if(ban[p[idx1]][p[u]])new_score++;
		for(auto u:adj[idx2])if(ban[p[idx2]][p[u]])new_score++;
		if(rand_double()<exp(6.0*(score-new_score))){
			score=new_score;
			continue;
		}
		swap(p[idx1],p[idx2]);
	}
	vector<pi> ans(0);
	for(auto [u,v]:edges)ans.emplace_back(p[u],p[v]);
	return ans;
}


ll bob(int M, vector<pi> W){
	const int S=M;
	vector<ll> dp(S+1,0LL);
	dp[0]=dp[1]=1;
	for(int i=2;i<=S;i++){
		for(int j=0;j<i-j-1;j++){
			dp[i]+=dp[j]*dp[i-j-1];
		}
		if(i&1){
			int j=i/2;
			dp[i]+=dp[j]*(dp[j]+1)/2;
		}
	}
	ll X=0;
	for(int i=2;i<W.size()-2;i++)X+=dp[i];
	vector<vector<int>> padj(M,vector<int>()),adj(M,vector<int>());
	vector<vector<bool>> link(M,vector<bool>(M,false));
	for(auto [u,v]:W){
		link[u][v]=link[v][u]=true;
		padj[u].emplace_back(v);
		padj[v].emplace_back(u);
	}
	vector<bool> vis(M,false);
	int rt=-1;
	[&](){
		for(int i=0;i<M;i++)if(padj[i].size()>2){
			for(int j=0;j<M;j++)if(j!=i&&link[i][j]){
				for(int k=0;k<M;k++)if(k!=i&&k!=j&&link[i][k]&&link[j][k]){
					vis[j]=vis[k]=true;
					rt=i;
					return;
				}
			}
		}
	}();
	assert(rt!=-1);
	vector<int> sz(M+1,0);
	vector<ll> v(M+1,0);
	function<void(int)> dfs=[&](int u){
		vis[u]=true;
		sz[u]=1;
		for(auto v:padj[u])if(!vis[v]){
			dfs(v);
			sz[u]+=sz[v];
			adj[u].emplace_back(v);
		}
		sort(adj[u].begin(),adj[u].end(),[&](int l,int r){
			return sz[l]<sz[r];
		});
		if(adj[u].size()==0)return;
		int l=M,r=M;
		if(adj[u].size()==1)r=adj[u][0];
		if(adj[u].size()==2)l=adj[u][0],r=adj[u][1];
		for(int i=0;i<sz[l]&&i<sz[r];i++)v[u]+=dp[i]*dp[sz[u]-i-1];
		if(sz[l]==sz[r]){
			if(v[l]<v[r])swap(l,r);
			v[u]+=v[l]*(v[l]+1)/2+v[r];
		}else{
			v[u]+=v[l]*dp[sz[r]]+v[r];
		}
	};
	dfs(rt);
	X+=v[rt];
	return X;
}