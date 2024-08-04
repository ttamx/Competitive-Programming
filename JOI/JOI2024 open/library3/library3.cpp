#include "library3.h"
#include <bits/stdc++.h>

using namespace std;

mt19937 rng(7891629);

void solve(int n){
	vector<int> p(n),ip(n);
	iota(p.begin(),p.end(),0);
	shuffle(p.begin(),p.end(),rng);
	for(int i=0;i<n;i++)ip[p[i]]=i;
	auto swapp=[&](int a,int b){
		swap(p[a],p[b]);
		ip[p[a]]=a;
		ip[p[b]]=b;
	};
	int cur=query(p);
	for(int i=1;i<n;i++){
		swapp(ip[0],ip[i]);
		int res=query(p);
		if(res>cur)cur=res;
		else swapp(ip[0],ip[i]);
		if(cur==n-1)break;
	}
	vector<vector<int>> q{p};
	while(!q.empty()){
		vector<vector<int>> nq;
		priority_queue<pair<int,int>> pq;
		vector<vector<int>> b(q.size()),c(q.size());
		for(int i=0;i<q.size();i++){
			auto &a=q[i];
			if(a.size()<=1)continue;
			shuffle(a.begin(),a.end(),rng);
			swapp(ip[a[0]],ip[a[1]]);
			cur--;
			b[i].emplace_back(a[0]);
			c[i].emplace_back(a[1]);
			if(a.size()>2)pq.emplace(a.size()-1,i);
		}
		while(!pq.empty()){
			auto [id,i]=pq.top();
			pq.pop();
			if(pq.empty()){
				swapp(ip[q[i][0]],ip[q[i][id]]);
				int res=query(p);
				swapp(ip[q[i][0]],ip[q[i][id]]);
				if(res<cur){
					b[i].emplace_back(q[i][id]);
				}else{
					c[i].emplace_back(q[i][id]);
				}
				if(id>2)pq.emplace(id-1,i);
			}else{
				auto [jd,j]=pq.top();
				pq.pop();
				swapp(ip[q[i][0]],ip[q[i][id]]);
				swapp(ip[q[j][0]],ip[q[j][jd]]);
				int res=query(p);
				swapp(ip[q[i][0]],ip[q[i][id]]);
				swapp(ip[q[j][0]],ip[q[j][jd]]);
				if(res<cur){
					b[i].emplace_back(q[i][id]);
					b[j].emplace_back(q[j][jd]);
				}else if(res>cur){
					c[i].emplace_back(q[i][id]);
					c[j].emplace_back(q[j][jd]);
				}else{
					swapp(ip[q[i][0]],ip[q[i][id]]);
					res=query(p);
					swapp(ip[q[i][0]],ip[q[i][id]]);
					if(res<cur){
						b[i].emplace_back(q[i][id]);
						c[j].emplace_back(q[j][jd]);
					}else{
						c[i].emplace_back(q[i][id]);
						b[j].emplace_back(q[j][jd]);
					}
				}
				if(id>2)pq.emplace(id-1,i);
				if(jd>2)pq.emplace(jd-1,j);
			}
		}
		for(int i=0;i<q.size();i++)if(q[i].size()>1){
			nq.emplace_back(b[i]);
			nq.emplace_back(c[i]);
		}
		swap(q,nq);
	}
	answer(p);
}
