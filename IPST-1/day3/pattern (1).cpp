#include "pattern.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

ll n,m;
ll dp[N][7];
ll all[N];
ll pow1[N],pow2[N];
vector<int> adj[N];
vector<int> req;

int total_pattern(int N, int M, std::vector<std::vector<int> >Path, std::vector<std::vector<int> >p)
{
	n=N,m=M;
	for(auto v:p)req.push_back(v[1]);
	sort(req.begin(),req.end());
	req.erase(unique(req.begin(),req.end()),req.end());
	if(req.size()>1)return 0;
	if(req.size()==1){
		if(req[0]>=m)return 0;
		return 1;
	}
	return m;
}
