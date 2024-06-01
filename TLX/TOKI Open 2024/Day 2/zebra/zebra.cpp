#include "zebra.h"
#include <bits/stdc++.h>

using namespace std;

const int N=505;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n;
vector<pair<int,int>> adj[N];
bool bad[N];

void dfs(int u,int p){
	bad[u]=true;
	for(auto [v,i]:adj[u])if(v!=p)dfs(v,u);
}

int getsz(int u,int p){
	int s=1;
	for(auto [v,i]:adj[u])if(v!=p&&!bad[v])s+=getsz(v,u);
	return s;
}

bool is_root(int u){
	vector<int> path[2];
	function<void(int,int,int)> dfs=[&](int u,int p,int d){
		for(auto [v,i]:adj[u])if(v!=p){
			path[d].emplace_back(i);
			dfs(v,u,d^1);
		}
	};
	dfs(u,u,1);
	return !is_zebra(path[0])&&!is_zebra(path[1]);
}

int find_root(int _n,vector<int> U,vector<int> V){
	n=_n;
	for(int i=0;i<n;i++){
		adj[i].clear();
		bad[i]=false;
	}
	for(int i=0;i<n-1;i++){
		adj[U[i]].emplace_back(V[i],i);
		adj[V[i]].emplace_back(U[i],i);
	}
	int par_edge=-1;
	int rt=-1;
	auto get_dif=[&](){
		vector<pair<int,int>> tmp;
		for(auto [u,i]:adj[rt])if(!bad[u])tmp.emplace_back(u,i);
		vector<int> tmp2;
		for(auto [u,i]:tmp)tmp2.emplace_back(i);
		if(!is_zebra(tmp2))return rt;
		if(tmp.size()==3){
			vector<int> ord{0,1,2};
			shuffle(ord.begin(),ord.end(),rng);
			for(int i=0;i<2;i++){
				int j=ord[i];
				if(!is_zebra({tmp[(j+1)%3].second,tmp[(j+2)%3].second})){
					par_edge=tmp[j].second;
					return tmp[j].first;
				}
			}
			par_edge=tmp[ord[2]].second;
			return tmp[ord[2]].first;
		}
		if(is_zebra({tmp[0].second,tmp[1].second})){
			int res;
			tie(res,par_edge)=tmp[is_zebra({tmp[1].second,tmp[2].second})];
			return res;
		}
		int l=2,r=tmp.size()-1;
		while(l<r){
			int m=(l+r)/2;
			vector<int> tmp2;
			for(int i=0;i<=m;i++)tmp2.emplace_back(tmp[i].second);
			if(is_zebra(tmp2))r=m;
			else l=m+1;
		}
		par_edge=tmp[l].second;
		return tmp[l].first;
	};
	while(true){
		rt=-1;
		int mnsz=0;
		for(int i=0;i<n;i++)if(!bad[i]){
			int deg=0;
			for(auto [u,id]:adj[i])if(!bad[u])deg++;
			if(deg<3)continue;
			int mx=0;
			for(auto [u,id]:adj[i])if(!bad[u])mx=max(mx,getsz(u,i));
			if(rt==-1||mx<mnsz){
				rt=i;
				mnsz=mx;
			}
		}
		if(rt!=-1){
			int rt2=get_dif();
			if(rt==rt2)return rt;
			dfs(rt,rt2);
			continue;
		}
		assert(par_edge!=-1);
		vector<pair<int,int>> path;
		int st=-1;
		for(int i=0;i<n;i++)if(!bad[i]){
			int deg=0;
			for(auto [u,id]:adj[i])if(!bad[u])deg++;
			if(deg==0)return i;
			if(deg==1)st=i;
		}
		for(int u=st,p=-1;;){
			int v=-1,id=-1;
			for(auto [x,i]:adj[u])if(!bad[x]&&x!=p)v=x,id=i;
			if(v==-1)break;
			path.emplace_back(v,id);
			p=u,u=v;
		}
		if(is_root(st))return st;
		if(path.size()==1)return path.back().first;
		int l=1,r=(path.size()+1)/2;
		int bound=r;
		while(l<r){
			int m=(l+r)/2;
			vector<int> tmp;
			for(int i=0;i<=m;i++){
				tmp.emplace_back(path[i*2].second);
			}
			if(is_zebra(tmp))r=m;
			else l=m+1;
		}
		if(l==bound){
			return is_root(path.back().first)?path.back().first:path.end()[-2].first;
		}
		if(is_zebra({path[l*2].second,path[l*2-1].second}))return path[l*2-2].first;
		else return path[l*2-1].first;
	}
	return 0;
}