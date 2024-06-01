#include "buffet.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const ll INF=LLONG_MAX/2;

int n;
int a[N],l[N],r[N],par[N];
pair<int,int> range[N];
int rt;
priority_queue<pair<int,int>> pq;

void build_cart(){
	auto cmp=[&](int i,int j){
		return a[i]<a[j]||(a[i]==a[j]&&i<j);
	};
	stack<int> s;
	for(int i=1;i<=n;i++){
		while(!s.empty()&&cmp(i,s.top())){
			l[i]=s.top();
			s.pop();
		}
		range[i].first=!s.empty()?s.top()+1:1;
		s.emplace(i);
	}
	while(!s.empty())s.pop();
	for(int i=n;i>=1;i--){
		while(!s.empty()&&cmp(i,s.top())){
			r[i]=s.top();
			s.pop();
		}
		range[i].second=!s.empty()?s.top()-1:n;
		s.emplace(i);
	}
	for(int i=1;i<=n;i++)if(l[i])par[l[i]]=i;
	for(int i=1;i<=n;i++)if(r[i])par[r[i]]=i;
	for(int i=1;i<=n;i++)if(!par[i])rt=i;
}

void dfs(int u,int val){
	if(!u)return;
	if(a[u]>val){
		pq.emplace(range[u].second-range[u].first+1,a[u]-val);
	}
	dfs(l[u],a[u]);
	dfs(r[u],a[u]);
}

ll min_leftover(int _n,vector<int> A) {
	n=_n;
	if(n==2)return 0LL;
	for(int i=1;i<=n;i++)a[i]=A[i-1];
	int mn=*min_element(a+1,a+n+1);
	ll ans=0;
	for(int i=1;i<=n;i++)ans+=a[i]-mn;
	build_cart();
	dfs(rt,mn);
	while(mn>0&&!pq.empty()){
		auto [wid,cnt]=pq.top();
		pq.pop();
		ll used=min(cnt,mn);
		ans-=used*wid;
		mn-=used;
	}
	return ans;
}