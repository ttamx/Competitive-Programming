#include "joitour.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const bool DBG=false;

int n;
int a[N];
vector<int> adj[N],adj2[N];
int sz[N];
bool used[N];
int par[N],lv[N];
ll dp[N][3],dp2[N][3],sum[N][3],sum2[N][3];
ll ans;

int get_sz(int u,int p=0){
	sz[u]=1;
	for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
	return sz[u];
}

int centroid(int u,int cnt,int p=0){
	for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
	return u;
}

int decom(int u){
	u=centroid(u,get_sz(u));
	used[u]=true;
	int cnt=0;
	for(auto v:adj[u])if(!used[v]){
		par[v]=u;
		lv[v]=lv[u]+1;
		int c=decom(v);
		adj2[u].emplace_back(c);
	}
	return u;
}

void dfs(int u,int p=0){
	if(a[u]!=1)dp[u][a[u]]++;
	for(auto v:adj[u])if(v!=p){
		dfs(v,u);
		sum[u][0]+=dp[v][0];
		sum[u][2]+=dp[v][2];
		sum2[u][0]+=dp2[v][0];
		sum2[u][2]+=dp2[v][2];
	}
	dp[u][0]+=sum[u][0];
	dp[u][2]+=sum[u][2];
	dp2[u][0]+=sum2[u][0];
	dp2[u][2]+=sum2[u][2];
	if(a[u]==1){
		dp2[u][0]+=sum[u][0];
		dp2[u][2]+=sum[u][2];
	}
	if(DBG){
		cerr << "--- " << u << " ---\n";
		cerr << dp[u][0] << " " << dp[u][2] << "\n";
		cerr << dp2[u][0] << " " << dp2[u][2] << "\n";
		cerr << sum[u][0] << " " << sum[u][2] << "\n";
		cerr << sum2[u][0] << " " << sum2[u][2] << "\n";
		cerr << "\n";
	}
	for(auto v:adj[u])if(v!=p){
		if(a[u]==1){
			ans+=dp[v][0]*(sum[u][2]-dp[v][2]);
			ans+=dp[v][2]*(sum[u][0]-dp[v][0]);
		}else{
			ans+=dp2[v][a[u]^2]*2;
		}
		ans+=dp[v][0]*(sum2[u][2]-dp2[v][2]);
		ans+=dp[v][2]*(sum2[u][0]-dp2[v][0]);
		ans+=dp2[v][0]*(sum[u][2]-dp[v][2]);
		ans+=dp2[v][2]*(sum[u][0]-dp[v][0]);
	}
}

void init(int N,vector<int> F,vector<int> U,vector<int> V,int Q){
	n=N;
	for(int i=1;i<=n;i++)a[i]=F[i-1];
	for(int i=0;i<n-1;i++){
		int u=U[i]+1,v=V[i]+1;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	dfs(1);
}

void change(int X,int Y){
	
}

long long num_tours(){
	assert(ans%2==0);
	return ans/2;
}
