#include "bestbank.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll inf=1e18;
const ll max_val=1e7;

int n,k;
int sz[N],pa[N];
ll dist[N][20];
int lv[N];
bool used[N];
vector<pair<int,int>> adj[N];

struct LiChaoTree{
	struct node{
		ll m,c;
		node *l,*r;
		node(ll m=0,ll c=inf):m(m),c(c),l(nullptr),r(nullptr){}
		ll get(ll x){
			return m*x+c;
		}
	};
	typedef node* pnode;
	pnode rt=nullptr;
	void update(ll l,ll r,pnode &t,ll m,ll c){
		if(!t)return void(t=new node(m,c));
		node x(m,c);
		ll mid=(l+r)/2;
		if(x.get(mid)<t->get(mid))swap(x,*t);
		if(l==r)return;
		if(t->get(l)>x.get(l))update(l,mid,t->l,x.m,x.c);
		if(t->get(r)>x.get(r))update(mid+1,r,t->r,x.m,x.c);
	}
	void add(ll m,ll c){
		update(1,max_val,rt,m,c);
	}
	ll query(ll l,ll r,pnode &t,ll x){
		if(!t||x<l||r<x)return inf;
		if(l==r)return t->get(x);
		ll mid=(l+r)/2;
		return min({t->get(x),query(l,mid,t->l,x),query(mid+1,r,t->r,x)});
	}
	ll get(ll x){
		return query(1,max_val,rt,x);
	}
}lct[N];

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
	for(auto b:B)update_bank(b[0],b[1],b[2]);
}

void update_bank(int P, int F,long long L){
	for(int u=P;u!=-1;u=pa[u])lct[u].add(F,L+dist[P][lv[u]]);
}

long long find_best_bank(int S, int Y){
	ll res=inf;
	Y/=100;
	for(int u=S;u!=-1;u=pa[u])res=min(res,lct[u].get(Y)+dist[S][lv[u]]);
	return res;
}