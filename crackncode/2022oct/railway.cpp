#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
long long p[N],ppl[N],sum[N],mx[N],mx2[N],mxr[N],sum2[N],ans=1e18,all;
vector<pair<int,long long>> adj[N];

void dfs(int u,int pa){
	ppl[u]=p[u];
	for(auto [v,w]:adj[u]){
		if(v==pa)continue;
		dfs(v,u);
		long long tmp=mx[v]+(w*ppl[v]);
		if(tmp>mx[u]){
			mx2[u]=mx[u];
			mx[u]=tmp;
		}else if(tmp>mx2[u]){
			mx2[u]=tmp;
		}
		sum[u]+=sum[v]+(w*ppl[v]);
		ppl[u]+=ppl[v];
	}
}

void dfs2(int u,int pa){
	for(auto [v,w]:adj[u]){
		if(v==pa)continue;
		sum2[v]=sum2[u]+(sum[u]-sum[v])-(w*ppl[v])+(w*(all-ppl[v]));
		if(mx[u]==mx[v]+(w*ppl[v]))mxr[v]=max(mxr[u],mx2[u])+((all-ppl[v])*w);
		else mxr[v]=max(mxr[u],mx[u])+((all-ppl[v])*w);
		dfs2(v,u);
	}
	long long tmp=mxr[u];
	if(tmp>mx[u]){
		mx2[u]=mx[u];
		mx[u]=tmp;
	}else if(tmp>mx2[u]){
		mx2[u]=tmp;
	}
	ans=min(ans,sum2[u]+sum[u]-mx[u]-mx2[u]);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> p[i];
		all+=p[i];
	}
	for(int i=1;i<n;++i){
		int u,v;
		long long d;
		cin >> u >> v >> d;
		adj[u].emplace_back(v,d);
		adj[v].emplace_back(u,d);
	}
	dfs(1,0);
	dfs2(1,0);
	cout << ans;
	return 0;
}
