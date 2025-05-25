#include "thief.h"
#include <bits/stdc++.h>

using namespace std;

void solve(int n,int m,vector<int> _u,vector<int> _v){
	vector<int> tmp(m);
	vector<vector<pair<int,int>>> adj(n);
	for(int i=0;i<m;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v,i);
		adj[v].emplace_back(u,~i);
	}
	vector<bool> used(n);
	vector<int> sz(n);
	function<int(int,int)> dfs_sz=[&](int u,int p)->int {
		sz[u]=1;
		for(auto [v,i]:adj[u]){
			if(v==p||used[v])continue;
			sz[u]+=dfs_sz(v,u);
		}
		return sz[u];
	};
	function<int(int,int,int)> centroid=[&](int u,int p,int tot)->int {
		for(auto [v,i]:adj[u])if(v!=p&&!used[v]&&sz[v]>tot/2)return centroid(v,u,tot);
		return u;
	};
	function<void(int,int,int)> dfs=[&](int u,int p,int rev){
		for(auto [v,i]:adj[u]){
			if(v==p)continue;
			if(i>=0)tmp[i]=rev;
			else tmp[~i]=rev^1;
			if(!used[v]){
				dfs(v,u,rev);
			}
		}
	};
	bool found=false;
	bool rev=false;
	vector<int> q;
	q.emplace_back(0);
	while(!q.empty()){
		int s=0;
		vector<int> nq;
		vector<vector<pair<int,int>>> group;
		for(int r=0;r<2;r++){
			for(auto u:q){
				dfs(u,-1,r);
			}
			if(query(tmp)){
				found=true;
				rev=r;
				break;
			}
		}
		if(found)break;
		for(auto u:q){
			u=centroid(u,-1,dfs_sz(u,-1));
			used[u]=true;
			vector<pair<int,int>> qq;
			for(auto [v,i]:adj[u]){
				if(!used[v]){
					nq.emplace_back(v);
					qq.emplace_back(v,i);
				}
			}
			group.emplace_back(qq);
			s=max(s,(int)qq.size());
		}
		assert(!nq.empty());
		int d=1;
		for(;d<s;d<<=1){
			for(int r=0;r<2;r++){
				for(auto &g:group){
					for(int i=0;i<g.size();i++){
						auto [v,id]=g[i];
						int rev=min(i&d,1)^r;
						dfs(v,-1,rev);
						if(id>=0)tmp[id]=rev;
						else tmp[~id]=rev^1;
					}
				}
				if(query(tmp)){
					found=true;
					break;
				}
			}
			if(found)break;
		}
		if(found)break;
		q=move(nq);
	}
	assert(found);
	auto base=tmp;
	int main_edge=-1;
	{
		int l=0,r=m-1;
		while(l<r){
			int mid=(l+r)/2;
			tmp=base;
			for(int i=0;i<=mid;i++){
				tmp[i]^=1;
			}
			if(!query(tmp))r=mid;
			else l=mid+1;
		}
		main_edge=l;
	}
	assert(main_edge!=-1);
	int st=_u[main_edge];
	int ed=_v[main_edge];
	if(base[main_edge]){
		swap(st,ed);
	}
	int a=-1,b=-1;
	{
		tmp=base;
		vector<pair<int,int>> ord;
		vector<bool> vis(n);
		vis[st]=true;
		vis[ed]=true;
		ord.emplace_back(st,-1);
		for(int i=0;i<ord.size();i++){
			int u=ord[i].first;
			for(auto [v,i]:adj[u]){
				if(!vis[v]){
					vis[v]=true;
					ord.emplace_back(v,~i);
				}
			}
		}
		int l=0,r=ord.size()-1;
		while(l<r){
			int mid=(l+r)/2;
			for(int i=1;i<ord.size();i++){
				int j=ord[i].second;
				if(i>mid)j=~j;
				if(j>=0)tmp[j]=0;
				else tmp[~j]=1;
			}
			if(query(tmp))r=mid;
			else l=mid+1;
		}
		a=ord[l].first;
	}
	{
		tmp=base;
		vector<pair<int,int>> ord;
		vector<bool> vis(n);
		vis[st]=true;
		vis[ed]=true;
		ord.emplace_back(ed,-1);
		for(int i=0;i<ord.size();i++){
			int u=ord[i].first;
			for(auto [v,i]:adj[u]){
				if(!vis[v]){
					vis[v]=true;
					ord.emplace_back(v,i);
				}
			}
		}
		int l=0,r=ord.size()-1;
		while(l<r){
			int mid=(l+r)/2;
			for(int i=1;i<ord.size();i++){
				int j=ord[i].second;
				if(i>mid)j=~j;
				if(j>=0)tmp[j]=0;
				else tmp[~j]=1;
			}
			if(query(tmp))r=mid;
			else l=mid+1;
		}
		b=ord[l].first;
	}
	answer(a,b);
}
