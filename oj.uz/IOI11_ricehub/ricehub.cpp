#include "ricehub.h"
#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

int besthub(int R, int L, int X[], ll B){
	vector<ll> qs(R);
	for(int i=0;i<R;i++)qs[i]=X[i];
	for(int i=1;i<R;i++)qs[i]+=qs[i-1];
	auto sum=[&](int l,int r){
		if(r<l)return 0ll;
		return qs[r]-(l>0?qs[l-1]:0);
	};
	auto check=[&](int req){
		for(int l=0,r=req-1;r<R;l++,r++){
			int m=(l+r)/2;
			ll res=(1ll*X[m]*(m-l)-sum(l,m-1))+(sum(m+1,r)-1ll*X[m]*(r-m));
			if(res<=B)return true;
		}
		return false;
	};
	int l=1,r=R;
	while(l<r){
		int m=(l+r+1)/2;
		if(check(m))l=m;
		else r=m-1;
	}
	return l;
}
