#include "deliveries.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;

int n;
vector<pair<int,int>> adj[N];
int sz[N],hv[N],head[N],tail[N],par[N],tin[N],tout[N],ord[N];
ll w[N],dist[N],val[N];
set<pair<ll,int>> ch[N];
int timer;
ll tot,ans;

struct Fenwick{
	ll t[N];
	void update(int i,ll v){
		if(i>0)for(;i<N;i+=i&-i)t[i]+=v;
	}
	ll query(int i){
		ll res=0;
		for(;i>0;i-=i&-i)res+=t[i];
		return res;
	}
	ll query(int l,int r){
		return query(r)-query(l-1);
	}
}f,fw;

struct SegTree{
	ll t[K],lz[K];
	void apply(int i,ll v){
		t[i]+=v;
		lz[i]+=v;
	}
	void push(int i){
		apply(i*2,lz[i]);
		apply(i*2+1,lz[i]);
		lz[i]=0;
	}
	void update(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return apply(i,v);
		push(i);
		int m=(l+r)/2;
		update(l,m,i*2,x,y,v);
		update(m+1,r,i*2+1,x,y,v);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void update(int x,int y,ll v){
		update(1,n,1,x,y,v);
	}
	ll findlast(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x||t[i]<v)return 0;
		if(l==r)return l;
		push(i);
		int m=(l+r)/2;
		ll res=findlast(m+1,r,i*2+1,x,y,v);
		if(res==0)res=findlast(l,m,i*2,x,y,v);
		return res;
	}
	ll findlast(int x,int y,ll v){
		return findlast(1,n,1,x,y,v);
	}
}s;

void dfs(int u){
	sz[u]=1;
	for(auto [v,w]:adj[u])if(v!=par[u]){
		par[v]=u;
		dist[v]=dist[u]+w;
		dfs(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[hv[u]])hv[u]=v;
	}
}

void hld(int u){
	tin[u]=++timer;
	ord[timer]=u;
	if(!head[u])head[u]=u;
	tail[head[u]]=u;
	if(hv[u])head[hv[u]]=head[u],hld(hv[u]);
	for(auto [v,w]:adj[u])if(v!=par[u]&&v!=hv[u])hld(v);
	tout[u]=timer;
}

void update(int u,ll v){
	tot+=v;
	ans+=v*dist[u];
	f.update(tin[u],v);
	fw.update(tin[u],v*dist[u]);
	while(u){
		s.update(tin[head[u]],tin[u],v);
		u=head[u];
		int p=par[u];
		fw.update(tin[p],v*dist[p]);
		ch[p].erase({val[u],u});
		val[u]+=v;
		ch[p].emplace(val[u],u);
		u=p;
	}
}

void init(int _n,vector<int> _u,vector<int> _v,vector<int> _t,vector<int> _w){
	n=_n;
	for(int i=0;i<n-1;i++){
		int u=_u[i]+1,v=_v[i]+1,w=_t[i];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	for(int i=0;i<n;i++)w[i+1]=_w[i];
	w[1]++;
	dfs(1);
	hld(1);
	for(int i=1;i<=n;i++)update(i,w[i]);
}

ll max_time(int i,int x){
	i++;
	if(i==1)x++;
	update(i,x-w[i]);
	w[i]=x;
	int u=1;
	ll half=tot/2,res=0;
	while(true){
		int x=u;
		u=ord[s.findlast(tin[u],tin[tail[u]],half+1)];
		res+=fw.query(tin[x],tin[u]-1);
		if(ch[u].empty())break;
		auto [w,v]=*ch[u].rbegin();
		if(w<=half)break;
		res+=(f.query(tin[u],tout[u])-f.query(tin[v],tout[v]))*dist[u];
		u=v;
	}
	return (ans+dist[u]*(tot-2*f.query(tin[u],tout[u]))-2*res)*2;
}
