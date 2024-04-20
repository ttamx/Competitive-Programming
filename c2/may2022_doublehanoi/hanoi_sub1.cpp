#include "hanoi.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

const ll INF=LLONG_MAX/2;

ll hanoi(int n,vi s0,vi s1,vi s2,vi t0,vi t1,vi t2){
	assert(n<=2);
	vector<vi> s{s0,s1,s2},t{t0,t1,t2};
	for(auto &v:s)reverse(v.begin(),v.end());
	for(auto &v:t)reverse(v.begin(),v.end());
	queue<pair<int,vector<vi>>> q;
	map<vector<vi>,bool> vis;
	q.emplace(0,s);
	vis[s]=true;
	while(!q.empty()){
		auto [d,u]=q.front();
		q.pop();
		if(u==t)return d;
		for(int i=0;i<3;i++)if(!u[i].empty()){
			for(int j=0;j<3;j++)if(i!=j){
				if(!u[j].empty()&&u[i].back()>u[j].back())continue;
				u[j].emplace_back(u[i].back());
				u[i].pop_back();
				if(!vis[u]){
					vis[u]=true;
					q.emplace(d+1,u);
				}
				u[i].emplace_back(u[j].back());
				u[j].pop_back();
			}
		}
	}
	assert(false);
	return 0LL;
}