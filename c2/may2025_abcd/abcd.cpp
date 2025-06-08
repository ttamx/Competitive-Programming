#include "abcd.h"
#include <bits/stdc++.h>

using namespace std;

mt19937 rng(time(0));

vector<char> abcd(int n){
	vector<int> ans(n);
	vector<array<int,4>> p(n,{0,1,2,3});
	auto ask=[&](vector<int> a){
		vector<char> tmp(n);
		for(int i=0;i<n;i++)tmp[i]='A'+p[i][a[i]];
		return exam(tmp);
	};
	for(auto &x:p)shuffle(x.begin(),x.end(),rng);
	int base=ask(vector<int>(n,0));
	vector<vector<array<int,3>>> group;
	for(int i=0;i<n;i+=2){
		if(i+1<n){
			int v0=base;
			vector<int> b(n,0);
			b[i]=b[i+1]=1;
			int v1=ask(b);
			if(v1==v0-2){
				ans[i]=0;
				ans[i+1]=0;
				continue;
			}
			if(v1==v0+2){
				ans[i]=1;
				ans[i+1]=1;
				continue;
			}
			b[i]=b[i+1]=2;
			int v2=ask(b);
			if(v2==v1+2){
				ans[i]=2;
				ans[i+1]=2;
				continue;
			}
			if(v0==v1&&v1==v2){
				ans[i]=3;
				ans[i+1]=3;
				continue;
			}
			vector<int> pos;
			int mx=max({v0,v1,v2});
			if(v0==mx)pos.emplace_back(0);
			if(v1==mx)pos.emplace_back(1);
			if(v2==mx)pos.emplace_back(2);
			if(pos.size()<2)pos.emplace_back(3);
			assert(pos.size()==2);
			vector<array<int,3>> cur;
			cur.push_back({pos[0],pos[1],i});
			cur.push_back({pos[1],pos[0],i+1});
			group.emplace_back(cur);
		}else{
			int v0=base;
			vector<int> b(n,0);
			b[i]=1;
			int v1=ask(b);
			if(v1==v0-1){
				ans[i]=0;
				continue;
			}
			if(v1==v0+1){
				ans[i]=1;
				continue;
			}
			vector<array<int,3>> cur(1,{2,3,i});
			group.emplace_back(cur);
		}
	}
	auto swapp=[&](vector<array<int,3>> &g){
		for(auto &e:g)swap(e[0],e[1]);
	};
	while(group.size()>1){
		vector<vector<array<int,3>>> new_group;
		auto a=ans;
		for(auto &g:group){
			if(rng()&1)swapp(g);
			for(int i=0;i<g.size();i++){
				int j=g[i][2];
				a[j]=g[i][0];
			}
		}
		base=ask(a);
		for(int i=0;i<group.size();i+=2){
			auto &g1=group[i];
			int j1=g1[0][2];
			if(i+1<group.size()){
				auto &g2=group[i+1];
				int j2=g2[0][2];
				auto b=a;
				b[j1]=g1[0][1];
				b[j2]=g2[0][1];
				int v=ask(b);
				if(v==base-2){
					for(auto e:g1)ans[e[2]]=e[0];
					for(auto e:g2)ans[e[2]]=e[0];
					continue;
				}
				if(v==base+2){
					for(auto e:g1)ans[e[2]]=e[1];
					for(auto e:g2)ans[e[2]]=e[1];
					continue;
				}
				swapp(g2);
				g1.insert(g1.end(),g2.begin(),g2.end());
				new_group.emplace_back(g1);
			}else{
				new_group.emplace_back(g1);
			}
		}
		group=move(new_group);
	}
	if(!group.empty()){
		auto &g=group[0];
		int i=g[0][2];
		vector<int> a(n);
		a[i]=g[0][0];
		int v0=ask(a);
		a[i]=g[0][1];
		int v1=ask(a);
		for(auto e:g)ans[e[2]]=e[v1>v0];
	}
	vector<char> res(n);
	for(int i=0;i<n;i++)res[i]='A'+p[i][ans[i]];
	return res;
}
