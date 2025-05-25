#include "swap.h"
#include <bits/stdc++.h>

using namespace std;

const int N=200005;
const int LG=18;
const int INF=INT_MAX/2;

int n,m;
int fa[N],par[LG][N],a[N],dep[N],deg[N];
bool ok[N];

int fp(int u){return fa[u]=u==fa[u]?u:fp(fa[u]);}

int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=LG-1;i>=0;i--)if(dep[par[i][u]]>=dep[v])u=par[i][u];
	if(u==v)return u;
	for(int i=LG-1;i>=0;i--)if(par[i][u]!=par[i][v])u=par[i][u],v=par[i][v];
	return par[0][u];
}

void init(int _n,int _m,vector<int> _u,vector<int> _v,vector<int> _w){
	n=_n,m=_m;
	vector<tuple<int,int,int>> e;
	for(int i=0;i<m;i++)e.emplace_back(_w[i],_u[i],_v[i]);
	sort(e.begin(),e.end());
	iota(fa,fa+2*n,0);
	fill(a,a+2*n,INF);
	int cur=n;
	for(auto [w,u,v]:e){
		bool good=(++deg[u]>2||++deg[v]>2);
		u=fp(u),v=fp(v);
		if(u!=v){
			fa[u]=fa[v]=par[0][u]=par[0][v]=cur;
			ok[cur]=good||ok[u]||ok[v];
			if(ok[cur])a[cur]=w;
			cur++;
		}else{
			a[u]=min(a[u],w);
			ok[u]=true;
		}
	}
	par[0][cur-1]=cur-1;
	for(int i=cur-2;i>=0;i--){
		int p=par[0][i];
		dep[i]=dep[p]+1;
		a[i]=min(a[i],a[p]);
	}
	for(int i=1;i<LG;i++)for(int u=0;u<cur;u++)par[i][u]=par[i-1][par[i-1][u]];
}

int getMinimumFuelCapacity(int u,int v){
	int res=a[lca(u,v)];
	return res<INF?res:-1;
}