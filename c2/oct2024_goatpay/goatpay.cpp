#include "goatpay.h"
#include <bits/stdc++.h>

using namespace std;

const int N=1e6+5;

struct Fenwick{
	int n;
	vector<int> t;
	void init(int _n){
		n=_n;
		t.assign(n+1,0);
	}
	void update(int i,int v){
		assert(i>=1);
		for(;i<=n;i+=i&-i){
			t[i]^=v;
		}
	}
	int query(int i){
		int res=0;
		for(;i>0;i-=i&-i){
			res^=t[i];
		}
		return res;
	}
}f[N];

int n;
vector<pair<int,int>> adj[N];
int c[N],w[N];
int tin[N],tout[N];
int timer;
vector<int> ct[N];
int pos1[N],pos2[N];
int cnt[N];

void dfs(int u,int p=-1){
	for(auto [v,i]:adj[u]){
		if(v==p)continue;
		tin[v]=++timer;
		ct[c[i]].emplace_back(tin[v]);
		pos1[i]=ct[c[i]].size();
		f[c[i]].update(pos1[i],w[i]);
		dfs(v,u);
		tout[v]=++timer;
		ct[c[i]].emplace_back(tout[v]);
		pos2[i]=ct[c[i]].size();
		f[c[i]].update(pos2[i],w[i]);
	}
}

void plant_tree(int _n,vector<int> _u,vector<int> _v,vector<int> _w,vector<int> _c){
	n=_n;
	for(int i=0;i<n-1;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v,i);
		adj[v].emplace_back(u,i);
		w[i]=_w[i],c[i]=_c[i];
		cnt[c[i]]+=2;
	}
	for(int i=1;i<=n;i++)f[i].init(cnt[i]);
	dfs(0);
}

int goat_pay(int u,int v,int x){
	if(tin[u]>tin[v])swap(u,v);
	auto &a=ct[x];
	int l=upper_bound(a.begin(),a.end(),tin[u])-a.begin();
	int r=upper_bound(a.begin(),a.end(),tin[v])-a.begin();
	return f[x].query(r)^f[x].query(l);
}

void update_edge(int i,int d){
	d^=w[i];
	f[c[i]].update(pos1[i],d);
	f[c[i]].update(pos2[i],d);
	w[i]^=d;
}