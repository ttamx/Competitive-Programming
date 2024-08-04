#include "joitour.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
vector<int> adj[N];
int a[N];

enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};

struct StaticTopTree{
	int root,node_id;
	int hv[N],p[N];
	int lch[4*N],rch[4*N],par[4*N];
	Type type[4*N];
	int dfs(int u){
		int s=1,mx=0;
		for(int v:adj[u])if(v!=p[u]){
			p[v]=u;
			int t=dfs(v);
			if(t>mx)mx=t,hv[u]=v;
			s+=t;
		}
		return s;
	}
	int add(int i,int l,int r,Type t){
		if(!i)i=++node_id;
		lch[i]=l,rch[i]=r,type[i]=t;
		if(l)par[l]=i;
		if(r)par[r]=i;
		return i;
	}
	pair<int,int> merge(const vector<pair<int,int>> &a,Type t){
		if(a.size()==1)return a[0];
		int tot=0;
		vector<pair<int,int>> b,c;
		for(auto [i,s]:a)tot+=s;
		for(auto [i,s]:a){
			(tot>s?b:c).emplace_back(i,s);
			tot-=s*2;
		}
		auto [i,si]=merge(b,t);
		auto [j,sj]=merge(c,t);
		return {add(0,i,j,t),si+sj};
	}
	pair<int,int> compress(int i){
		vector<pair<int,int>> a{add_vertex(i)};
		while(hv[i])a.emplace_back(add_vertex(i=hv[i]));
		return merge(a,Compress);
	}
	pair<int,int> rake(int i){
		vector<pair<int,int>> a;
		for(auto j:adj[i])if(j!=p[i]&&j!=hv[i])a.emplace_back(add_edge(j));
		return a.empty()?make_pair(0,0):merge(a,Rake);
	}
	pair<int,int> add_edge(int i){
		auto [j,s]=compress(i);
		return {add(0,j,0,AddEdge),s};
	}
	pair<int,int> add_vertex(int i){
		auto [j,s]=rake(i);
		return {add(i,j,0,j?AddVertex:Vertex),s+1};
	}
	void build(){
		node_id=n;
		dfs(1);
		root=compress(1).first;
	}
}stt;

struct Info{
	ll c0,c2,c10,c12,c02,p10,p12,s1,ans;
}dp[4*N];

Info compress(Info p,Info c){
	Info res;
	res.c0=p.c0+c.c0,res.c2=p.c2+c.c2,res.s1=p.s1+c.s1;
	res.c10=p.c10+c.c10+p.s1*c.c0;
	res.c12=p.c12+c.c12+p.s1*c.c2;
	res.p10=p.p10+c.p10+c.s1*p.c0;
	res.p12=p.p12+c.p12+c.s1*p.c2;
	res.ans=p.ans+c.ans+p.c0*c.c12+p.c2*c.c10+c.c0*p.p12+c.c2*p.p10;
	return res;
}

Info rake(Info l,Info r){
	Info res;
	res.c0=l.c0+r.c0,res.c2=l.c2+r.c2;
	res.c02=l.c02+r.c02+l.c0*r.c2+l.c2*r.c0;
	res.c10=l.c10+r.c10,res.c12=l.c12+r.c12;
	res.ans=l.ans+r.ans+l.c0*r.c12+l.c2*r.c10+r.c0*l.c12+r.c2*l.c10;
	return res;
}

Info add_edge(Info x){
	Info res;
	res.c0=x.c0,res.c2=x.c2;
	res.c10=x.c10,res.c12=x.c12;
	res.c02=0;
	res.ans=x.ans;
	return res;
}

Info add_vertex(Info x,int i){
	Info res;
	res.c0=x.c0+(a[i]==0);
	res.c2=x.c2+(a[i]==2);
	res.s1=a[i]==1;
	res.c10=res.p10=x.c10+res.s1*x.c0;
	res.c12=res.p12=x.c12+res.s1*x.c2;
	res.ans=x.ans+res.s1*x.c02+(a[i]==0)*x.c12+(a[i]==2)*x.c10;
	return res;
}

Info vertex(int i){
	Info res;
	res.c0=a[i]==0,res.s1=a[i]==1,res.c2=a[i]==2;
	res.c10=res.c12=res.p10=res.p12=res.ans=0;
	return res;
}

void update(int i){
	if(stt.type[i]==Compress)dp[i]=compress(dp[stt.lch[i]],dp[stt.rch[i]]);
	else if(stt.type[i]==Rake)dp[i]=rake(dp[stt.lch[i]],dp[stt.rch[i]]);
	else if(stt.type[i]==AddEdge)dp[i]=add_edge(dp[stt.lch[i]]);
	else if(stt.type[i]==AddVertex)dp[i]=add_vertex(dp[stt.lch[i]],i);
	else if(stt.type[i]==Vertex)dp[i]=vertex(i);
}

void dfs(int i){
	if(!i)return;
	dfs(stt.lch[i]);
	dfs(stt.rch[i]);
	update(i);
}

void init(int _n,vector<int> _a,vector<int> _u,vector<int> _v,int Q){
	n=_n;
	for(int i=1;i<=n;i++)a[i]=_a[i-1];
	for(int i=0;i<n-1;i++){
		int u=_u[i]+1,v=_v[i]+1;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	stt.build();
	dfs(stt.root);
}

void change(int i,int t){
	i++;
	a[i]=t;
	for(int u=i;u;u=stt.par[u])update(u);
}

ll num_tours(){
	return dp[stt.root].ans;
}