#include "cheatsheet.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> write_cheatsheet(int n, vector<int> a){
	vector<int> r;
	vector<vector<int>> vec(350005);
	for(int i=0;i<n;i++){
		vec[a[i]].emplace_back(i);
	}
	int idx=0;
	for(int i=1;i<=350000;i++){
		if(vec[i].empty())continue;
		for(auto x:vec[i])r.emplace_back(x);
		int pre=i/599+1,suf=i%599+1;
		r.emplace_back(pre*1000+idx++);
		r.emplace_back(suf*1000+idx++);
	}
	return r;
}

vector<int> recover_answer(int n, vector<int> r){
	vector<int> ans(n);
	queue<int> q;
	for(int i=0;i<r.size();i++){
		if(r[i]<=n){
			q.emplace(r[i]);
			continue;
		}
		int pre=r[i]/1000-1;
		i++;
		int suf=r[i]/1000-1;
		while(!q.empty()){
			ans[q.front()]=pre*599+suf;
			q.pop();
		}
	}
	return ans;
}
