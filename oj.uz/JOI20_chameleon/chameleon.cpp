#include "chameleon.h"
#include <bits/stdc++.h>

using namespace std;

void Solve(int n){
	auto check=[&](vector<int> &a,int l,int r,int u){
		vector<int> b{u};
		for(int i=l;i<=r;i++)b.emplace_back(a[i]);
		return Query(b)<b.size();
	};
	auto bsearch=[&](vector<int> &a,int st,int u){
		int l=st,r=a.size();
		while(l<r){
			int m=(l+r)/2;
			if(check(a,st,m,u))r=m;
			else l=m+1;
		}
		return l;
	};
	vector<vector<int>> adj(2*n+1);
	for(int i=2;i<=2*n;i++){
		vector<int> col(i);
		function<void(int,int)> dfs=[&](int u,int c){
			if(col[u])return;
			col[u]=c;
			for(auto v:adj[u])dfs(v,3-c);
		};
		for(int j=1;j<i;j++)dfs(j,1);
		array<vector<int>,2> comp;
		for(int j=1;j<i;j++)comp[col[j]-1].emplace_back(j);
		for(auto &a:comp){
			int st=0;
			while(check(a,st,a.size()-1,i)){
				st=bsearch(a,st,i);
				int u=a[st];
				adj[i].emplace_back(u);
				adj[u].emplace_back(i);
				st++;
			}
		}
	}
	vector<int> ans(2*n+1),val(2*n+1);
	for(int i=1;i<=2*n;i++){
		auto &a=adj[i];
		if(a.size()==1){
			ans[i]=a[0];
			ans[a[0]]=i;
		}else{
			for(auto x:a)val[i]^=x;
			while(Query({i,a[0],a[1]})>1){
				rotate(a.begin(),a.begin()+1,a.end());
			}
			val[i]^=a[2];
			val[a[2]]^=i;
		}
	}
	for(int i=1;i<=2*n;i++){
		if(!ans[i])ans[i]=val[i];
		if(i<ans[i])Answer(i,ans[i]);
	}
}
