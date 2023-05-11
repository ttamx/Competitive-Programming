#include "bridge.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll qs[N],qs2[N];
ll dpl[N],dpr[N];

bool querymode=false;

struct line{
	mutable ll m,c,p;
	line(ll m,ll c):m(m),c(c){}
	line(ll p):p(p){}
	const bool operator<(const line &o)const{
		if(querymode)return p<o.p;
		return m>o.m;
	}
};

struct convexhull:multiset<line>{
	ll inf=LONG_LONG_MAX;
	ll div(ll a,ll b){
		return a/b-(a^b<0&&a%b);
	}
	bool isect(iterator x,iterator y){
		if(y==end())return x->p=inf,false;
		if(x->m==y->m)x->p=x->c<=y->c?inf:-inf;
		else x->p=div(x->c-y->c,y->m-x->m);
		return x->p>=y->p;
	}
	void add(ll m,ll c){
		auto y=insert(line(m,c)),x=y,z=next(y);
		while(isect(y,z))z=erase(z);
		if(y!=begin()&&isect(--x,y))isect(x,erase(y));
		while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
	}
	ll get(ll x){
		if(empty())return inf;
		querymode=true;
		auto l=lower_bound(line(x));
		querymode=false;
		return l->m*x+l->c;
	}
}cht;

long long destroy_bridge(int N, vector<int> W){
	n=N;
	for(int i=1;i<=n;i++){
		qs[i]=qs[i-1]+W[i-1];
		qs2[i]=qs2[i-1]+W[i-1]*W[i-1];
	}
	for(int i=2;i<=n;i++){
		cht.add(-2*qs[i-2],qs[i-2]*qs[i-2]+qs2[i-2]);
		dpl[i]=qs[i]*qs[i]-qs2[i]+cht.get(qs[i]);
		if(i>2)dpl[i]=min(dpl[i],dpl[i-1]);
	}
	cht.clear();
	for(int i=n;i>=1;i--){
		qs[i]=qs[i+1]+W[i-1];
		qs2[i]=qs2[i+1]+W[i-1]*W[i-1];
	}
	for(int i=n-1;i>=1;i--){
		cht.add(-2*qs[i+2],qs[i+2]*qs[i+2]+qs2[i+2]);
		dpr[i]=qs[i]*qs[i]-qs2[i]+cht.get(qs[i]);
		if(i<n-1)dpr[i]=min(dpr[i],dpr[i+1]);
	}
	ll ans=LONG_LONG_MAX;
	for(int i=3;i<n-1;i++)ans=min(ans,dpl[i-1]+dpr[i+1]);
	return ans/2;
}
