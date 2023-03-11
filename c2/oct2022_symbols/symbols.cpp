#include "symbols.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=80005;
const int K=1<<18;
const ll mod=20232566;

struct mint{
	ll x;
	mint():x(0){}
	mint(ll x):x(x%mod){}
	mint& operator+=(mint o){x=(x+o.x)%mod;return *this;}
	mint& operator-=(mint o){x=(mod+x-o.x)%mod;return *this;}
	mint& operator*=(mint o){x=(x*o.x)%mod;return *this;}
	friend mint operator+(mint a,mint b){return a+=b;}
	friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}
};

int n,q;

struct segtree{
	mint t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=26);
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]*t[i*2+1];
	}
	void build(){
		build(0,n-1,1);
	}
	void update(int l,int r,int i,int &x,int &v){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=v);
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=t[i*2]*t[i*2+1];
	}
	void update(int x,int v){
		update(0,n-1,1,x,v);
	}
}s;

set<int> st[N];

void explore_site(int N, int Q) {
	n=N,q=Q;
	s.build();
}

bool ok=true;

int retrieve_notes(int L, int R) {
	if(R-L+1>26)ok=false;
	if(!ok)return 0;
	for(int i=L;i<=R;i++){
		for(int j=L;j<i;j++)st[i].emplace(j);
		s.update(i,max(0,26-(int)st[i].size()));
	}
	return s.t[1].x;
}