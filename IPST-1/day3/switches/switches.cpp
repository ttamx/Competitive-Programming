#include "switches.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e4+5;
const int K=1<<17;

ll qs[N],dp[N],l[N],r[N];
ll a[N],c[N];
set<pair<int,int>> s;

struct segtree{
	ll tree[K];
	bool lz[K];
	void pushlz(int l,int r,int i){
		if(!lz[i])return;
		tree[i]=(qs[r]-qs[l-1])-tree[i];
		if(l<r){
			lz[i*2]=!lz[i*2];
			lz[i*2+1]=!lz[i*2+1];
		}
		lz[i]=false;
	}
	void build(int l,int r,int i){
		if(l==r){
			tree[i]=a[l];
			return;
		}
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		tree[i]=tree[i*2]+tree[i*2+1];
	}
	void update(int l,int r,int i,int x,int y){
		pushlz(l,r,i);
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			lz[i]=true;
			pushlz(l,r,i);
			return;
		}
		int m=(l+r)/2;
		update(l,m,i*2,x,y);
		update(m+1,r,i*2+1,x,y);
		tree[i]=tree[i*2]+tree[i*2+1];
	}
};

long long minimum_energy(int N, int M, int K, std::vector<int> A, std::vector<int> L, std::vector<int> R, std::vector<int> C){
	for(int i=0;i<N;i++){
		a[i+1]=A[i];
	}
	for(int i=1;i<=N;i++){
		qs[i]=qs[i-1]+a[i];
	}
	for(int i=0;i<M;i++){
		l[i+1]=L[i]+1;
		r[i+1]=R[i]+1;
		c[i+1]=C[i];
		if(qs[R[i]+1]-qs[L[i]]<=C[i])continue;
		s.insert({L[i]+1,R[i]+1});
	}
	return dp[M];
}
