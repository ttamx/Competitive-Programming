#include "expensive.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ld qr=123456789123456789;

struct line{
	mutable ld m,c,p;
	line(ld m=0,ld c=0,ld p=0):m(m),c(c),p(p){}
	bool operator<(const line&o)const{
		if(o.c==qr)return p<o.p;
		return m<o.m;
	}
};

struct convexhull:multiset<line>{
	ld inf=1.0/0.0;
	bool isect(iterator x,iterator y){
		if(y==end())return x->p=inf,false;
		if(x->m==y->m)x->p=x->c>=y->c?inf:-inf;
		else x->p=(x->c-y->c)/(y->m-x->m);
		return x->p>=y->p;
	}
	void add(ld m,ld c){
		auto x=insert(line(m,c,0)),y=x;
		while(isect(x,next(x)))erase(next(x));
		if(x!=begin()&&isect(--x,y))isect(x,erase(y));
		while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
	}
	ld get(ld x){
		if(empty())return -inf;
		auto l=*lower_bound(line(0,qr,x));
		return l.m*x+l.c;
	}
}cht;

const int N=1e6+5;

int n,q;
vector<pair<int,int>> adj[N];
pair<int,int> dp[N];
int lv[N],pa[N][20];
vector<int> lf;

void dfs(int u,int p){
	lv[u]=lv[p]+1;
	pa[u][0]=p;
	for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
	for(auto [v,i]:adj[u]){
		if(v==p)continue;
		dp[v]=dp[u];
		if(i==1)dp[v].first++;
		else dp[v].second++;
		dfs(v,u);
	}
}

int lca(int a,int b){
	if(lv[a]<lv[b])swap(a,b);
	for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
	if(a==b)return a;
	for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
	return pa[a][0];
}

pair<int,int> calc(int u,int v){
	auto [a1,b1]=dp[u];
	auto [a2,b2]=dp[v];
	auto [a3,b3]=dp[lca(u,v)];
	return {a1+a2-2*a3,b1+b2-2*b3};
}

void initialize(int N, int Q, vector<pair<int, int>> R,vector<int> C) {
	n=N,q=Q;
	for(int i=0;i<n-1;i++){
		auto [u,v]=R[i];
		adj[u].emplace_back(v,C[i]);
		adj[v].emplace_back(u,C[i]);
	}
	for(int i=0;i<n;i++)if(adj[i].size()==1)lf.emplace_back(i);
	dfs(0,0);
	for(int i=0;i<lf.size();i++){
		for(int j=0;j<i;j++){
			auto [a,b]=calc(lf[i],lf[j]);
			cht.add(a,b);
		}
	}
}

long long most_expensive(int a, int b) {
	ld x=1.0*a/b,y=b;
	return (ll)max((ld)0,cht.get(x)*y);
}