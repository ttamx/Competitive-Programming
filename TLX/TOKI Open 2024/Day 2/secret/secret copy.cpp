#include "secret.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const ll INF=LLONG_MAX/2;

int n,m;
int a[N];
ll qs[N];
set<int> s;

struct SegTree{
	struct Node{
		int l,r;
		Node():l(m),r(-1){}
		Node(int x):l(x),r(x){};
		Node(int _l,int _r):l(_l),r(_r){};
		friend Node operator+(Node l,Node r){
			return Node(min(l.l,r.l),max(l.r,r.r));
		}
	}t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=Node(a[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(0,n-1,1);
	}
	Node query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return Node();
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
	}
	Node query(int x,int y){
		return query(0,n-1,1,x,y);
	}
}seg;

void init(int _n,int _m,vector<int> A){
	n=_n,m=_m;
	for(int i=0;i<n;i++)a[i]=A[i];
	seg.build();
	for(int i=1;i<n;i++){
		int d=abs(a[i]-a[i-1]);
		qs[i]=qs[i-1]+d;
	}
}

void toggle(int R){
	if(!s.emplace(R).second)s.erase(R);
}

ll query(int S,int T){
	auto res=seg.query(S,T);
	auto it=s.lower_bound(res.l);
	if(it!=s.end()&&*it<res.r)return -1LL;
  	return qs[T]-qs[S];
}
