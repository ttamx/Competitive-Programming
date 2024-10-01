#include "roads.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n;
vector<pair<int,int>> adj[N];
ll dp[N][2];
ll sum[N],val[N],mn[N];
int deg[N];
int par[N],we[N];
vector<int> event[N];
int disc[N];
int timer=0;
set<pair<int,int>,greater<pair<int,int>>> nodes;
bool vis[N];

struct Treap{
	struct Node;
	using Ptr = Node*;
	struct Node{
		ll val,sum;
		int sz,prio;
		Ptr l,r;
		Node(ll _val):val(_val),sum(_val),sz(1),prio(rng()),l(),r(){}
	};
	Ptr root;
	Treap():root(){}
	int get_sz(Ptr t){
		return t?t->sz:0;
	}
	ll get_sum(Ptr t){
		return t?t->sum:0LL;
	}
	void pull(Ptr t){
		if(!t)return;
		t->sz=get_sz(t->l)+get_sz(t->r)+1;
		t->sum=get_sum(t->l)+get_sum(t->r)+t->val;
	}
	void merge(Ptr &t,Ptr l,Ptr r){
		if(!l)return void(t=r);
		if(!r)return void(t=l);
		if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
		else merge(r->l,l,r->l),t=r;
		pull(t);
	}
	void split(Ptr t,Ptr &l,Ptr &r,int k){
		if(!t)return void(l=r=nullptr);
		int sz=get_sz(t->l)+1;
		if(sz<=k)split(t->r,t->r,r,k-sz),l=t;
		else split(t->l,l,t->l,k),r=t;
		pull(t);
	}
	void split_key(Ptr t,Ptr &l,Ptr &r,ll key){
		if(!t)return void(l=r=nullptr);
		if(t->val<key)split_key(t->r,t->r,r,key),l=t;
		else split_key(t->l,l,t->l,key),r=t;
		pull(t);
	}
	void insert(ll val){
		Ptr l,r;
		split_key(root,l,r,val);
		merge(root,l,new Node(val));
		merge(root,root,r);
	}
	void erase(ll val){
		Ptr l,r,x;
		split_key(root,l,r,val);
		split(r,x,r,1);
		assert(get_sz(x)==1);
		assert(x->val==val);
		delete x;
		merge(root,l,r);
	}
	ll query(int k){
		Ptr l,r;
		split(root,l,r,k);
		ll res=get_sum(l);
		merge(root,l,r);
		return res;
	}
}tr[N];

struct DSU{
	int p[N],sz[N];
	DSU(){
		iota(p,p+N,0);
	}
	int fp(int u){
		return p[u]=u==p[u]?u:fp(p[u]);
	}
	void uni(int u,int v){
		p[fp(u)]=fp(v);
	}
}dsu;

void dfs(int u,int p){
	par[u]=p;
	disc[u]=++timer;
	for(auto [v,w]:adj[u])if(v!=p){
		we[v]=w;
		dfs(v,u);
	}
}

void upd(int u){
	int p=par[u];
	if(p==-1)return;
	sum[p]-=mn[u];
	if(val[u]>0){
		tr[p].erase(val[u]);
	}else{
		deg[p]++;
	}
	if(dp[u][0]<dp[u][1]+we[u]){
		mn[u]=dp[u][0];
		val[u]=dp[u][1]-dp[u][0]+we[u];
	}else{
		mn[u]=dp[u][1]+we[u];
		val[u]=0;
	}
	if(val[u]>0){
		tr[p].insert(val[u]);
	}else{
		deg[p]--;
	}
	sum[p]+=mn[u];
}

vector<ll> minimum_closure_costs(int _n,vector<int> _u,vector<int> _v,vector<int> _w){
	n=_n;
	vector<ll> ans(n);
	for(int i=0;i<n-1;i++){
		int u=_u[i],v=_v[i],w=_w[i];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
		ans[0]+=w;
	}
	for(int i=0;i<n;i++){
		event[adj[i].size()].emplace_back(i);
	}
	dfs(0,-1);
	for(int i=0;i<n;i++){
		deg[i]=1;
		nodes.emplace(disc[i],i);
	}
	deg[0]=0;
	for(int k=1;k<n;k++){
		priority_queue<pair<int,int>> pq;
		vector<int> roots;
		for(auto u:event[k]){
			nodes.erase(make_pair(disc[u],u));
			for(auto [v,w]:adj[u])if(v!=par[u]){
				dsu.uni(v,u);
			}
			u=dsu.fp(u);
			dp[u][0]=dp[u][1]=0;
			upd(u);
		}
		auto work=[&](int t){
			while(!pq.empty()&&pq.top().first>t){
				int u=pq.top().second;
				pq.pop();
				if(vis[u])continue;
				vis[u]=true;
				roots.emplace_back(u);
				upd(u);
			}
		};
		for(auto [t,u]:nodes){
			work(t);
			int p=dsu.fp(u);
			pq.emplace(disc[p],p);
			dp[u][0]=dp[u][1]=sum[u];
			if(deg[u]>k){
				dp[u][0]+=tr[u].query(deg[u]-k);
			}
			if(deg[u]>k+1){
				dp[u][1]+=tr[u].query(deg[u]-k-1);
			}
			if(p!=u){
				dp[p][0]+=min(dp[u][0],dp[u][1]+we[u]);
				dp[p][1]+=min(dp[u][0],dp[u][1]+we[u]);
			}
		}
		work(-1);
		ans[k]=dp[0][0];
		for(auto u:roots){
			vis[u]=false;
			dp[u][0]=dp[u][1]=0;
			upd(u);
		}
	}
	return ans;
}
