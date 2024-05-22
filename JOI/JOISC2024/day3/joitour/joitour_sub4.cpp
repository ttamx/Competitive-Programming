#include "joitour.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int LG=20;
const bool DBG=false;
const int K=1<<19;

int n;
int a[N];
ll ans;

struct Segtree{
	struct node{
		ll suf[3],pre[3],cnt[3];
		node(){
			for(int i=0;i<3;i++)suf[i]=pre[i]=cnt[i]=0;
		}
		node(int x){
			for(int i=0;i<3;i++)suf[i]=pre[i]=cnt[i]=0;
			cnt[x]=1;
		}
		friend node operator+(const node &lhs,const node &rhs){
			node res;
			res.suf[0]=lhs.suf[0]+rhs.suf[0]+lhs.cnt[0]*rhs.cnt[1];
			res.suf[2]=lhs.suf[2]+rhs.suf[2]+lhs.cnt[2]*rhs.cnt[1];
			res.pre[0]=lhs.pre[0]+rhs.pre[0]+rhs.cnt[0]*lhs.cnt[1];
			res.pre[2]=lhs.pre[2]+rhs.pre[2]+rhs.cnt[2]*lhs.cnt[1];
			for(int i=0;i<3;i++)res.cnt[i]=lhs.cnt[i]+rhs.cnt[i];
			return res;
		}
	}t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=node(a[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x,int v){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=node(v));
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=t[i*2]+t[i*2+1];
	}
	void update(int x,int v){
		update(1,n,1,x,v);
	}
	node query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return node();
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
	}
	node query(int x,int y){
		return query(1,n,1,x,y);
	}
}s;

void init(int N,vector<int> F,vector<int> U,vector<int> V,int Q){
	n=N;
	for(int i=1;i<=n;i++)a[i]=F[i-1];
	s.build();
	for(int i=1;i<=n;i++){
		auto ql=s.query(1,i-1),qr=s.query(i+1,n);
		if(a[i]==1){
			ans+=ql.cnt[0]*qr.cnt[2];
			ans+=ql.cnt[2]*qr.cnt[0];
		}else{
			ans+=ql.suf[a[i]^2];
			ans+=qr.pre[a[i]^2];
		}
	}
	assert(ans%3==0);
	ans/=3;
}

void change(int X,int Y){
	X++;
	auto ql=s.query(1,X-1),qr=s.query(X+1,n);
	if(a[X]==1){
		ans-=ql.cnt[0]*qr.cnt[2];
		ans-=ql.cnt[2]*qr.cnt[0];
	}else{
		ans-=ql.suf[a[X]^2];
		ans-=qr.pre[a[X]^2];
	}
	a[X]=Y;
	s.update(X,Y);
	ql=s.query(1,X-1),qr=s.query(X+1,n);
	if(a[X]==1){
		ans+=ql.cnt[0]*qr.cnt[2];
		ans+=ql.cnt[2]*qr.cnt[0];
	}else{
		ans+=ql.suf[a[X]^2];
		ans+=qr.pre[a[X]^2];
	}
}

long long num_tours(){
	if(DBG)cerr << "RETURN " << ans << "\n";
	return ans;
}
