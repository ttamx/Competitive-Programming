#include "wiring.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll inf=1e18;

int n;
ll dp[N];
vector<pair<int,int>> v;

ll min_total_length(vector<int> r,vector<int> b){
	v.emplace_back(-2e9,-1);
	int ri=0,bi=0;
	while(ri<r.size()||bi<b.size()){
		if(bi==b.size())v.emplace_back(r[ri++],1);
		else if(ri==r.size())v.emplace_back(b[bi++],2);
		else if(r[ri]<b[bi]) v.emplace_back(r[ri++],1);
		else v.emplace_back(b[bi++],2);
	}
	n=ri+bi;
	int st=1;
	for(int i=1;i<=n;i++)dp[i]=inf;
	for(int i=1;i<=n;i++){
		if(v[i].second!=v[i-1].second){
			for(int j=st;j<i;j++)dp[j]=min(dp[j],dp[j-1]+v[i].first-v[j].first);
			ll sum=0;
			for(int l=i-1,r=i;l>=1&&r<=n&&v[l].second==v[i-1].second&&v[r].second==v[i].second;l--,r++){
				sum+=v[r].first-v[l].first;
				dp[r]=min(dp[r],dp[l-1]+sum);
			}
			st=i;
		}
		dp[i]=min(dp[i],dp[i-1]+v[i].first-v[st-1].first);
	}
	return dp[n];
}