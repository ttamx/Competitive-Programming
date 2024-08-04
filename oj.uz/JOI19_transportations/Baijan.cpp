#include "Baijan.h"
#include <bits/stdc++.h>

using namespace std;

namespace Baijan{

using P = pair<int,int>;

const int INF=INT_MAX/2;

int n;
vector<int> dp;
vector<vector<pair<int,int>>> adj;
int dat,counter,last;
priority_queue<P,vector<P>,greater<P>> pq;

void send(int id,int v){
	for(int i=0;i<9;i++)SendB(v>>i&1);
	for(int i=0;i<11;i++)SendB(id>>i&1);
}

void receive(int id,int dist){
	dist+=last;
	pq.emplace(dist,id);
	while(!pq.empty()&&dp[pq.top().second]<INF)pq.pop();
	if(pq.empty())return;
	auto [d,u]=pq.top();
	dp[u]=d;
	for(auto [v,w]:adj[u])if(dp[v]==INF)pq.emplace(d+w,v);
	send(u,d-last);
	last=d;
}

}

void InitB(int _n, int b,vector<int> _u,vector<int> _v,vector<int> _c){
	using namespace Baijan;
	n=_n;
	dp.assign(n,INF);
	adj.assign(n,{});
	for(int i=0;i<b;i++){
		int u=_u[i],v=_v[i],c=_c[i];
		adj[u].emplace_back(v,c);
		adj[v].emplace_back(u,c);
	}
	dp[0]=0;
	for(auto [v,w]:adj[0])pq.emplace(w,v);
		dat=0,counter=-1;
}

void ReceiveB(bool x){
	using namespace Baijan;
	if(counter==-1){
		if(x){
			counter++;
		}else{
			receive(0,0);
		}
		return;
	}
	dat|=int(x)<<counter;
	counter++;
	if(counter==20){
		receive(dat>>9,dat&511);
		dat=0,counter=-1;
	}
}