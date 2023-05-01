#include "bestbank.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll inf=1e18;

int n,k;
int sz[N],pa[N];
ll dist[N][20];
int lv[N];
bool used[N];
vector<pair<int,int>> adj[N];
bool querymode;

struct line{
	mutable ll m,c,p;
	line(ll p):m(0),c(inf),p(p){}
	line(ll m,ll c):m(m),c(c),p(0){}
	bool operator<(const line &o)const{return querymode?p<o.p:m>o.m;}
};

struct convexhull:multiset<line>{
	ll div(ll a,ll b){return a/b-(a^b<0&&a%b);}
	bool isect(iterator x,iterator y){
		if(y==end())return x->p=inf,false;
		if(x->m==y->m)x->p=x->c<=y->c?inf:-inf;
		else x->p=div(x->c-y->c,y->m-x->m);
		return x->p>=y->p;
	}
	void add(ll m,ll c){
		auto y=insert(line(m,c)),x=y,z=next(y);
		while(isect(y,z))z=erase(z);
		if(x!=begin()&&isect(--x,y))isect(x,erase(y));
		while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
	}
	ll get(ll x){
		if(empty())return inf;
		querymode=true;
		auto l=lower_bound(line(x));
		querymode=false;
		return l->m*x+l->c;
	}
}cht[N];

int dfs(int u,int p=-1){
	sz[u]=1;
	for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
	return sz[u];
}

int centroid(int u,int cnt,int p=-1){
	for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
	return u;
}

void filldist(int u,int d,int p=-1){
	for(auto [v,w]:adj[u]){
		if(used[v]||v==p)continue;
		dist[v][d]=dist[u][d]+w;
		filldist(v,d,u);
	}
}

void decom(int u,int d,int p=-1){
	u=centroid(u,dfs(u));
	pa[u]=p;
	used[u]=true;
	lv[u]=d;
	filldist(u,d);
	for(auto [v,w]:adj[u])if(!used[v])decom(v,d+1,u);
}

void initialize(int N, int K,vector<vector<int>> R,vector<vector<long long>> B){
	n=N,k=K;
	for(auto &r:R){
		int u=r[0],v=r[1],w=r[2];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	decom(0,0);
	for(auto b:B){
		int p=b[0],f=b[1];
		ll l=b[2];
		update_bank(p,f,l);
	}
}

void update_bank(int P, int F,long long L){
	for(int u=P;u!=-1;u=pa[u])cht[u].add(F,L+dist[P][lv[u]]);
}

long long find_best_bank(int S, int Y){
	ll res=inf;
	Y/=100;
	for(int u=S;u!=-1;u=pa[u])res=min(res,cht[u].get(Y)+dist[S][lv[u]]);
	return res;
}