#include "dango3.h"
#include <bits/stdc++.h>

using namespace std;

void Solve(int n,int m){
	n*=m;
	vector<vector<int>> ans(m);
	auto ask=[&](const vector<bool> a){
		vector<int> b;
		for(int i=1;i<=n;i++)if(a[i])b.emplace_back(i);
		return m-Query(b)-1;
	};
	for(int i=1;i<=n;i++){
		int l=0,r=m-1;
		while(l<r){
			int md=(l+r)/2;
			vector<bool> ok(n+1,true);
			ok[i]=false;
			for(int j=0;j<=md;j++)for(auto x:ans[j])ok[x]=false;
			if(ask(ok)<=md)r=md;
			else l=md+1;
		}
		ans[l].emplace_back(i);
	}
	for(auto &x:ans)Answer(x);
}