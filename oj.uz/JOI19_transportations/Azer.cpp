#include "Azer.h"
#include <bits/stdc++.h>

using namespace std;

namespace Azer{

using P = pair<int,int>;

const int INF=INT_MAX/2;

int n;
vector<int> dp;
vector<bool> vis;
vector<vector<pair<int,int>>> adj;
int dat,counter,last;
priority_queue<P,vector<P>,greater<P>> pq;

void send(int id,int v){
	SendA(1);
	for(int i=0;i<9;i++)SendA(v>>i&1);
	for(int i=0;i<11;i++)SendA(id>>i&1);
}

void receive(int id,int dist){
	dist+=last;
	last=dist;
	dp[id]=dist;
	vis[id]=true;
	for(auto [v,w]:adj[id])if(dist+w<dp[v])pq.emplace(dp[v]=dist+w,v);
	while(!pq.empty()&&vis[pq.top().second])pq.pop();
	if(pq.empty())return SendA(0);
	auto [d,u]=pq.top();
	pq.pop();
	send(u,d-last);
}

}

void InitA(int _n, int a,vector<int> _u,vector<int> _v,vector<int> _c){
	using namespace Azer;
	dat=counter=0;
	n=_n;
	dp.assign(n,INF);
	vis.assign(n,false);
	adj.assign(n,{});
	for(int i=0;i<a;i++){
		int u=_u[i],v=_v[i],c=_c[i];
		adj[u].emplace_back(v,c);
		adj[v].emplace_back(u,c);
	}
	dp[0]=0;
	for(auto [v,w]:adj[0])pq.emplace(w,v);
	if(!pq.empty()){
		auto [d,u]=pq.top();
		send(u,d);
	}else{
		SendA(0);
	}
}

void ReceiveA(bool x){
	using namespace Azer;
	dat|=int(x)<<counter;
	counter++;
	if(counter==20){
		receive(dat>>9,dat&511);
		dat=counter=0;
	}
}

vector<int> Answer(){
	using namespace Azer;
	return dp;
}
