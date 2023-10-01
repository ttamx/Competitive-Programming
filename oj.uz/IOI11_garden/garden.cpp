#include "garden.h"
#include "gardenlib.h"
#include<bits/stdc++.h>

using namespace std;

const int N=150005;
const int M=300005;
const int inf=2e9;

int n,p;
vector<int> padj[N];
vector<pair<int,int>> adj[N][2];
int dp[2][N][2];
int cnt[2][M];
int cyc[2];

void dfs(int t,int u,int s,int d=0){
	dp[t][u][s]=d;
	for(auto [v,w]:adj[u][s]){
		if(v==p&&w==t){
			cyc[t]=d+1;
		}else{
			dfs(t,v,w,d+1);
		}
	}
}

void count_routes(int N, int M, int P, int R[][2], int Q, int G[]){
	n=N,p=P;
	for(int t=0;t<2;t++)for(int i=0;i<n;i++)dp[t][i][0]=dp[t][i][1]=inf;
	for(int i=0;i<M;i++){
		int u=R[i][0],v=R[i][1];
		padj[u].emplace_back(v);
		padj[v].emplace_back(u);
	}
	for(int u=0;u<n;u++){
		for(int s=0;s<2;s++){
			int v=padj[u][min(s,(int)padj[u].size()-1)];
			adj[v][padj[v][0]==u].emplace_back(u,s);
		}
	}
	dfs(0,p,0);
	dfs(1,p,1);
	for(int i=0;i<Q;i++){
		int k=G[i];
		int ans=0;
		for(int u=0;u<n;u++){
			bool ok=false;
			for(int t=0;t<2;t++){
				if(dp[t][u][0]>k)continue;
				int d=k-dp[t][u][0];
				if(cyc[t])d%=cyc[t];
				ok|=d==0;
			}
			ans+=ok;
		}
		answer(ans);
	}
}