#include "purwokerto.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int MOD=1e9+7;

int n,m;
vector<pair<int,int>> seq;
deque<pair<int,int>> dq;
ll ans=0;
int ways=1;

struct Fenwick{
	int t[N];
	void update(int i,int v){
		for(;i<=n;i+=i&-i)t[i]+=v;
	}
	int query(int i){
		int res=0;
		for(;i>0;i-=i&-i)res+=t[i];
		return res;
	}
}f;

pair<ll,int> purwokerto(int _n,int _m,vector<int> T){
	n=_n,m=_m;
	for(auto x:T){
		if(!seq.empty()&&seq.back().first==x)seq.back().second++;
		else seq.emplace_back(x,1);
	}
	int cnt=0;
	for(auto [op,t]:seq){
		if(op){
			int used=min(t,cnt);
			for(int i=0;i<used;i++)ways=1LL*ways*(t-i)%MOD;
			cnt-=used;
			while(used--){
				auto &[l,r]=dq.front();
				ans+=r;
				int pos=f.query(r);
				ways=1LL*ways*pos%MOD;
				f.update(r,-pos);
				f.update(r+1,pos);
				if(l<r)r--;
				else dq.pop_front();
			}
		}else{
			while(t--){
				int p=n;
				while(!dq.empty()&&p<=dq.front().second){
					p-=dq.front().second-dq.front().first+1;
					dq.pop_front();
				}
				if(p<1)p=1;
				else cnt++;
				dq.emplace_front(p,n);
				f.update(p,1);
			}
		}
	}
	return {ans,ways};
}
