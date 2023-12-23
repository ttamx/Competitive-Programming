#include "train.h"
#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int K=20;

int n,m,rt;
vector<int> adj[N];
int pa[N][K],lv[N],sz[N],disc[N];
bool leaf[N];
int cnt[N],cnt2[N];
vector<int> vec[N];
int t;

void predfs(int u,int p=0){
	disc[u]=++t;
	lv[u]=lv[p]+1;
	pa[u][0]=p;
	if(adj[u].size()==1)leaf[u]=true,sz[u]=1;
	for(int i=1;i<K;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
	for(auto v:adj[u])if(v!=p){
		predfs(v,u);
		sz[u]+=sz[v];
	}
}

void dfs(int u,int p=0){
	for(auto v:adj[u])if(v!=p){
		dfs(v,u);
		cnt[u]+=cnt[v];
		cnt2[u]+=cnt2[v];
	}
}

int lca(int u,int v){
	if(lv[u]<lv[v])swap(u,v);
	for(int i=K-1;i>=0;i--)if(lv[pa[u][i]]>=lv[v])u=pa[u][i];
	if(u==v)return u;
	for(int i=K-1;i>=0;i--)if(pa[u][i]!=pa[v][i])u=pa[u][i],v=pa[v][i];
	return pa[u][0];
}

int train(int _n, int _m, vector<int> _u, vector<int> _v,vector<int> A, vector<int> B) {
	n=_n,m=_m;
	if(n==2){
		for(int i=0;i<m;i++)if(A[i]!=B[i])return 1;
		return 0;
	}
	for(int i=0;i<n-1;i++){
		int u=_u[i]+1,v=_v[i]+1;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	for(int i=1;i<=n;i++)if(adj[i].size()>1)rt=i;
	predfs(rt);
	for(int i=0;i<m;i++){
		int a=A[i]+1,b=B[i]+1;
		if(leaf[a])vec[a].emplace_back(b);
		if(leaf[b])vec[b].emplace_back(a);
	}
	for(int i=1;i<=n;i++)if(leaf[i]){
		vec[i].emplace_back(i);
		sort(vec[i].begin(),vec[i].end(),[&](int l,int r){
			return disc[l]<disc[r];
		});
		int top=vec[i][0];
		cnt[top]++,cnt[pa[top][0]]--;
		for(int j=1;j<vec[i].size();j++){
			int cur=vec[i][j],pre=vec[i][j-1];
			int anc=lca(pre,cur);
			if(lv[anc]<lv[top]){
				cnt[cur]++,cnt[pa[top][0]]++,cnt[anc]--,cnt[pa[anc][0]]--;
				top=anc;
			}else{
				cnt[cur]++,cnt[anc]--;
			}
		}
		cnt[i]--,cnt[pa[top][0]]++;
		cnt2[i]++,cnt2[top]--;
	}
	dfs(rt);
	int ans=n;
	for(int i=1;i<=n;i++){
		int sum=0,mx=0;
		vector<int> res={sz[rt]-sz[i]-cnt[i]};
		for(auto v:adj[i])if(v!=pa[i][0])res.emplace_back(sz[v]-cnt2[v]);
		for(auto x:res){
			sum+=x;
			mx=max(mx,x);
		}
		ans=min(ans,max(mx,(sum+1)/2));
	}
	return ans;
}