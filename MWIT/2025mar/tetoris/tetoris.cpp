#include"tetoris.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n;
vector<int> a;
vector<pair<ll,ll>> b;
vector<ll> sv,sc;
ll base,sumv,sumc;

void init(int _n, int _q, vector<int> _a){
	n=_n;
	a=move(_a);
	vector<int> s;
	auto push=[&](ll v,ll c){if(v>0&&c>0)b.emplace_back(v,c);};
	for(int i=0;i<n;i++){
		int h=0,j;
		while(!s.empty()&&a[j=s.back()]<=a[i]){
			push(i-j-1,a[j]-h);
			s.pop_back();
			h=a[j];
		}
		if(!s.empty())push(i-s.back()-1,a[i]-h);
		s.emplace_back(i);
	}
	sort(b.begin(),b.end());
	for(auto [v,c]:b){
		sv.emplace_back(sumv+=v*c);
		sc.emplace_back(sumc+=c);
	}
	base=*max_element(a.begin(),a.end());
}

ll miku_ask(ll x){
	int i=upper_bound(sv.begin(),sv.end(),x)-sv.begin();
	if(i==b.size())return base;
	ll res=base+sumc;
	if(i){
		x-=sv[i-1];
		res-=sc[i-1];
	}
	return res-x/b[i].first;
}