#include "mergedmedian.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll ma[N],mb[N];

ll ga(int x){
	if(x<0)return 0;
	if(x>n)return 1e18;
	if(ma[x])return ma[x];
	return ma[x]=alice(x);
}

ll gb(int x){
	if(x<0)return 0;
	if(x>=n)return 1e18;
	if(mb[x])return mb[x];
	return mb[x]=bob(x);
}

long long find_merged_median(int N){
	n=N;
	int l=0,r=n;
	while(l+1<r){
		int m=(l+r)/2;
		ll a=ga(m);
		ll b=gb(n-m-1);
		if(a<b){
			l=m;
		}else{
			r=m;
		}
	}
	if(ga(l)<=gb(n-l-1)){
		if(gb(n-l-1)<=ga(l+1))return gb(n-l-1);
		return ga(l+1);
	}
	if(ga(l)<=gb(n-l))return ga(l);
	return gb(n-l);
}