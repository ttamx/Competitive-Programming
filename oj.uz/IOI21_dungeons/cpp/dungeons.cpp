#include "dungeons.h"
#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int N=400005;
const int K=25;
const int L=8;
const ll inf=1e18;
const int S=1e7;
 
int n;
int s[N],p[N],w[N],l[N];
ll add[N];
 
struct edge{
	int to;
	ll add,lim;
	edge(){}
	edge(int to,ll add,ll lim):to(to),add(add),lim(lim){}
}dp[L][N][K];

void init(int _n,vector<int> _s,vector<int> _p,vector<int> _w,vector<int> _l){
	n=_n;
	for(int i=0;i<n;i++)s[i]=_s[i],p[i]=_p[i],w[i]=_w[i],l[i]=_l[i];
	s[n]=p[n]=0;
	w[n]=l[n]=n;
	vector<vector<int>> adj(n+1);
	for(int i=0;i<n;i++)adj[w[i]].emplace_back(i);
	queue<int> q;
	q.emplace(n);
	while(!q.empty()){
		auto u=q.front();
		q.pop();
		for(auto v:adj[u]){
			add[v]=add[u]+s[v];
			q.emplace(v);
		}
	}
	for(int i=0;i<L;i++){
		for(int u=0;u<n;u++){
			if(s[u]<=(1<<(3*i))){
				dp[i][u][0]=edge(w[u],s[u],inf);
			}else{
				dp[i][u][0]=edge(l[u],p[u],s[u]);
			}
		}
		dp[i][n][0]=edge(n,0,inf);
		for(int j=1;j<K;j++){
			for(int u=0;u<=n;u++){
				int v=dp[i][u][j-1].to;
				dp[i][u][j].to=dp[i][v][j-1].to;
				dp[i][u][j].add=dp[i][u][j-1].add+dp[i][v][j-1].add;
				dp[i][u][j].lim=min(dp[i][u][j-1].lim,dp[i][v][j-1].lim-dp[i][u][j-1].add);
			}
		}
	}
}
 
ll simulate(int x, int z){
	int phase=0;
	ll sz=1;
	int cur=x;
	ll val=z;
	while(cur!=n&&val<S){
		while(sz*8<=val){
			sz*=8;
			phase++;
		}
		for(int i=K-1;i>=0;i--){
			auto e=dp[phase][cur][i];
			if(val>=e.lim)continue;
			val+=e.add;
			cur=e.to;
		}
		if(val>=s[cur]){
			val+=s[cur];
			cur=w[cur];
		}else{
			val+=p[cur];
			cur=l[cur];
		}
	}
	return val+add[cur];
}