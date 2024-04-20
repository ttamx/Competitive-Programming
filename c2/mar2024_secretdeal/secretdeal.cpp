#include "secretdeal.h"
#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=1e5+5;
const int K=35;
const int INF=INT_MAX/2;
const double EPS=1e-6;

int n,m,k,l;
int w[N];
vector<int> adj[N];
int dp[K][N];
bool vis[K][N];

int solve(){
	for(int mask=0;mask<1<<l;mask++)for(int i=0;i<n;i++){
		dp[mask][i]=INF;
		vis[mask][i]=false;
	}
	for(int i=0,id=0;i<n;i++)if(!w[i])dp[1<<(rng()%l)][i]=0;
	for(int mask=0;mask<1<<l;mask++){
		for(int mask2=mask;mask2;mask2=(mask2-1)&mask){
			for(int i=0;i<n;i++){
				dp[mask][i]=min(dp[mask][i],dp[mask2][i]+dp[mask^mask2][i]-w[i]);
			}
		}
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
		for(int i=0;i<n;i++)if(dp[mask][i]<INF)pq.emplace(dp[mask][i],i);
		while(!pq.empty()){
			auto [d,u]=pq.top();
			pq.pop();
			if(vis[mask][u])continue;
			vis[mask][u]=true;
			for(auto v:adj[u])if(d+w[v]<dp[mask][v]){
				dp[mask][v]=d+w[v];
				pq.emplace(d+w[v],v);
			}
		}
	}
	return *min_element(dp[(1<<l)-1],dp[(1<<l)-1]+n);
}

int make_deal(int N, int M, int K, int L, vector<int> A, vector<int> B, vector<int> W) {
	n=N,m=M,k=K,l=L;
	for(int i=0;i<n;i++)w[i]=W[i];
	for(int i=0;i<m;i++){
		int u=A[i],v=B[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	int res=INF;
	double p=1;
	for(int i=1;i<l;i++)p*=1.0*i/l;
	p=1-p;
	for(double q=1;q>EPS;q*=p)res=min(res,solve());
	return res;
}