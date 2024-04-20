#include "hanoi.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using ar = array<int,4>;

const ll INF=LLONG_MAX/2;

vector<vl> calc_dp(int n,vector<vi> a){
	for(auto &v:a)reverse(v.begin(),v.end());
	vector<vl> dp(n+1,vl(3));
	for(int k=1;k<=n;k++){
		vi cnt(3);
		for(int i=0;i<3;i++){
			while(!a[i].empty()&&a[i].back()<k){
				cnt[i]++;
				a[i].pop_back();
			}
		}
		for(int i=0;i<3;i++){
			if(cnt[i]==2){
				dp[k][i]=dp[k-1][i];
				continue;
			}
			if(cnt[i]==0){
				dp[k][i]=INF;
				for(int j=0;j<3;j++)if(i!=j){
					if(cnt[j]==1){
						dp[k][i]=min(dp[k][i],dp[k-1][j]+(2LL<<k)-2);
						dp[k][i]=min(dp[k][i],dp[k-1][i]+(2LL<<k)-1);
					}
					if(cnt[j]==0)dp[k][i]=dp[k-1][j]+(1LL<<k);
				}
				continue;
			}
			for(int j=0;j<3;j++)if(cnt[j]==0){
				dp[k][i]=dp[k-1][j]+(1LL<<k)-1;
			}
		}
	}
	return dp;
}

struct State{
	ll d;
	vi u;
	int x;
	State(ll _d,vi _u,int _x):d(_d),u(_u),x(_x){}
	bool operator<(const State &o)const{
		return d>o.d;
	}
};

ll hanoi(int n,vi s0,vi s1,vi s2,vi t0,vi t1,vi t2){
	vector<vi> s{s0,s1,s2},t{t0,t1,t2};
	auto dps=calc_dp(n,s);
	auto dpt=calc_dp(n,t);
	for(int k=n-1;k>=0;k--){
		vi cs(3),ct(3);
		bool ok=true;
		for(int i=0;i<3;i++){
			while(!s[i].empty()&&s[i].back()==k){
				cs[i]++;
				s[i].pop_back();
			}
			while(!t[i].empty()&&t[i].back()==k){
				ct[i]++;
				t[i].pop_back();
			}
			if(cs[i]!=ct[i])ok=false;
		}
		if(ok)continue;
		ll ans=INF;
		map<pair<vi,int>,ll> dp;
		priority_queue<State> pq;
		for(int i=0;i<3;i++){
			pq.emplace(State(dps[k][i],cs,i));
			dp[{cs,i}]=dps[k][i];
		}
		while(!pq.empty()){
			auto [d,u,x]=pq.top();
			pq.pop();
			if(d>dp[{u,x}])continue;
			if(u==ct){
				ans=min(ans,d+dpt[k][x]);
				continue;
			}
			for(int i=0;i<3;i++)if(i!=x&&u[i]>0){
				for(int j=0;j<3;j++)if(i!=j&&j!=x){
					u[i]--,u[j]++;
					for(int p=0;p<3;p++){
						ll nd=d+1;
						if(p!=x)nd+=(2LL<<k)-2;
						if(dp.find({u,p})==dp.end()||nd<dp[{u,p}]){
							dp[{u,p}]=nd;
							pq.emplace(State(nd,u,p));
						}
					}
					u[i]++,u[j]--;
				}
			}
		}
		return ans;
	}
	return 0LL;
}