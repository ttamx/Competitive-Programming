#include "joitour.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int LG=20;
const bool DBG=1;

int n;
int a[N];
vector<int> adj[N];
int sz[N];
bool used[N];
int par[N],lv[N],cpar[N];
ll cnt[N][3],cnt2[N][3];
ll ans;
int tin[N],tout[N],hv[N],hd[N];
int timer;

struct Fenwick{
	ll t[N];
	void update(int i,int v){
		for(;i<N;i+=i&-i)t[i]+=v;
	}
	ll query(int i){
		ll res=0;
		for(;i>0;i-=i&-i)res+=t[i];
		return res;
	}
	ll query(int l,int r){
		return query(r)-query(l-1);
	}
}f[3];

void pre_dfs(int u,int p=0){
	par[u]=p;
	lv[u]=lv[p]+1;
	sz[u]=1;
	for(auto v:adj[u])if(v!=p){
		pre_dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[hv[u]])hv[u]=v;
	}
}

void hld(int u,int p=0){
	tin[u]=++timer;
	if(!hd[u])hd[u]=u;
	if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
	for(auto v:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
	tout[u]=timer;
}

int get_sz(int u,int p=0){
	sz[u]=1;
	for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
	return sz[u];
}

int centroid(int u,int cnt,int p=0){
	for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
	return u;
}

void fill_cnt(int u,int rt,int c=0,int p=0){
	if(a[u]!=1){
		cnt[rt][a[u]]++;
		cnt2[rt][a[u]]+=c;
	}else c++;
	for(auto v:adj[u])if(v!=p&&!used[v])fill_cnt(v,rt,c,u);
}

int decom(int u){
	u=centroid(u,get_sz(u));
	used[u]=true;
	fill_cnt(u,u);
	if(DBG){
		cerr << "--- " << u << " ---\n";
		cerr << cnt[u][0] << " " << cnt[u][2] << "\n";
		cerr << cnt2[u][0] << " " << cnt2[u][2] << "\n";
		cerr << "\n";
	}
	for(auto v:adj[u])if(!used[v])cpar[decom(v)]=u;
	return u;
}

ll query(int u,int v){
	ll res=0;
	if(a[v]==1)res--;
	while(hd[u]!=hd[v]){
		if(lv[hd[u]]<lv[hd[v]])swap(u,v);
		res+=f[1].query(tin[hd[u]],tin[u]);
		u=par[hd[u]];
	}
	if(lv[u]<lv[v])swap(u,v);
	res+=f[1].query(tin[v],tin[u]);
	return res;
}

void init(int N,vector<int> F,vector<int> U,vector<int> V,int Q){
	n=N;
	for(int i=1;i<=n;i++)a[i]=F[i-1];
	for(int i=0;i<n-1;i++){
		int u=U[i]+1,v=V[i]+1;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	pre_dfs(1);
	hld(1);
	decom(1);
	for(int i=1;i<=n;i++)f[a[i]].update(tin[i],1);
	for(int i=1;i<=n;i++)if(a[i]==1){
		if(DBG)cerr << f[0].query(tin[i]+1,tout[i]) << " " << (f[2].query(n)-f[2].query(tin[i],tout[i])) << "\n";
		if(DBG)cerr << f[2].query(tin[i]+1,tout[i]) << " " << (f[0].query(n)-f[0].query(tin[i],tout[i])) << "\n";
		ans+=f[0].query(tin[i]+1,tout[i])*(f[2].query(n)-f[2].query(tin[i],tout[i]));
		ans+=f[2].query(tin[i]+1,tout[i])*(f[0].query(n)-f[0].query(tin[i],tout[i]));
		for(auto j:adj[i])if(j!=par[i]){
			ans-=f[0].query(tin[j],tout[j])*f[2].query(tin[j],tout[j]);
		}
	}
	if(DBG)cerr << ans << "\n";
	for(int i=1;i<=n;i++)if(a[i]==0){
		for(int u=i,v=0;u;v=u,u=cpar[u]){
			if(DBG)cerr << i << " -> " << u << " (" << v << ") : " << query(i,u) << "\n";
			ans+=query(i,u)*(cnt[u][2]-cnt[v][2]);
			ans+=cnt2[u][2]-cnt2[v][2];
		}
	}
	if(DBG)cerr << ans << "\n";
	for(int i=1;i<=n;i++)if(a[i]==2){
		for(int u=i,v=0;u;v=u,u=cpar[u]){
			if(DBG)cerr << i << " -> " << u << " (" << v << ") : " << query(i,u) << "\n";
			ans+=query(i,u)*(cnt[u][0]-cnt[v][0]);
			ans+=cnt2[u][0]-cnt2[v][0];
		}
	}
	if(DBG)cerr << ans << "\n";
	assert(ans%3==0);
	ans/=3;
}

void change(int X,int Y){
	X++;
	if(DBG)cerr << "CHANGE " << X << " FROM " << a[X] << " TO " << Y << "\n";
	if(a[X]==1){
		if(DBG)cerr << f[0].query(tin[X]+1,tout[X]) << " " << (f[2].query(n)-f[2].query(tin[X],tout[X])) << "\n";
		if(DBG)cerr << f[2].query(tin[X]+1,tout[X]) << " " << (f[0].query(n)-f[0].query(tin[X],tout[X])) << "\n";
		ans-=f[0].query(tin[X]+1,tout[X])*(f[2].query(n)-f[2].query(tin[X],tout[X]));
		ans-=f[2].query(tin[X]+1,tout[X])*(f[0].query(n)-f[0].query(tin[X],tout[X]));
		for(auto j:adj[X])if(j!=par[X]){
			ans-=f[0].query(tin[j],tout[j])*f[2].query(tin[j],tout[j]);
		}
	}else{
		for(int u=X,v=0;u;v=u,u=cpar[u]){
			if(DBG){
				cerr << X << " -> " << u << " (" << v << ") : " << query(X,u) << " x " << (cnt[u][a[X]^2]-cnt[v][a[X]^2]) << "\n";
				cerr << cnt2[u][a[X]^2]-cnt2[v][a[X]^2] << "\n";
			}
			ans-=query(X,u)*(cnt[u][a[X]^2]-cnt[v][a[X]^2]);
			ans-=cnt2[u][a[X]^2]-cnt2[v][a[X]^2];
		}
	}
	f[a[X]].update(tin[X],-1);
	a[X]=Y;
	f[a[X]].update(tin[X],1);
	if(a[X]==1){
		if(DBG)cerr << f[0].query(tin[X]+1,tout[X]) << " " << (f[2].query(n)-f[2].query(tin[X],tout[X])) << "\n";
		if(DBG)cerr << f[2].query(tin[X]+1,tout[X]) << " " << (f[0].query(n)-f[0].query(tin[X],tout[X])) << "\n";
		ans+=f[0].query(tin[X]+1,tout[X])*(f[2].query(n)-f[2].query(tin[X],tout[X]));
		ans+=f[2].query(tin[X]+1,tout[X])*(f[0].query(n)-f[0].query(tin[X],tout[X]));
		for(auto j:adj[X])if(j!=par[X]){
			ans-=f[0].query(tin[j],tout[j])*f[2].query(tin[j],tout[j]);
		}
	}else{
		for(int u=X,v=0;u;v=u,u=cpar[u]){
			if(DBG)cerr << X << " -> " << u << " (" << v << ") : " << query(X,u) << "\n";
			ans+=query(X,u)*(cnt[u][a[X]^2]-cnt[v][a[X]^2]);
			ans+=cnt2[u][a[X]^2]-cnt2[v][a[X]^2];
		}
	}
}

long long num_tours(){
	if(DBG)cerr << "RETURN " << ans << "\n";
	return ans;
}
