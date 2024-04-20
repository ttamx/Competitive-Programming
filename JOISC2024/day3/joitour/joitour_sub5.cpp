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

void dbg(int u){
	if(DBG){
		cerr << "--- " << u << " ---\n";
		cerr << dp[u][0] << " " << dp[u][2] << "\n";
		cerr << dp2[u][0] << " " << dp2[u][2] << "\n";
		cerr << sum[u][0] << " " << sum[u][2] << "\n";
		cerr << sum2[u][0] << " " << sum2[u][2] << "\n";
		cerr << "\n";
	}
}

void dfs(int u,int p=0){
	par[u]=p;
	for(auto v:adj[u])if(v!=p){
		adj2[u].emplace_back(v);
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
	if(a[u]!=1)dp[u][a[u]]++;
	else{
		dp2[u][0]+=sum[u][0];
		dp2[u][2]+=sum[u][2];
	}
	dbg(u);
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
	ans/=2;
}

void change(int X,int Y){
	X++;
	if(DBG)cerr << "CHANGE " << X << " FROM " << a[X] << " TO " << Y << "\n";
	dbg(X);
	ll tmp=0;
	for(auto v:adj2[X]){
		dbg(v);
		if(a[X]==1){
			tmp+=dp[v][0]*(sum[X][2]-dp[v][2]);
			tmp+=dp[v][2]*(sum[X][0]-dp[v][0]);
		}else{
			ans-=dp2[v][a[X]^2];
		}
	}
	if(DBG)cerr << "SUB : " << tmp << "\n";
	assert(tmp%2==0);
	ans-=tmp/2;
	vector<pair<int,int>> ord;
	for(int u=par[X],v=X;u;v=u,u=par[u]){
		ord.emplace_back(u,v);
		if(a[u]==1){
			ans-=dp[v][0]*(sum[u][2]-dp[v][2]);
			ans-=dp[v][2]*(sum[u][0]-dp[v][0]);
		}else{
			ans-=dp2[v][a[u]^2];
		}
		ans-=dp[v][0]*(sum2[u][2]-dp2[v][2]);
		ans-=dp[v][2]*(sum2[u][0]-dp2[v][0]);
		ans-=dp2[v][0]*(sum[u][2]-dp[v][2]);
		ans-=dp2[v][2]*(sum[u][0]-dp[v][0]);
	}
	reverse(ord.begin(),ord.end());
	for(auto [u,v]:ord){
		dp[u][0]-=sum[u][0];
		dp[u][2]-=sum[u][2];
		dp2[u][0]-=sum2[u][0];
		dp2[u][2]-=sum2[u][2];
		if(a[u]==1){
			dp2[u][0]-=sum[u][0];
			dp2[u][2]-=sum[u][2];
		}
		sum[u][0]-=dp[v][0];
		sum[u][2]-=dp[v][2];
		sum2[u][0]-=dp2[v][0];
		sum2[u][2]-=dp2[v][2];
	}
	if(a[X]!=1)dp[X][a[X]]--;
	else{
		dp2[X][0]-=sum[X][0];
		dp2[X][2]-=sum[X][2];
	}
	a[X]=Y;
	if(a[X]!=1)dp[X][a[X]]++;
	else{
		dp2[X][0]+=sum[X][0];
		dp2[X][2]+=sum[X][2];
	}
	reverse(ord.begin(),ord.end());
	for(auto [u,v]:ord){
		sum[u][0]+=dp[v][0];
		sum[u][2]+=dp[v][2];
		sum2[u][0]+=dp2[v][0];
		sum2[u][2]+=dp2[v][2];
		dp[u][0]+=sum[u][0];
		dp[u][2]+=sum[u][2];
		dp2[u][0]+=sum2[u][0];
		dp2[u][2]+=sum2[u][2];
		if(a[u]==1){
			dp2[u][0]+=sum[u][0];
			dp2[u][2]+=sum[u][2];
		}
	}
	reverse(ord.begin(),ord.end());
	for(auto [u,v]:ord){
		if(a[u]==1){
			ans+=dp[v][0]*(sum[u][2]-dp[v][2]);
			ans+=dp[v][2]*(sum[u][0]-dp[v][0]);
		}else{
			ans+=dp2[v][a[u]^2];
		}
		ans+=dp[v][0]*(sum2[u][2]-dp2[v][2]);
		ans+=dp[v][2]*(sum2[u][0]-dp2[v][0]);
		ans+=dp2[v][0]*(sum[u][2]-dp[v][2]);
		ans+=dp2[v][2]*(sum[u][0]-dp[v][0]);
	}
	dbg(X);
	tmp=0;
	for(auto v:adj2[X]){
		dbg(v);
		if(a[X]==1){
			tmp+=dp[v][0]*(sum[X][2]-dp[v][2]);
			tmp+=dp[v][2]*(sum[X][0]-dp[v][0]);
		}else{
			ans+=dp2[v][a[X]^2];
		}
	}
	if(DBG)cerr << "ADD : " << tmp << "\n";
	assert(tmp%2==0);
	ans+=tmp/2;
}

long long num_tours(){
	if(DBG)cerr << "RETURN " << ans << "\n";
	return ans;
}
