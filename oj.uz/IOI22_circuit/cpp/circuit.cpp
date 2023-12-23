#include "circuit.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=1<<18;
const ll mod=1e9+2022;

int n,m;
ll a[N],mul[N];
vector<int> adj[N];

struct segtree{
	ll t[K],all[K];
	bool lz[K];
	void pushlz(int l,int r,int i){
		if(!lz[i])return;
		t[i]=(mod+all[i]-t[i])%mod;
		if(l<r){
			lz[i*2]^=true;
			lz[i*2+1]^=true;
		}
		lz[i]=false;
	}
	void build(int l,int r,int i){
		if(l==r){
			t[i]=a[l]*mul[l];
			all[i]=mul[l];
			return;
		}
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=(t[i*2]+t[i*2+1])%mod;
		all[i]=(all[i*2]+all[i*2+1])%mod;
	}
	void build(){
		build(1,m,1);
	}
	void update(int l,int r,int i,int x,int y){
		pushlz(l,r,i);
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return lz[i]=true,pushlz(l,r,i),void();
		int m=(l+r)/2;
		update(l,m,i*2,x,y);
		update(m+1,r,i*2+1,x,y);
		t[i]=(t[i*2]+t[i*2+1])%mod;
	}
	void update(int x,int y){
		update(1,m,1,x,y);
	}
}s;

struct segtree2{
	ll t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=adj[l].size());
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=(t[i*2]*t[i*2+1])%mod;
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x,int v){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=v);
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=(t[i*2]*t[i*2+1])%mod;
	}
	void update(int x,int y){
		update(1,n,1,x,y);
	}
}s2;

void dfs(int u,int d=0){
	if(u>n)return void(mul[u-n]=s2.t[1]);
	s2.update(u,1);
	for(auto v:adj[u])dfs(v,d+1);
	s2.update(u,adj[u].size());
}

void init(int N,int M,vector<int> P,vector<int> A) {
	n=N,m=M;
	for(int i=1;i<=m;i++)a[i]=A[i-1];
	for(int i=1;i<n+m;i++)adj[P[i]+1].emplace_back(i+1);
	s2.build();
	dfs(1);
	s.build();
}

int count_ways(int L, int R) {
	L-=n-1;
	R-=n-1;
	s.update(L,R);
	return s.t[1];
}