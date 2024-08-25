#include "ricehub.h"
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N=1e5+5;
const ll INF=1e18;

int n;
ll b;
ll a[N],qs[N];

bool check(int s){
	ll res=INF;
	for(int l=1,r=s;r<=n;l++,r++){
		int m=(l+r)/2;
		ll val=a[m]*(m-l)-(qs[m-1]-qs[l-1])+(qs[r]-qs[m])-a[m]*(r-m);
		res=min(res,val);
	}
	return res<=b;
}

int besthub(int _n, int L, int _a[], long long _b){
	n=_n,b=_b;
	for(int i=1;i<=n;i++){
		a[i]=_a[i-1];
	}
	for(int i=1;i<=n;i++){
		qs[i]=qs[i-1]+a[i];
	}
	int l=1,r=n;
	while(l<r){
		int m=(l+r+1)/2;
		if(check(m)){
			l=m;
		}else{
			r=m-1;
		}
	}
	return l;
}
