#include <bits/stdc++.h>
#include "cake.h"

using namespace std;

using ll = long long;

const int N=100005;

int n,k;
ll a[N],b[N];
pair<ll,int> dp[N];

struct Range{
	int l,r,p;
	Range(int _l,int _r,int _p):l(_l),r(_r),p(_p){}
};

pair<ll,int> solve(ll lambda){
	deque<Range> dq{Range(2,n,1)};
	auto cost=[&](int l,int r){
		return (a[r]-a[l])*(b[r]-b[l]);
	};
	auto calc=[&](int i,int j){
		auto res=dp[j];
		res.first+=cost(i,j)+lambda;
		res.second++;
		return res;
	};
	for(int i=2;i<=n;i++){
		dp[i]=calc(i,dq.front().p);
		if(dq.front().r==i)dq.pop_front();
		else dq.front().l++;
		while(!dq.empty()&&calc(dq.back().l,i)<calc(dq.back().l,dq.back().p))dq.pop_back();
		if(dq.empty())dq.emplace_back(i+1,n,i);
		else{
			auto [l,r,p]=dq.back();
			while(l<r){
				int m=(l+r+1)/2;
				if(calc(m,i)<calc(m,p))r=m-1;
				else l=m;
			}
			dq.back().r=l;
			if(l<n)dq.emplace_back(l+1,n,i);
		}
	}
	return dp[n];
}

ll whipped_cream_price(int N, int M, vector<int> X, vector<int> Y) {
	n=N,k=M;
	for(int i=1;i<=n;i++){
		a[i]=X[i-1];
		b[i]=Y[i-1];
	}
	ll l=0,r=4e12;
	while(l<r){
		ll m=(l+r)/2;
		if(solve(m).second<=k)r=m;
		else l=m+1;
	}
	solve(l);
	return solve(l).first-l*k;
}