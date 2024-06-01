#include "secret.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=LLONG_MAX/2;

int n,m;
int a[N];
ll qs[N];
int cnt[N];
set<int> s;

void init(int _n,int _m,vector<int> A){
	n=_n,m=_m;
	for(int i=0;i<n;i++)a[i]=A[i];
	for(int i=1;i<n;i++){
		int d=abs(a[i]-a[i-1]);
		qs[i]=qs[i-1]+min(d,m-d);
	}
}

void toggle(int R){
	if(!s.emplace(R).second)s.erase(R);
	for(int i=1;i<n;i++){
		qs[i]=qs[i-1];
		cnt[i]=cnt[i-1];
		if(a[i]==a[i-1])continue;
		int d=m;
		auto [l,r]=minmax(a[i-1],a[i]);
		auto it=s.lower_bound(l);
		if(it==s.end()||*it>=r)d=min(d,r-l);
		if(s.empty()||(*s.begin()>=l&&*s.rbegin()<r))d=min(d,m-r+l);
		if(d<m)qs[i]+=d;
		else cnt[i]++;
	}
}

ll query(int S,int T){
	if(cnt[T]-cnt[S])return -1LL;
  	return qs[T]-qs[S];
}
