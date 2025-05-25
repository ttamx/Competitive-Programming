#include "eatingfish.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=300005;
const int K=1<<20;

int n;
int a[N];

struct Segtree{
	int t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=a[l]);
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void build(){build(0,n-1,1);}
	void modify(int l,int r,int i,int x,int v){
		if(l==r)return void(t[i]=v);
		int m=(l+r)/2;
		if(x<=m)modify(l,m,i*2,x,v);
		else modify(m+1,r,i*2+1,x,v);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void modify(int x,int v){modify(0,n-1,1,x,v);}
	int find_first(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x||t[i]<=v)return n;
		if(l==r)return l;
		int m=(l+r)/2;
		int res=find_first(l,m,i*2,x,y,v);
		if(res==n)res=find_first(m+1,r,i*2+1,x,y,v);
		return res;
	}
	int find_first(int x,int y,ll v){return find_first(0,n-1,1,x,y,v);}
	int find_last(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x||t[i]<=v)return -1;
		if(l==r)return l;
		int m=(l+r)/2;
		int res=find_last(m+1,r,i*2+1,x,y,v);
		if(res==-1)res=find_last(l,m,i*2,x,y,v);
		return res;
	}
	int find_last(int x,int y,ll v){return find_last(0,n-1,1,x,y,v);}
}seg;

struct Fenwick{
	ll t[N];
	void update(int i,int v){
		for(i++;i<=n;i+=i&-i)t[i]+=v;
	}
	ll query(int i){
		ll res=0;
		for(i++;i>0;i-=i&-i)res+=t[i];
		return res;
	}
	ll query(int l,int r){return query(r)-query(l-1);}
}fen;

void init_fish(int _n,vector<int> _a){
	n=_n;
	for(int i=0;i<n;i++)fen.update(i,a[i]=_a[i]);
	seg.build();
}

void cast_magic(int i,int _v){
	ll v=_v;
	fen.update(i,v-a[i]);
	seg.modify(i,v);
	a[i]=v;
}

ll eat_friend(int i,int l,int r){
	int cl=i,cr=i;
	auto s=[&](){return fen.query(cl,cr);};
	while(true){
		if(l<cl){
			int p=seg.find_last(l,cl-1,s())+1;
			if(p<cl){
				cl=max(l,p);
				continue;
			}
		}
		if(r>cr){
			int p=seg.find_first(cr+1,r,s())-1;
			if(p>cr){
				cr=min(r,p);
				continue;
			}
		}
		break;
	}
	return s();
}