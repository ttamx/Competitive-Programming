#include "horses.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;
const int K=1<<20;
const ll mod=1e9+7;

int n;
int X[N],Y[N];

struct segtree{
	struct node{
		ll x,y,pre,suf,all,ans;
		node(){}
		node(ll x,ll y):x(x),y(y),pre(x),suf(1),all(x),ans(x*y%mod){}
		friend node operator+(node l,node r){
			node res;
			res.x=l.x*r.x%mod;
			res.all=min(l.all*r.all,mod);
			if(l.y>min(l.suf*r.pre,mod)*r.y){
				res.y=l.y;
				res.pre=l.pre;
				res.suf=min(l.suf*r.all,mod);
				res.ans=l.ans;
			}else{
				res.y=r.y;
				res.pre=min(l.all*r.pre,mod);
				res.suf=r.suf;
				res.ans=l.x*r.ans%mod;
			}
			return res;
		}
	}t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=node(X[l],Y[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=node(X[l],Y[l]));
		int m=(l+r)/2;
		update(l,m,i*2,x);
		update(m+1,r,i*2+1,x);
		t[i]=t[i*2]+t[i*2+1];
	}
	void update(int x){
		update(1,n,1,x);
	}
}s;

int init(int _n, int _X[], int _Y[]) {
	n=_n;
	for(int i=1;i<=n;i++)X[i]=_X[i-1],Y[i]=_Y[i-1];
	s.build();
	return s.t[1].ans;
}

int updateX(int pos, int val) {
	pos++;
	X[pos]=val;
	s.update(pos);
	return s.t[1].ans;
}

int updateY(int pos, int val) {
	pos++;
	Y[pos]=val;
	s.update(pos);
	return s.t[1].ans;
}