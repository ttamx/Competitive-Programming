#include "meetings.h"
#include<bits/stdc++.h>

using namespace std;

void Solve(int n){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	vector<vector<int>> comp(n);
	for(int i=1;i<n;i++)comp[0].emplace_back(i);
	auto link=[&](int u,int v){
		if(u>v)swap(u,v);
		Bridge(u,v);
	};
	function<void(int)> dnc=[&](int s){
		int sz=comp[s].size();
		if(!sz)return;
		vector<int> res,path{s};
		swap(res,comp[s]);
		int t=res[rng()%sz];
		for(auto u:res)if(u!=t){
			int v=Query(s,t,u);
			if(u==v)path.emplace_back(u);
			else comp[v].emplace_back(u);
		}
		sort(path.begin()+1,path.end(),[&](int l,int r){
			return Query(s,l,r)==l;
		});
		path.emplace_back(t);
		for(int i=1;i<path.size();i++)link(path[i-1],path[i]);
		for(auto u:path)dnc(u);
	};
	dnc(0);
}