#include "highway.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=90005;
const int M=130005;

int n,m,a,b;
vector<int> e;
vector<int> edge1(M),edge2(M),dist1(N),dist2(N);
vector<p2> adj[N];
long long cost;
vector<t3> group1,group2;
int type[M];
int mainedge;

void bfs(int st,vector<int> &dist,vector<int> &edge){
	queue<int> q;
	edge[st]=mainedge;
	dist[st]=1;
	q.emplace(st);
	while(!q.empty()){
		auto u=q.front();
		q.pop();
		for(auto [v,id]:adj[u]){
			if(dist[v])continue;
			edge[v]=id;
			dist[v]=dist[u]+1;
			q.emplace(v);
		}
	}
}

int sol1(){
	int l=0,r=m-1;
	while(l<r){
		int mid=(l+r)/2;
		for(int i=0;i<m;i++)e[i]=i<=mid;
		if(ask(e)!=cost)r=mid;
		else l=mid+1;
	}
	return l;
}

int sol2(vector<t3> &ingroup,vector<t3> &exgroup){
	int l=0,r=ingroup.size()-1;
	while(l<r){
		int mid=(l+r)/2;
		e=vector<int>(m,1);
		for(auto x:exgroup)e[get<2>(x)]=0;
		for(int i=1;i<=mid;i++)e[get<2>(ingroup[i])]=0;
		if(ask(e)==cost)r=mid;
		else l=mid+1;
	}
	return get<1>(ingroup[l]);
}

void find_pair(int n, vector<int> U, vector<int> V, int A, int B){
	a=A,b=B;
	m=U.size();
	for(int i=0;i<m;i++){
		int u=U[i],v=V[i];
		adj[u].emplace_back(v,i);
		adj[v].emplace_back(u,i);
	}
	e=vector<int>(m,0);
	cost=ask(e);
	mainedge=sol1();
	int st1=U[mainedge];
	int st2=V[mainedge];
	bfs(st1,dist1,edge1);
	bfs(st2,dist2,edge2);
	for(int i=0;i<n;i++){
		if(dist1[i]<dist2[i])group1.emplace_back(dist1[i],i,edge1[i]);
		if(dist2[i]<dist1[i])group2.emplace_back(dist2[i],i,edge2[i]);
	}
	sort(group1.begin(),group1.end());
	sort(group2.begin(),group2.end());
	int ans1=sol2(group1,group2);
	int ans2=sol2(group2,group1);
	answer(ans1,ans2);
}